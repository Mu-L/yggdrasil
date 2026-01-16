# network_handler.hpp 文档

## 概述
- 文件： [yggr/network/network_handler.hpp](yggr/network/network_handler.hpp#L1-L400)
- 描述：`network_handler` 是对操作处理器（`OP_Handler`）与服务管理器（`service_handler_type`）的组合封装，协调服务信号处理、运行/停止流程、协议注册与数据发送接口。适用于集中管理网络服务生命周期与消息分发的场景。

## 模板参数与相关类型
- 模板参数：`OP_Handler` — 提供网络协议注册、会话管理、发送/访问接口以及控制器注册机制。
- 主要类型别名：
  - `op_handler_type`：模板参数类型。
  - `service_handler_type`：由 `op_handler_type::service_handler_type` 定义。
  - `service_handler_init_type`、`op_handler_init_type`：各自的初始化类型。
  - `adapter_mgr_type`、`adapter_mgr_ptr_type`：适配器管理器类型与指针。

## 构造与析构
- 构造函数：

```cpp
template<typename Service_Handler_Init, typename OP_Handler_Init>
network_handler(const Service_Handler_Init& service_init,
                const OP_Handler_Init& svr_init)
    : _brun(false),
      _service_handler(service_init),
      _op_handler(_service_handler, const_cast<OP_Handler_Init&>(svr_init)) {}
```

- 析构函数断言 `_brun` 为 false，表示在销毁前应确保已停止运行。

## 主要功能/方法
- 协议注册/注销：
  - `register_network_protocol<Real_Data>(u32 stat)`
  - `register_network_protocol_of_container<Real_Data, Container>(u32 stat)`
  - `register_network_protocol<Container>(send_id, recv_id, u32 stat)`
  - `unregister_network_protocol<Real_Data>(u32 stat)`
  - `unregister_network_protocol<ID>(id, tag, stat)`

这些方法均委托给 `_op_handler` 实现。

- 信号与生命周期管理：
  - `add_signal(u32 sig)`：向 `service_handler` 添加信号监听。
  - `run()` / `run(handler)`：
    - 使用原子 `_brun` 防止重复启动。
    - 自动注册常见信号（`SIGINT`, `SIGTERM`, 平台相关的 `SIGBREAK`, `SIGSTOP` 等）并设置信号处理回调（默认调用 `stop()`，或使用传入 `handler`）。
    - 启动 `_op_handler.run()` 与 `_service_handler.run()`（顺序为先 OP 再 Service）。
    - 最后断言 `_brun` 与 `_service_handler.is_running()` 状态一致。
  - `stop()`：
    - 原子切换 `_brun` 为 false，调用 `_service_handler.stop()` 与 `_op_handler.stop()`。
    - 移除之前添加的信号并取消信号处理回调。

- 会话与发送接口：
  - `online_size()`：返回在线会话数量，委托 `_op_handler.online_size()`。
  - `clear_sessions()`、`clear()`：委托 `_op_handler`。
  - `send_packet(...)`：多重模板重载，支持按键/网络信息/数据/处理器发送，或直接发送已构造包。
  - `access(...)`：提供对会话的访问接口，支持按键或无键的处理器回调，并保留返回值类型推导。

- 其它：
  - `service_handler()` / `op_handler()`：返回内部引用。
  - `check_state()`：委托 `_op_handler.check_state()`。
  - `get_adapter_mgr_ptr()`：返回适配器管理器指针。
  - `register_controller<Tag>(CtrlCenter&)`：私有，供 `yggr::system_controller::ctrl_center` 使用以注册控制器。

## 实现细节与异常安全
- 内部使用 `boost::atomic<bool> _brun` 管理运行状态。
- 构造中通过 `const_cast` 传递 `svr_init` 给 `_op_handler`（注意这可能引入异常/别名语义问题，需确保传入的 `svr_init` 在生命周期内有效）。
- `run()` 在设置信号回调后先调用 `_op_handler.run()` 再调用 `_service_handler.run()`，反向顺序在 `stop()` 中对两个组件调用 `stop()`。

## 使用示例
```cpp
// 假设已定义 OP_Handler 和相应的初始化类型
ServiceHandlerInit sh_init = /* ... */;
OPHandlerInit op_init = /* ... */;
network_handler<OP_Handler> nh(sh_init, op_init);

nh.register_network_protocol<MyMessage>();
nh.run();
// ... 运行期间通过 nh.send_packet(...) 分发消息
nh.stop();
nh.join(); // 可通过 service_handler().join() 或直接访问
```

## 注意事项
- 在销毁 `network_handler` 前，必须确保 `stop()` 已被调用并等待服务停止，否则析构断言会触发。
- `register_network_protocol` 等模板函数完全委托给 `_op_handler`，使用前请参阅 `OP_Handler` 的文档以了解具体约定（例如 ID/tag 语义、容器支持）。
- 信号注册涉及平台差异（Windows/Android），使用自定义 `run(handler)` 可提供自定义信号处理逻辑。

## 参考
- 源码： [yggr/network/network_handler.hpp](yggr/network/network_handler.hpp#L1-L400)

---
