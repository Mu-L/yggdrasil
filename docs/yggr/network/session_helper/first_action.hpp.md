**first_action.hpp 文档**

简介：
- `first_action` 是一个小型函数对象（functor），用于会话（Session）在建立/激活后的第一次动作。通常在连接建立后被调用以触发初始发送并启动接收循环。

用途：
- 在会话成功关联连接对象后，执行首个发送操作（`next_send()`），并设置后续的接收回调（`prv_recv_packet_helper`），确保会话开始正常的数据收发流程。

要求与约定：
- `Session` 模板参数须满足以下接口：
  - `conn_ptr_type`：连接指针类型。
  - `get_conn_ptr()`：返回当前连接指针（`conn_ptr_type`）。
  - `handler_close_level_error()`：当无法获得有效连接时调用的错误处理回调。
  - `prv_recv_packet_helper(tuple)`：内部方法，用于注册接收回调，参数为一个包含接收处理和错误处理的 tuple。
  - `handler_recv(...)`：接收数据的回调函数，签名在 `prv_recv_packet_helper` 中被绑定为 `&session_type::handler_recv`。
  - `shared_from_this()`：Session 支持 enable_shared_from_this，用于绑定成员函数时获取 `shared_ptr`。

行为说明（步骤）：
- 获取连接指针：调用 `s.get_conn_ptr()`。
- 连接不存在：若返回空指针，调用 `s.handler_close_level_error()` 并返回。
- 首次发送：对连接调用 `ptr->next_send()`，触发会话首次发送（可能是握手或心跳等）。
- 启动接收：调用 `s.prv_recv_packet_helper(...)` 并绑定两个回调：
  - 第一个：`session_type::handler_recv`（接收处理），绑定 `s.shared_from_this()` 和两个占位符 `_1, _2`。
  - 第二个：`session_type::handler_close_level_error`（错误处理），绑定 `s.shared_from_this()`。

实现细节：
- `prv_recv_packet_helper` 接受的 tuple 使用了 `yggr::make_tuple` 与 `boost::bind` 来封装成员函数回调。

示例（伪代码）：

```cpp
// Session 类型需实现库中约定的方法
struct MySession : std::enable_shared_from_this<MySession> {
    using conn_ptr_type = std::shared_ptr<MyConn>;
    conn_ptr_type get_conn_ptr();
    void handler_close_level_error();
    void handler_recv(...);
    void prv_recv_packet_helper(...);
};

MySession s;
yggr::network::session_helper::first_action act;
act(s); // 执行首次动作：发送并开始接收
```

注意事项：
- `first_action` 假定 `Session` 的生命周期由 `shared_ptr` 控制且 `shared_from_this()` 可用，否则绑定成员函数可能导致未定义行为。
- `ptr->next_send()` 的具体行为由连接类型实现，可能触发实际发送或将数据放入发送队列。

文件： [yggr/network/session_helper/first_action.hpp](first_action.hpp)
