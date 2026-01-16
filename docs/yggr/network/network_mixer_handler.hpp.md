# network_mixer_handler.hpp 文档

## 概述
- 文件： [yggr/network/network_mixer_handler.hpp](yggr/network/network_mixer_handler.hpp#L1-L2194)
- 描述：`network_mixer_handler` 提供一个可组合的“混合”网络处理器框架，允许将多个不同类型的 OP 处理器（`OP_Handler`）按类型分类并统一管理。它封装服务生命周期（run/stop）、信号处理、适配器注册、会话管理（在线数量、清理）以及跨多个处理器的消息发送和访问分发。

## 设计要点
- 使用 Boost.MPL 与模板元编程在编译期生成针对多个处理器类型的容器和操作序列。
- 每个处理器类型在内部映射为一个线程安全的 `safe_list` 容器，容器元素为对应处理器的 `shared_ptr`。
- 通过 `value_wrap`（`safe_wrap<tuple_of_containers>`）保存所有处理器容器，以实现线程安全的读写与原子交换。
- 支持按类型索引（模板参数）或按位置调用指定子处理器集合的操作（`using_method`）。

## 模板参数
- `ServiceHandler`：服务管理器类型，负责信号、运行与停止等。
- `Adapter_Mgr`：适配器管理器类型，用于协议注册/注销与适配器相关操作。
- `Mutex`（可选）：用于 `safe_list` 的互斥策略（默认 `void` 表示内部选择）。
- `Vals...`：可变参数列表，代表需要混合管理的 `OP_Handler` 类型集合（可在末尾用 `yggr::tuples::null_type` 作为终止符）。

## 主要类型别名
- `adapter_mgr_type` / `adapter_mgr_ptr_type`
- `params_type`：为每个 `OP_Handler` 生成的容器类型集合（`safe_list` 的 shared_ptrs）。
- `value_type`：从 `params_type` 转换而来的 yggr 元组类型，封装在 `value_wrap_type` 中。

## 主要功能
- 协议注册/注销：委托 `adapter_mgr_type` 进行 `register_adapter` / `unregister_adapter` 等操作。
- 生命周期管理：
  - `run()` / `run(handler)`：原子设置 `_brun`，注册信号，触发内部每个处理器的 `run()`，并调用 `_service_handler.run()`。
  - `stop()`：原子切换 `_brun`，调用 `_service_handler.stop()`，并对每个处理器调用 `stop()`，移除信号处理。
  - `join()`：委托 `_service_handler.join()`。
- 会话与清理：
  - `online_size()`：累加各个子处理器的 `online_size()`。
  - `clear_sessions()`：对每个处理器调用 `clear_sessions()`。
  - `clear()`：对每个处理器调用 `clear()`。
- 发送与访问：
  - `send_packet(...)`：三个重载，支持按 key/netinfo/data/handler 或 key/pak/handler 或 key/pak；操作会遍历每个子处理器容器，直到某个处理器成功发送为止。
  - `access(...)` / `access_of_all(...)`：对单个或所有子处理器执行访问回调。
- 动态追加处理器实例：
  - `append<OP_Handler>(lkh_init, port)`：在对应容器中构造并添加新的 `OP_Handler` 实例（会使用内部 `adapter_mgr` 与 `service_handler` 初始化），若服务正在运行则立即调用该处理器的 `run()`。
- 按类型/索引的自定义调用：
  - `using_method<i>(handler)` 或 `using_method<Val_T>(handler)`：针对第 i 个或类型为 `Val_T` 的子处理器集合执行传入 `handler`。
- 控制器注册：
  - 私有 `register_controller<Tag>(CtrlCenter&)` 被 `yggr::system_controller::ctrl_center` 友元调用以注册控制器至子处理器。

## 实现细节
- 大量模板递归结构（`*_op` 模板）用于在编译期对每个子处理器容器生成对应操作（run/stop/send/access/clear/register_controller 等），以避免运行时类型分支。
- 使用 `safe_wrap` 与 `safe_list` 提供并发安全访问：大多数操作通过 `value_wrap.get_shared_ptr()` 获取当前快照并对快照遍历。
- `append` 采用 MPL 查找对应容器索引并在运行时构造对应 `OP_Handler` 实例并 push_back 到容器。
- 信号注册/移除在 `pro_add_signal` / `pro_remove_signal` 中集中管理，兼容 Windows/Android 等平台的特定信号。

## 断言与静态检查
- 在编译期通过 `BOOST_MPL_ASSERT` 检查模板参数集合中 handler 类型唯一性等约束。
- 运行期使用 `assert` 检查指针有效性与前置条件。

## 依赖
- Boost：MPL、thread、asio、functional/hash 等。
- yggr 内部工具：`safe_container`、`tuple`、`mplex` 工具、`serialization`、`smart_ptr_ex/shared_ptr` 等。

## 使用示例（简化）
```cpp
// 定义混合管理器，管理 HandlerA 和 HandlerB
network_mixer_handler<ServiceHandler, AdapterMgr, void, HandlerA, HandlerB> mixer(sh_init, adapter_src);

// 追加运行时实例
mixer.append<HandlerA>(lkh_init_a, port_a);
mixer.append<HandlerB>(lkh_init_b, port_b);

mixer.run();
// 发送数据，内部会遍历各 Handler 容器并尝试发送
mixer.send_packet(key, netinfo, data, handler);

mixer.stop();
```

## 注意事项与建议
- 模板元编程复杂，确保传入的 `Vals...` 中类型互不重复并且每个类型满足 OP handler 接口契约（例如提供 `run()`, `stop()`, `send_packet()`, `access()` 等）。
- `append` 对于构造失败或 `adapter_mgr` 不可用会返回 `false`，调用者应检查返回值。
- 运行时操作遍历所有子处理器容器，代价随子处理器数量线性增长；选择合理的 `Vals` 数量和容器分配策略以优化性能。

## 参考
- 源码： [yggr/network/network_mixer_handler.hpp](yggr/network/network_mixer_handler.hpp#L1-L2194)

---
