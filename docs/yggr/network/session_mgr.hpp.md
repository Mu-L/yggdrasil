# session_mgr.hpp 文档

## 概述
- 文件： [yggr/network/session_mgr.hpp](yggr/network/session_mgr.hpp#L1-L663)
- 描述：`session_mgr<Session, Start_Mode, State_Checker, Exception_Fixer>` 管理一组 `Session` 实例（通过 `safe_unordered_map` 存储），负责会话创建、插入、移除、遍历、发送、以及与适配器（`adapter_mgr`）的交互。它支持不同的启动模式、状态检查和异常修复策略，通过模板参数实现高度可定制化。

## 模板参数
- `Session`：会话类型，需要定义诸如 `id_type`, `protocol_tag_type`, `service_type`, `socket_type`, `send_data_type`, `recv_data_type`, `owner_id_parser_type` 等别名与成员。
- `Start_Mode`：启动模式策略类型，用于在新连接到来时创建并启用 `Session`（例如 TCP accept、UDP 关联、P2P 等）。`Start_Mode` 应实现 `operator()(conn_ptr_type, session_mgr&)`。
- `State_Checker`：用于检查会话状态的策略（提供 `operator()(cont_type&)` 或带回调的变体）。
- `Exception_Fixer`：异常处理/修复策略类型，用于在会话创建或运行时出现异常时处理（`operator()(key, session_mgr&)`）。

## 关键类型别名
- `session_ptr_type`：`yggr::shared_ptr<Session>`。
- `key_type`：`Session::id_type`。
- `smap_type`：`safe_unordered_map<key_type, session_ptr_type>`，用于存储会话。
- `adapter_mgr_type` / `adapter_mgr_ptr_type`：会话使用的适配器管理器类型与智能指针。
- `send_data_type` / `recv_data_type`：用于发送/接收的数据类型。

## 构造与析构
- 构造可接受 `adapter_src_type&` 或 `adapter_mgr_ptr_type`，并封装到内部 `_adp_mgr_wrap`。
- 析构断言 `_smap` 为空（要求在销毁前清理所有会话）。

## 会话生命周期管理
- `insert(conn_ptr_type pconn)`：使用默认或传入的 `start_mode` 创建并插入会话（`start_mode(pconn, *this)`）。
- `remove(const key_type& key)`：查找并移除会话，若找到则调用 `close()` 并返回 true。
- `drop(const key_type& key)`：从内部容器中移除并返回 `session_ptr_type`，但不关闭会话。
- `create_session_only(const boost::system::error_code& e, const Creator& creator)`：内部创建会话的工厂函数，处理错误码并与 `_smap` 交互；若出现错误，调用 `exception_fixer` 并抛出系统异常。

## 会话集合操作
- `clear_sessions()`：关闭并清空所有会话（但保留适配器管理器）。
- `clear()`：关闭并清空所有会话，并调用 `adapter_mgr.clear()`。
- `empty()`, `size()`：查询会话数量。

## 协议/适配器注册
- `register_adapter<Real_Data>(u32 stat)`、`register_adapter_of_container<Real_Data, Container>(u32 stat)`、`register_adapter(Container, send_id, recv_id, u32 stat)`：委托 `adapter_mgr` 进行注册。
- 对应的 `unregister_adapter` 可按类型或 ID 注销适配器。

## 发送与访问接口
- `send_packet(key, netinfo, data)` / `send_packet(key, pak, handler)` / `send_packet(key, pak)`：查找目标会话并委托其 `send_packet`。
- `access(key, handler)`：在找到会话时执行传入的 `handler`（通过内部 `smap.find` 与 wrap-helper 调用）。
- `access(handler)` / `access(handler) const`：对整个 map 使用 `using_handler`。
- `access_of_all(handler)`：对所有会话迭代并调用 handler。
- `send_to_adapter(recv_data_type& pak)`：将接收到的数据转发给对应会话的 `send_to_adapter`。

## 状态检查与清理
- `check_state()`：将当前 `_smap` 内容拷贝到本地 `cont_type` 并调用 `state_checker_type::operator()(cont)`。
- `check_state(handler)`：带回调版本。

## 异常处理
- 内部定义错误码（`E_invalid_session`, `E_duplication_id`）并使用 `exception::exception::throw_error` 抛出错误。
- `handler_session_exception(const key_type& key)` 会通过 `exception_fixer` 处理异常。

## 内部辅助函数
- `prv_s_handler_find_session_ref` / `prv_s_handler_find_session_cref`：用于 `smap.find` 的回调封装，支持传入通用 `Handler` 封装类型。
- `prv_s_throw_error`：辅助抛出异常的包装函数。

## 线程与并发
- `_smap` 是线程安全的 `safe_unordered_map`，允许并发访问与安全查找/遍历。
- 许多操作通过 `get_shared_ptr` 与本地副本进行，以降低并发问题。

## 使用示例
```cpp
typedef my_session session_t;
typedef session_mgr<session_t, my_start_mode, my_state_checker, my_exception_fixer> sess_mgr_t;

sess_mgr_t mgr(adp_src);
// 在 accept 回调中：
mgr.insert(conn_ptr);

mgr.send_packet(sid, netinfo, data);
mgr.check_state();
mgr.clear_sessions();
```

## 注意事项
- `Session` 类型必须满足接口契约（ID、send_packet、close、create 等）。
- 在调用 `insert` 时，如果 `adapter_mgr` 不可用，方法会返回且不会插入。
- `create_session_only` 在错误时会调用 `exception_fixer` 并抛出异常；请提供合适的 `Exception_Fixer` 实现以处理并恢复错误情况。

## 参考
- 源码： [yggr/network/session_mgr.hpp](yggr/network/session_mgr.hpp#L1-L663)
