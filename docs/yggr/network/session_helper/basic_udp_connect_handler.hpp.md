**basic_udp_connect_handler.hpp 文档**

简介：
- `basic_udp_connect_handler` 是一个模板化的辅助类，用于对基于 UDP 的“连接”（UDP 语义下的会话）进行异步建立与检查流程管理。它封装了地址解析、按序尝试多个 endpoint、发送检测包以确认可达性、超时处理以及在检测失败时重试/替换连接的通用逻辑。

模板参数：
- `ConnPtr`：连接指针类型（通常为 `shared_ptr<Conn>` 或类似封装）。
- `NetInfo`：发送检测包时使用的网络信息类型（例如用于封装应用层检测数据）。

`Conn` 所需接口（概要）：
- 类型别名：`endpoint_type`、`protocol_type`、`deadline_timer_type` 等。
- 方法：
  - `get_service()`：返回 `io_service`/`io_context`。
  - `connect(endpoint)`：设置/绑定要使用的远端 endpoint（UDP 无连接但会为发送/接收设定对端）。
  - `send_packet(NetInfo, udp_conn_checker_type, handler)`：发送检测包并在收到应答或超时/错误时回调 handler。
  - `close()`、`shut_down_all()`、`timer_finish()`：资源与定时器管理。
  - `get_init_object()`、`get_socket_destroyer()`、`clear_socket_destroyer()`：用于创建/转移套接字控制权的辅助接口。

主要类型别名（摘要）：
- `conn_ptr_type`：同 `ConnPtr`。
- `conn_type`：指针指向的连接类型。
- `endpoint_type`、`protocol_type`：与 `conn_type` 相关的 endpoint/protocol。
- `resolver_type`：用于 DNS/地址解析的解析器类型。
- `id_type`：内部用于备份/追踪连接的 id 类型（来自 `yggr::ids::id64_type`）。
- `udp_conn_checker_type`：用于生成检测包的检查器类型（来自 `yggr::network::udp_ctrl_data::udp_conn_checker`）。

主要静态接口：
- `s_connect(conn_ptr, addr, port, handler)`
  - 作用：解析 `addr:port`，将 `pconn` 与第一个解析到的 endpoint 关联（`connect(edpt)`），发送检测包并在收到结果时通过内部回调处理。
  - `handler` 签名：可调用对象，通常原型为 `bool handler(const boost::system::error_code& e, conn_ptr_type pconn)`。返回值 `bool` 用于指示当检测成功后是否继续创建/保留新连接并再次调用 `s_connect`。

- `s_connect(conn_ptr, addr, port, handler, timeout)`
  - 作用：与上面重载类似，但附带超时 `timeout`。在指定超时时间到达前若未收到检测响应，会触发超时处理并调用 `handler`（带超时错误码）。

内部行为要点：
- 备份机制：在发起检测前，会将 `pconn` 存入内部安全备份容器（`backup`），并获得一个 `id`，用于在回调中临时获取或移除该连接（`drop_backup` / `get`）。此机制避免在异步回调期间对象被提前析构。
- 地址解析：使用 `resolver` 将 `addr:port` 解析为一组 endpoint，按顺序对每个 endpoint 执行 `connect(edpt)` + `send_packet`，直到某个 endpoint 检测成功或用尽所有 endpoint。
- 检测包：类使用 `NetInfo()`（默认构造）与 `udp_conn_checker_type(0)` 构造检测包参数调用 `send_packet`，回调 `prv_s_handler_connect_v1` / `v2` 来处理结果。
- 替换套接字控制权：当需要重建新的 `conn` 时，会用 `pconn->get_socket_destroyer()` 将 socket 管理权传递给新的 `conn`，然后在旧连接上调用 `clear_socket_destroyer()` 与 `close()`。
- 超时处理：对于带超时的重载，会为该 `id` 设置定时器（`expires_from_now_timer_wait`）；超时触发时会调用 `prv_s_handler_timedout`，在满足超时条件后调用 `handler` 并传入 `boost::asio::error::timed_out`。
- 错误上报：在最终失败路径，会通过 `exception::exception::throw_error` 抛出 `E_UDP_BASE_NETWORK_SYSTEM` 的系统级错误。

回调 handler 约定：
- `handler` 一般接收 `(const boost::system::error_code&, conn_ptr_type)`。
- 返回 `bool`：若返回 `true`，表示在成功后希望继续创建/保留新连接并再次调用 `s_connect`（用于链式或批量连接）；若返回 `false`，则当前连接会被关闭并停止重试。
- 在部分超时或检测失败场景中，回调可能只接收到错误码（或 `pconn` 为空），因此 handler 应当具备对没有有效 `pconn` 的容错处理。

示例（伪代码）：

```cpp
// 假设 ConnPtr 是 shared_ptr<MyUdpConn>，NetInfo 是自定义检测数据类型
ConnPtr pconn = make_shared<MyUdpConn>(init_obj);

auto handler = [](const boost::system::error_code& ec, ConnPtr p)->bool{
    if(!ec) {
        // 检测成功，p 可用于后续通信
        return true; // 若需要，可继续创建并尝试下一个连接
    }
    else {
        // 处理错误或超时
        return false; // 停止重试
    }
};

// 不带超时
yggr::network::session_helper::basic_udp_connect_handler<ConnPtr, NetInfo>::s_connect(pconn, "example.com", "12345", handler);

// 带超时（例如 3 秒）
yggr::network::session_helper::basic_udp_connect_handler<ConnPtr, NetInfo>::s_connect(pconn, "example.com", "12345", handler, boost::posix_time::seconds(3));
```

注意事项：
- `ConnPtr` / `conn_type` 必须实现头文件中期望的接口（特别是 `send_packet`、套接字 destroyer 和定时器接口）。
- UDP 检测使用发送检测包并等待应答的方式，并非真正的“连接”，因此上层逻辑需理解 UDP 的无连接特性。
- handler 在被库内部调用时，可能出现 `pconn` 为空或仅收到错误码的情况，编写 handler 时应考虑这些场景。

扩展建议：
- 若需要把此文档加入项目文档索引，我可以帮你添加到主文档目录或将关键注释放回头文件以生成 Doxygen 文档。

文件： [yggr/network/session_helper/basic_udp_connect_handler.hpp](yggr/network/session_helper/basic_udp_connect_handler.hpp)
