**basic_tcp_connect_handler.hpp 文档**

简介：
- `basic_tcp_connect_handler` 是一个模板化的辅助工具，用于对基于 TCP 的连接（ConnPtr）进行异步连接管理。它封装了地址解析、按序尝试多个 endpoint、超时处理以及在连接失败时进行重试/替换连接的通用逻辑。

模板参数：
- `ConnPtr`：连接指针类型（通常是 `shared_ptr<Conn>` 或类似封装）。`Conn` 需要定义以下成员类型和方法：
  - `endpoint_type`、`protocol_type`、`deadline_timer_type` 等类型别名
  - `get_service()`：返回 `io_service`/`io_context`
  - `connect(tuple)`：发起异步 connect（接受 endpoint 与 handler 的 tuple）
  - `close()`、`shut_down_all()`、`timer_finish()` 等生命周期和定时器管理方法
  - `get_init_object()`：用于创建新连接的初始化参数

主要类型别名（摘要）：
- `conn_ptr_type`：同 `ConnPtr`
- `conn_type`：指针所指类型
- `endpoint_type`、`protocol_type`：与 `conn_type` 相关的 endpoint/protocol
- `resolver_type`：用于 DNS/地址解析的解析器类型
- `id_type`：内部用于备份/追踪连接的 id 类型（来自 `yggr::ids::id64_type`）

主要静态接口：
- `s_connect(conn_ptr, addr, port, handler)`
  - 作用：使用解析器解析 `addr:port`，取得第一个 endpoint，发起异步 connect，并在完成时调用内部 handler 逻辑。
  - `handler` 签名：可调用对象，原型应为 `bool handler(const boost::system::error_code& e, conn_ptr_type pconn)` 或在不带超时的情况下也可接受 `(const boost::system::error_code&, conn_ptr_type)`。返回值 `bool` 表示是否在成功连接后继续使用并发起下一个连接（library 内部用于决定是否创建新连接并再次调用 s_connect）。

- `s_connect(conn_ptr, addr, port, handler, timeout)`
  - 作用：与上面重载类似，但附带超时 `timeout`。如果连接在 `timeout` 到期后仍未完成，将触发超时处理并调用 `handler`（带超时错误码）。

内部行为（要点）：
- 备份：在发起异步 connect 前，会将 `pconn` 备份到内部安全容器，并获得一个 `id` 用于后续查找或取消。
- 地址解析：使用 `resolver` 将 `addr:port` 解析为一组 endpoint，按顺序尝试每个 endpoint，直到成功或用尽所有 endpoint。
- 重试 / 替换连接：当解析的 endpoint 失败且 handler 表示继续重试时，会重建一个新的 `conn`（使用 `get_init_object()`），并对新连接再次调用 `s_connect`（可循环重试多个 endpoint）。
- 超时处理：当使用带 `timeout` 的重载时，会为该 `id` 设置一个超时定时器；超时触发后会调用 `pconn->shut_down_all()` 并将超时错误（`boost::asio::error::timed_out`）传给 `handler`。
- 错误上报：在某些错误路径，最终会通过 `exception::exception::throw_error` 抛出网络系统级错误（`E_TCP_BASE_NETWORK_SYSTEM`）。

回调 handler 约定：
- handler 需要能够接收一个 `boost::system::error_code`，并且通常可接收 `conn_ptr_type`（在非超时触发时）。
- 返回 `bool`：若返回 `true`，表示在成功后希望继续创建/保留新连接并再次调用 `s_connect`（库用于链式连接尝试）；若返回 `false`，则当前连接会被关闭并停止重试。

示例（伪代码）:

```cpp
// 假设 ConnPtr 是 shared_ptr<MyTcpConn>
ConnPtr pconn = make_shared<MyTcpConn>(init_obj);

auto handler = [](const boost::system::error_code& ec, ConnPtr p)->bool{
    if(!ec) {
        // 连接成功
        // p 可用于后续读写
        return true; // 如果想继续并创建下一个连接（根据具体逻辑）
    }
    else {
        // 处理错误（包括超时）
        return false; // 不再重试则关闭
    }
};

// 不带超时
yggr::network::session_helper::basic_tcp_connect_handler<ConnPtr>::s_connect(pconn, "example.com", "80", handler);

// 带超时（例如 5 秒）
yggr::network::session_helper::basic_tcp_connect_handler<ConnPtr>::s_connect(pconn, "example.com", "80", handler, boost::posix_time::seconds(5));
```

注意事项：
- `ConnPtr` / `conn_type` 必须实现库中期望的接口（定时器、connect 接口与构造/初始化方法）。
- handler 在被库内部调用时可能只收到错误码（例如超时触发时），因此应对缺少 `pconn` 的情形进行容错处理。
- 该类通过内部安全容器临时“备份”连接以防止回调期间连接对象被析构；理解这一点有助于正确管理生命周期。

扩展建议：
- 若需要将该文件纳入项目文档系统，可将此 Markdown 加入到项目的文档索引或转换为 Doxygen 注释插入到头文件中。

文件： [yggr/network/session_helper/basic_tcp_connect_handler.hpp](yggr/network/session_helper/basic_tcp_connect_handler.hpp)
