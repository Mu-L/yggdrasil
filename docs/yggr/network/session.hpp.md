# session.hpp

概述
- 提供 `session<...>` 模板类，用于封装网络连接会话（server/client）。
- 负责连接生命周期、收发包、适配器分发、数据检查与加密、状态修复与定时器等。

模板参数
- `Tag`：标识会话类型（必须为 server 或 client）。
- `Conn`：连接（connection）类型，需实现 `send_packet`/`recv_packet` 等接口。
- `Adapter_Mgr`：适配器管理器类型，负责将接收到的数据派发到上层处理器。
- `PacketsChecker`：数据包检查器，提供 `operator()(packet)` 返回错误或无错。
- `PacketsCrypher`：包加解密器，提供 `encrypt`/`decrypt`/`restore_info` 等。
- `First_Action`：首次动作处理策略类型（可选，用于连接建立后需要执行的操作）。
- `State_Fixer`：会话状态修复/检查器类型，提供 `fix_packet`、`check` 等方法。
- `Mutex`：用于线程同步的互斥类型（默认值可见实现）。

关键类型别名
- `id_type`：会话 ID 类型（封装为 `id_wrap`）。
- `conn_ptr_type`、`adapter_mgr_ptr_type`：连接与适配器管理器的 shared_ptr。
- `send_data_type` / `recv_data_type`：发送/接收的数据包类型。
- `endpoint_type`：底层 endpoint 类型（地址/端口）。

主要构造与初始化
- 构造函数接受 `id_start_value`（可选），并通过 `id_wrap`/`conn_wrap`/`adapter_mgr_wrap`/`packets_*_wrap` 等进行初始包装。
- 对 `Tag` 做静态断言以确保为 server/client。

主要公有方法（概要）
- get_id(), compare_eq(id), is_open(), is_connected(): 会话状态与 ID 访问。
- start(), close(close_code): 启动/关闭会话（关闭会触发错误报告与清理）。
- hold_recv(), stop_recv(): 控制是否继续接收。
- set_option / get_option: 连接选项代理。
- deadline_timer 相关: `start_timer`, `cancel_timer`, `get_deadline_timer` 等控制定时器。
- local/remote endpoint：`local_endpoint()`, `remote_endpoint()` 及地址/端口/字符串转换辅助函数。
- update_remote_endpoint(addr, port) / update_remote_endpoint(endpoint)：更新远端地址。

发送/接收 API
- `send_packet(netinfo, data)`：将 `netinfo` 和 `data` 封装为 `send_data_type` 并发送。
- `send_packet(send_data_type&, handler?)`：支持带回调的发送重载。
- `prv_send_packet_helper`：将发送委托到底层 `conn`。
- `prv_recv_packet_helper`：从连接异步接收并绑定到 `handler_recv`。

适配器交互
- `send_to_adapter(recv_data_type&)`：在接收包通过检查与解密后，将包交给 `Adapter_Mgr::send`。
- `handler_adapter_mgr_recv`：适配器产生要发送到远端的包时被调用并转发为 `send_packet`。

数据校验与加解密（私有）
- `prv_fix_send_opacket(send_data_type&)`：更新时间、检查包（PacketsChecker），再调用 `encrypt`。
- `prv_fix_recv_ipacket(recv_data_type&)`：对接收包调用 `PacketsChecker`，再 `decrypt` 并 `restore_info`。

错误与异常处理
- 使用 `error_maker_type` 生成错误，并通过 `prv_s_throw_error` 抛出（包含系统代码与会话 ID）。
- `handler_close_level_error()` 在检测到严重状态时统一触发会话关闭错误。

回调处理
- `handler_send` / `handler_recv`：分别处理底层发送/接收完成逻辑，发生错误时调用 `prv_s_throw_error`。
- 支持将用户提供的回调封装为 `args_holder` 并在发送完成后调用。

私有成员（概要）
- `_id_wrap`, `_conn_wrap`, `_adp_mgr_wrap`, `_packets_checker_wrap`, `_packets_crypher_wrap` 等包装成员。
- `_local_endpoint_wrap`, `_remote_endpoint_wrap`：本地/远端 endpoint 包装。
- `_state_fixer_wrap`：状态修复器包装。

非成员比较运算
- 提供多态的 `operator==` / `operator!=`，支持 `session` 与 `id_type`、或不同模板参数的 `session` 之间的比较，均委托 `compare_eq`。

示例（伪代码）
- 创建并启动会话：

```cpp
typedef session<client_tag, MyConn, MyAdapterMgr, MyChk, MyCryp, MyFirst, MyFixer> my_session;
boost::shared_ptr<my_session> s = boost::make_shared<my_session>(start_id);
s->start();
// 发送数据
s->send_packet(netinfo, payload);
```

注意事项
- `Tag` 必须为库中定义的 server/client 标签类型。
- 依赖：底层 `Conn` 必须实现异步发送/接收接口；`PacketsChecker`/`PacketsCrypher` 与 `Adapter_Mgr` 必须按约定行为实现。
- 文件实现涉及大量 `safe_wrap` 包装，用于线程安全访问与生命周期管理。

参考文件
- 头文件：session.hpp（实现复杂，建议直接阅读以获取完整细节）


----
自动生成：基于 yggr/network/session.hpp 阅读挖掘的概要文档。
