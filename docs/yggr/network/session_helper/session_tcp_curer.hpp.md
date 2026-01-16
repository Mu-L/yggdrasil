**session_tcp_curer.hpp 文档**

简介：
- `session_tcp_curer` 是基于 `basic_tcp_connect_handler` 的策略型函数对象，用于在会话管理器中恢复或替换 TCP 连接。通常在会话迁移、故障恢复或重新连接场景下使用。

模板参数：
- `Session`：会话类型，要求提供 `conn_ptr_type`、`conn_type` 等类型别名，以及 `get_conn_ptr()` 等接口。

继承与职责：
- 继承自 `basic_tcp_connect_handler<typename Session::conn_ptr_type>`，因此可以使用其静态方法 `s_connect` 发起异步 TCP 连接并处理重试/超时逻辑。

主要行为：
- 提供两个重载 `operator()`：
  - `operator()(const Key& key, Session_Mgr& smgrt)`：在会话管理器中按 `key` 查找并移除（`drop`）会话指针，尝试用新的连接替换并插入管理器，然后关闭原会话。
  - `operator()(conn_ptr_type pconn, Session_Mgr& smgrt)`：直接以给定连接指针作为被替换/恢复目标，发起新的连接并在成功时插入管理器。

内部流程要点：
- `prv_operator_helper(key, psmgr)`：从 `psmgr` 调用 `drop(key)` 获取 `session_ptr`，若存在则取出其 `conn_ptr` 并交由 `prv_operator_helper(pconn, psmgr)` 处理，最后对旧会话调用 `close()`。
- `prv_operator_helper(pconn, psmgr)`：基于传入的 `pconn` 构造一个新的 `conn_type` 实例 `new_pconn`（使用 `pconn->get_init_object()`），然后调用 `base_type::s_connect` 发起异步连接，连接成功后通过 `s_new_handler_connect` 将 `new_pconn` 插入 `psmgr`。
- `s_new_handler_connect`：当新连接成功（`!e`）时调用 `psmgr->insert(pconn)` 并返回 `false`（表示不再重试）；在错误情况下返回 `true`（触发 `basic_tcp_connect_handler` 的重试机制）。

类型安全与断言：
- 使用 `BOOST_MPL_ASSERT` 与 `boost::is_same` 确保 `session_mgr_type::session_type` 与传入的 `Session` 类型一致，防止类型不匹配的误用。

示例（伪代码）：

```cpp
using curer = yggr::network::session_helper::session_tcp_curer<MySession>;
curer c;

// 通过 key 恢复会话连接
c(some_key, session_mgr);

// 或直接以旧连接尝试替换/恢复
c(old_conn_ptr, session_mgr);
```

注意事项：
- `Session_Mgr` 需提供 `drop(key)`（返回 `session_ptr_type`）与 `insert(conn_ptr)` 接口。
- `conn_type` 必须提供 `get_init_object()`、`str_remote_address<std::string>()`、`str_remote_port<std::string>()` 等方法以支持新连接的创建与目标地址获取。
- 该组件依赖 `basic_tcp_connect_handler` 的行为（包括重试与超时），因此其回调签名和超时逻辑应与 `basic_tcp_connect_handler` 的约定一致。

文件： [yggr/network/session_helper/session_tcp_curer.hpp](session_tcp_curer.hpp)
