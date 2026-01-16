**udp_async_acceptor_handler.hpp 文档**

简介：
- `udp_async_acceptor_handler` 是用于接收与处理 UDP 数据报并在必要时将其转换为会话连接（或交付给适配器）的组件。它实现了对 UDP 套接字池、数据包收集/重组、检测包处理和会话插入的完整逻辑。

模板参数：
- `ServicePool`：提供 `service_type`（io_service / io_context）的服务池类型。
- `Acceptor`：UDP 接收端（在本实现中 `acceptor_type` 必须等同于 `conn_type::socket_type`）。
- `SessionMgrWrap`：会话管理器封装，需提供 `value_ptr_type`、`get_shared_ptr()`、`insert(conn_ptr)`、`send_to_adapter(...)` 等接口。
- `OptionsSetter`：用于在创建连接/套接字时进行选项设置或验证的策略类型。
- `Error_Maker`：错误生成器类型，提供 `error_type` 与 `make_error()` 以及若干 `E_*` 错误码。

主要类型别名（摘要）：
- `conn_type`、`conn_ptr_type`、`socket_type`、`endpoint_type`、`udp_socket_pool_type`、`udp_packets_collecter_type`、`recv_data_type` 等，均基于 `Session` 与 `Conn` 的类型定义。

关键功能与流程：
- 套接字池：内部维护 `udp_socket_pool`，按 `init.pool_size` 大小初始化，用于复用底层 UDP sockets，避免频繁创建销毁。
- listen/recv 流程：
  - `listen()`：如果 `_pacceptor` 有效，调用 `recv(_pacceptor)` 启动接收循环。
  - `recv(psocket)`：从静态接收缓存队列获取缓冲区，准备接收并调用 `psocket->async_receive_from(...)`，回调为 `handler_recv`。
  - `handler_recv(...)`：再次调用 `recv(psocket)` 继续接收；若接收成功则将接收到的缓冲打包交给 `_collecter.collect()`，若收集得到完整包则解析为 `recv_data_type`。根据 `recv_data_type::owner_id()` 判断数据类型：
    - 若 `owner_id()` 为空（表示是新连接请求／检测包），调用 `accept_complete(ped, rd)`。
    - 否则调用 `recv_complete(ped, rd)` 将数据转发给会话管理器（`psmgr->send_to_adapter(data)`)。
- accept_complete：
  - 从 `_pudp_socket_pool` 获取一个 socket（`get`），并基于检测包数据校验（`udp_conn_checker`）通过 `data.load(checker)` 与 `checker.check()`。
  - 若校验通过，调用 `pro_s_create_connect` 创建 `conn_ptr_type`（将 socket 与回收 handler 绑定），然后对 `pconn->connect(*ped)` 并将 `pconn` 插入会话管理器 `psmgr->insert(pconn)`。
- recv_complete：直接把接收到的数据派发到适配器层 `psmgr->send_to_adapter(data)`（如果会话管理器存在）。

辅助与错误处理：
- `pro_s_create_connect(socket, handler)`：构造 `conn_type` 的 `conn_ptr`，异常安全返回空指针表示创建失败。
- `pro_s_back_socket`：用于将 socket 返回到 socket 池。
- 错误通过 `pro_s_throw_error` 与 `error_maker_type::make_error(...)` 转为 `exception::exception::throw_error` 抛出或记录，常用系统码为 `E_UDP_BASE_NETWORK_SYSTEM`。

缓冲与收集器：
- 使用 `udp_packets_collecter` 对分片/多包场景进行重组，返回 `packet_wrap_ptr_type` 表示可用的包用于解析；收集器同时负责回收 buffer 与管理临时对象。

示例（伪代码）：

```cpp
ServicePool pool = ...;
auto acceptor = make_shared<MyUdpSocket>(...);
udp_async_acceptor_handler<ServicePool, MyUdpSocket, SessionMgrWrap, OptionsSetter, ErrorMaker> handler(pool, acceptor, smgr_wrap, 64);
handler.listen();

// 停止与清理
handler.close();
```

注意事项：
- UDP 为无连接协议，本组件通过检测包（udp_conn_checker）识别并将符合条件的数据升级为会话连接（在插入会话管理器之前会为其分配/绑定独立 socket）。
- `conn_type` 构造函数签名应支持 `(socket_type&, Handler)`，以便在连接对象生命周期结束时能正确归还 socket（`pro_s_back_socket`）。
- `_s_recv_buf_queue` 为全局静态接收缓冲队列，确保同一进程内共享且复用接收缓冲。
- 错误路径会调用 `pro_s_throw_error`，调用者需保证全局异常策略能够接受该行为（或替换 `Error_Maker`）。

文件： [yggr/network/session_helper/udp_async_acceptor_handler.hpp](udp_async_acceptor_handler.hpp)
