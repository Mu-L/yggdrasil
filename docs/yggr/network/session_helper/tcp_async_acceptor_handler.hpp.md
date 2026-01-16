**tcp_async_acceptor_handler.hpp 文档**

简介：
- `tcp_async_acceptor_handler` 是一个用于异步接受 TCP 连接并将新连接注册到会话管理器的模板类。它封装了连接分配、accept 调用、错误处理和选项验证等服务端接收端通用逻辑。

模板参数：
- `ServicePool`：提供 `service_type` 的对象（用于创建连接时的 io_service / io_context）。
- `Acceptor`：异步 acceptor 类型（需提供 `async_accept(link, handler)`）。
- `SessionMgrWrap`：封装的会话管理器类型，需提供 `value_ptr_type`、`get_shared_ptr()` 与 `insert(conn_ptr)` 接口，以及 `value_type::conn_ptr_type`。
- `OptionsSetter`：可选的选项设置/验证策略类型，默认需提供 `operator()(conn)` 返回 `bool`。
- `Error_Maker`：错误生成器类型，需提供 `error_type` 与若干 `E_*` 枚举/常量及 `make_error()` 方法。

主要类型别名（摘要）：
- `conn_type`、`conn_ptr_type`：会话管理器中使用的连接类型与其指针。
- `acceptor_ptr_type`：`shared_ptr<Acceptor>`。
- `service_type`：来自 `ServicePool` 的 `service_type`。
- `id_type`：用于内部备份容器的 key（来自 `ids::id64_type`）。

关键方法与行为：
- 构造：
  - `tcp_async_acceptor_handler(service_pool_type& pool, acceptor_ptr_type pacceptor, session_mgr_wrap_type& smgr_wrap, const init_type&)`：保存服务池、acceptor 与会话管理器封装引用。
- `listen()`：
  - 分配一个新的 `conn_type`（使用 `service_pool.get_service()`），并将其 `conn_ptr` 备份到内部安全备份容器（`base_type::backup`），用于在 accept 回调中匹配。
  - 调用 `_pacceptor->async_accept(ptr->get_link(), handler)` 发起异步 accept，`handler` 为 `pro_handler_accept`。
  - 若分配失败或备份失败，会使用 `pro_s_throw_error` 抛出或记录错误并重试分配。
- `pro_handler_accept(const boost::system::error_code& e, const id_type& id)`：accept 的回调。
  - 从备份中 `drop_backup(id)` 获取对应的 `conn_ptr`。
  - 立即再次调用 `listen()` 以接收下一个连接。
  - 若 `pconn` 为空或出现错误 `e`，会关闭连接并通过 `pro_s_throw_error` 抛出/记录错误。
  - 否则，调用 `pro_s_options_setter()(*pconn)` 进行选项验证；若失败则抛错并关闭连接。
  - 获取 `session_mgr_ptr_type psmgr = _session_mgr_wrap.get_shared_ptr()`，若有效则调用 `psmgr->insert(pconn)` 将新连接插入会话管理器。
- `close()`：清理备份容器并在回调中关闭所有备份的连接（`pro_s_handler_clear_backup`）。

错误与异常处理：
- 在内存分配、accept 或验证失败的路径上，类会调用 `pro_s_throw_error` 并使用 `error_maker_type::make_error(...)` 生成适当的错误，然后通过 `exception::exception::throw_error` 抛出或记录（可携带系统码 `E_TCP_BASE_NETWORK_SYSTEM`）。

选项与扩展点：
- `OptionsSetter`：通过 `pro_s_options_setter()` 获取静态默认实例并对新连接进行验证或初始化，返回 `bool` 决定是否接纳该连接。
- `Error_Maker`：用于将内部错误映射为 `exception::exception` 所需的错误对象。

线程与生命周期注意：
- 内部使用 `safe_backup_device` 将待接受的连接临时保存在容器中，配合 `id_type` 在回调中关联；析构时断言备份容器为空以确保正确关闭与清理。
- `listen()` 在每次 accept 回调开始时都会再次调用以确保持续接收（边接受边启动下一个 accept）。

示例（伪代码）：

```cpp
ServicePool pool = ...;
auto acceptor = make_shared<MyAcceptor>(...);
SessionMgrWrap smgr_wrap = ...;
tcp_async_acceptor_handler<ServicePool, MyAcceptor, SessionMgrWrap, MyOptionsSetter, MyErrorMaker> handler(pool, acceptor, smgr_wrap, {});
handler.listen();

// 在需要停止时
handler.close();
```

注意事项：
- `Acceptor` 与 `conn_type` 需要按项目约定提供 `get_link()`、`get_init_object()`、`get_link()` 等接口。
- `session_mgr_wrap_type` 的 `get_shared_ptr()` 应返回有效的会话管理器指针，否则新连接无法被插入。
- 构造/分配失败、选项设置失败会导致对应连接被关闭以避免资源泄露。

文件： [yggr/network/session_helper/tcp_async_acceptor_handler.hpp](tcp_async_acceptor_handler.hpp)
