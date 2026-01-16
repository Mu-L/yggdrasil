**udp_connect_handler.hpp 文档**

简介：
- `udp_connect_handler` 用于主动发起 UDP “连接” 语义的流程：分配/复用 UDP socket、发送检测包、接收检测回复并在检测通过后将连接插入会话管理器（包含启动模式数据）。它基于 `basic_udp_connect_handler` 提供地址解析、重试与超时机制。

模板参数：
- `ServicePool`：提供 `service_type`（io_service / io_context）的服务池。
- `SessionMgrWrap`：会话管理器封装类型，需提供 `value_ptr_type`、`get_shared_ptr()`、`insert(conn_ptr, start_mode)`、`send_to_adapter(...)` 等接口。
- `OptionsSetter`：连接选项设置/验证类型，需提供 `operator()(conn)` 返回 `bool`。
- `Error_Maker`：错误生成器类型，提供 `error_type` 与 `make_error()` 等常量/方法。

主要类型别名（摘要）：
- `conn_type` / `conn_ptr_type`：会话使用的连接类型与指针。
- `socket_type` / `socket_ptr_type` / `udp_socket_pool_type`：UDP socket 与 socket 池类型，用于 socket 分配与回收。
- `recv_data_type`：接收到的应用层数据结构（由 `udp_packet_wrap` 解析得到），其中 `owner_id()` 用于判断是否为新连接请求。

关键方法与行为：
- 构造：接受 `service_pool`、`session_mgr_wrap` 与 `init_type`（socket 池大小），内部创建 `_pudp_socket_pool`。
- `connect(addr, port)` 与 `connect(addr, port, timeout)`：
  - 从 `_pudp_socket_pool` 获取一个 socket（`get`），创建 `conn_ptr`（使用 `pro_s_create_connect` 并绑定回收 handler）。
  - 调用 `recv(psocket)` 启动对该 socket 的异步接收（buffer 分配与 `async_receive_from`）。
  - 调用 `base_type::s_connect(pconn, addr, port, handler[, timeout])` 发起地址解析与发送检测流程，回调为 `pro_s_handler_connect`。
- `pro_s_handler_connect`：当检测操作完成时被调用，成功时（无错误码）会关闭 `pconn` 并停止重试（当前设计中主动发起的 UDP 连接在检测成功时直接关闭连接对象，详见实现）。出错时返回 `true` 表示继续重试。
- `recv` / `handler_recv`：管理 socket 的异步接收与数据重组，通过 `_collecter.collect` 得到完整包并解析为 `recv_data_type`。根据 `recv_data_type::owner_id()` 区分新连接（`owner_id()==0`）或已有会话的数据。
  - 新连接请求：调用 `accept_complete` → `pro_insert_to_session`，此处会创建 `conn_ptr`（绑定 socket 回收 handler）、调用 `pconn->connect(*ped)` 并构建 `start_mode`（从 `recv_data`）后调用 `psmgr->insert(pconn, start_mode)` 将连接插入会话管理器。
  - 已有会话数据：调用 `recv_complete`，将数据交给 `psmgr->send_to_adapter(data)`。
- `close()`：清理并关闭所有正在备份的连接（`base_type::clear_backup`）并关闭 socket 池。

错误与资源管理：
- 通过 `pro_s_throw_error` 与 `error_maker_type::make_error(...)` 抛出或记录错误，常用系统码为 `E_UDP_BASE_NETWORK_SYSTEM`。
- `pro_s_back_socket` 用于在连接对象完成后将 socket 返回到池。
- `pro_s_create_connect(socket, handler)` 提供异常安全的连接对象创建。

使用约定与注意事项：
- UDP 是无连接协议，此处“连接”是应用层的会话抽象；检测包（`udp_conn_checker`）用于确认对端可达并携带启动数据用于构建 `start_mode`。
- `conn_type` 构造签名应支持 `(socket_type&, Handler)`，Handler 被用于在连接对象释放时回收 socket。
- `_s_recv_buf_queue` 为静态复用的接收缓冲队列，保证性能与内存复用。
- 在使用 `connect` 时，请确保 `OptionsSetter` 与 `Error_Maker` 能配合你的会话管理策略。

示例（伪代码）：

```cpp
udp_connect_handler<ServicePool, SessionMgrWrap, OptionsSetter, ErrorMaker> handler(pool, smgr_wrap, init_type(32));
handler.connect("example.com", "12345");
// 或带超时
handler.connect("example.com", "12345", boost::posix_time::seconds(3));
```

文件： [yggr/network/session_helper/udp_connect_handler.hpp](udp_connect_handler.hpp)
