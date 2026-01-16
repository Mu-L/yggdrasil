**tcp_connect_handler.hpp 文档**

简介：
- `tcp_connect_handler` 是用于发起主动 TCP 连接并在连接成功后将连接插入会话管理器的辅助类。它基于 `basic_tcp_connect_handler` 提供地址解析、重试与超时处理逻辑，并在成功连接后进行选项验证与会话管理器注册。

模板参数：
- `ServicePool`：提供 `service_type`（io_service / io_context）的服务池类型。
- `SessionMgrWrap`：会话管理器封装类型，需提供 `value_ptr_type`、`get_shared_ptr()` 与 `value_type::conn_ptr_type` 等。
- `OptionsSetter`：连接选项设置/验证类型，需提供 `operator()(conn)` 返回 `bool`。
- `Error_Maker`：错误生成器类型，需提供 `error_type` 与 `make_error()` 以及若干 `E_*` 错误码。

主要类型别名：
- `conn_type`、`conn_ptr_type`：会话使用的连接类型与其指针。
- `base_type`：`basic_tcp_connect_handler<conn_ptr_type>`，提供静态连接接口 `s_connect`。

主要方法与行为：
- 构造：`tcp_connect_handler(service_pool_type& service_pool, session_mgr_wrap_type& smgr_wrap, const init_type&)`。
- `connect(addr, port)` 与 `connect(addr, port, timeout)`：
  - 分配 `conn_type` 实例（使用 `_service_pool.get_service()`），若分配失败则通过 `pro_s_throw_error` 抛错并返回。
  - 调用 `base_type::s_connect` 发起异步连接，完成后回调 `pro_handler_connect`（重载带超时的版本会传入 `tm_duration`）。
- `pro_handler_connect(const boost::system::error_code& e, conn_ptr_type pconn)`：连接完成处理逻辑。
  - 若 `pconn` 为空则抛错并返回 `false`（停止连接流程）。
  - 若连接成功（`!e`）：先通过 `pro_s_options_setter()(*pconn)` 进行选项验证，若失败则关闭连接并抛错；随后获取 `session_mgr_ptr_type smgr_ptr = _smgr_wrap.get_shared_ptr()`，若有效则调用 `smgr_ptr->insert(pconn)` 将连接插入管理器并返回 `false`（表示停止重试）；若 `smgr_ptr` 无效则关闭连接并抛错。
  - 若连接出错（e 有值），调用 `pro_s_throw_error(e, E_TCP_BASE_NETWORK_SYSTEM)` 并返回 `true`（触发 `basic_tcp_connect_handler` 的重试机制）。
- `close()`：清理并关闭所有备份连接（通过 `base_type::clear_backup` 调用 `pro_s_handler_clear_backup`）。

错误与选项处理：
- 使用 `options_setter_type` 进行连接后的验证或初始化，控制是否接纳该连接。
- 错误通过 `error_maker_type::make_error(...)` 构造并交由 `exception::exception::throw_error` 抛出，部分携带系统码 `E_TCP_BASE_NETWORK_SYSTEM`。

线程与生命周期：
- 内部使用 `basic_tcp_connect_handler` 的备份容器在发起异步连接时保存 `conn_ptr`，以便在回调时安全获取并管理连接生命周期；析构时断言备份容器为空以确保资源已清理。

示例（伪代码）：

```cpp
tcp_connect_handler<ServicePool, SessionMgrWrap, OptionsSetter, ErrorMaker> handler(pool, smgr_wrap, {});
handler.connect("example.com", "80");
// 或带超时时间
handler.connect("example.com", "80", boost::posix_time::seconds(5));
```

注意事项：
- `SessionMgrWrap::get_shared_ptr()` 必须返回会话管理器指针，且该管理器需实现 `insert(conn_ptr)`。
- `conn_type` 的构造与 `get_service()` 需与 `ServicePool` 的 `service_type` 兼容。
- `pro_handler_connect` 返回值约定：返回 `true` 表示在出错时继续连接（触发重试），返回 `false` 表示停止重试（如成功或不可恢复错误）。

文件： [yggr/network/session_helper/tcp_connect_handler.hpp](yggr/network/session_helper/tcp_connect_handler.hpp)
