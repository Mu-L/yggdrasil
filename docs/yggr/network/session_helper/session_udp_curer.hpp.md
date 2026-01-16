**session_udp_curer.hpp 文档**

简介：
- `session_udp_curer` 基于 `basic_udp_connect_handler`，用于在会话管理器中恢复或替换 UDP 类型的“连接”（会话的底层 UDP 套接字/对端信息）。典型场景包括会话迁移、重绑定或恢复会话的对端信息。

模板参数：
- `Session`：会话类型，要求提供 `conn_ptr_type`、`conn_type`、以及 `task_type::owner_info_type` 等成员类型。

继承与职责：
- 继承自 `basic_udp_connect_handler<typename Session::conn_ptr_type, typename Session::task_type::owner_info_type>`，因此可以使用其 `s_connect` 发起发送检测包并执行重试/超时逻辑以确认 UDP 对端可达性。

主要行为：
- 提供两个重载 `operator()`：
  - `operator()(const Key& key, Session_Mgr& smgrt)`：从会话管理器中按 `key` `drop` 出旧会话，取出其 `conn_ptr` 并尝试基于旧连接信息创建并检测新的 `conn`，完成后关闭旧会话。
  - `operator()(conn_ptr_type pconn, Session_Mgr& smgrt)`：直接以提供的 `pconn`（旧连接）为基础创建一个新的 `conn`，并通过 `base_type::s_connect` 发送检测包来确认新连接是否可用。

流程要点：
- `prv_operator_helper(key, psmgr)`：调用 `psmgr->drop(key)` 获取 `session_ptr`，若非空则取得其 `conn_ptr` 并交由 `prv_operator_helper(pconn, psmgr)`，最后关闭旧会话。
- `prv_operator_helper(pconn, psmgr)`：
  - 创建 `new_pconn`（使用 `pconn->get_init_object()` 与 `pconn->get_socket_destroyer()`），并在旧连接上调用 `pconn->clear_socket_destroyer()` 将套接字管理权移交给新连接。
  - 调用 `base_type::s_connect(new_pconn, remote_address, remote_port, handler)`，其中 `handler` 为 `s_new_handler_connect`，用于在检测成功时将 `new_pconn` 插入会话管理器（实现注：UDP 在这里通过发送检测包来确认对端可达性）。
- `s_new_handler_connect`：当回调时，如果 `psmgr` 无效则关闭 `pconn`；若 `pconn` 有效且 `e` 表示错误（非零）则返回 `true` 以触发重试；当前实现中在成功时不执行插入（留给上层逻辑或另一路径处理）。

类型与接口要求：
- `Session_Mgr` 需提供 `drop(key)`（返回 `session_ptr_type`）接口。
- `conn_type` 需要实现：
  - `get_init_object()`、`get_socket_destroyer()`、`clear_socket_destroyer()`
  - `template str_remote_address<std::string>()` 与 `template str_remote_port<std::string>()` 用于获取远端地址/端口字符串。

示例（伪代码）：

```cpp
using udp_curer = yggr::network::session_helper::session_udp_curer<MySession>;
udp_curer curer;

// 通过 key 恢复
curer(some_key, session_mgr);

// 或直接以旧连接恢复
curer(old_conn_ptr, session_mgr);
```

注意事项：
- UDP 为无连接协议，这里的“连接”更多是应用层的对端绑定与检测，`basic_udp_connect_handler` 通过发送“检测包”并等待响应来判断可达性。
- `prv_operator_helper` 将 socket 管理权从旧连接转移到新连接（通过 `get_socket_destroyer()` / `clear_socket_destroyer()`），使用时需确保套接字所有权的语义一致。
- `s_new_handler_connect` 的当前实现不会在成功回调中自动插入新会话（可能由设计者在其它路径处理），若需自动插入请在回调中调用 `psmgr->insert(pconn)`。

文件： [yggr/network/session_helper/session_udp_curer.hpp](session_udp_curer.hpp)
