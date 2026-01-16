# network_sender.hpp 文档

## 概述
- 文件： [yggr/network/network_sender.hpp](yggr/network/network_sender.hpp#L1-L200)
- 描述：`network_sender` 是一个小型适配器/函数对象模板，用于通过全局或单例 `NetEntity` 实例发送网络数据。它在发送前可选地调用 `Checker` 验证逻辑（默认为不做检查），并通过 `Getter` 获取目标 `NetEntity` 实例。

## 模板参数
- `NetEntity`：提供实际 `send_packet` 实现的实体类型（通常为连接/会话管理器或 OP handler）。
- `Checker`：发送前的检查器类型（默认为 `sender_checker::sender_non_checker`），其调用形式为 `chker(ptr, key, netinfo, data, handler)`，应返回 `bool`。
- `Mutex`：用于 `Getter` 的互斥策略类型（默认 `boost::shared_mutex`）。
- `version`：模板参数传递给 `Getter` 的版本号（默认为 0）。
- `Getter`：用于获得 `NetEntity` 单例/实例的模板（默认 `ptr_single`），应提供静态 `get_ins()` 返回 `obj_ptr_type`。

## 主要类型别名
- `net_entity_type`、`checker_type`。
- `getter_type`：`Getter<net_entity_type, Mutex, version>`。
- `net_entity_ptr_type`：由 `getter_type::obj_ptr_type` 定义的指针类型。

## 功能与用法
- `network_sender` 可作为函数对象，重载 `operator()` 支持三种发送形式：
  - `(key, netinfo, data, handler)`：发送含 `NetInfo` 与数据的包。
  - `(key, pak, handler)`：发送已构造包并提供回调处理器。
  - `(key, pak)`：发送已构造包且无需回调。
- 静态方法 `send_packet(...)` 实际执行：
  - 通过 `getter_type::get_ins()` 获取 `NetEntity` 指针。
  - 若指针有效，调用 `Checker` 执行检查；检查通过后调用 `ptr->send_packet(...)`。
- `non_handler_send`：一个空的静态回调，可用于不需要处理错误码时作为回调占位符。

## 行为细节
- 所有发送函数都首先构造 `checker_type` 的临时对象，然后获取 `NetEntity` 实例并按顺序检查指针与检查器的返回值，最后委托 `NetEntity` 执行发送。
- `Checker` 的接口应兼容三种发送签名（带/不带 `netinfo`、带/不带 `handler`），并在必要时使用 `ptr` 进行额外校验（例如是否在线、是否属于指定 Key 等）。
- `Getter` 需提供 `get_ins()` 静态函数以返回 `net_entity_ptr_type`。

## 示例
```cpp
// 假设 MyNetEntity 提供 send_packet 接口，且 ptr_single 已配置返回单例
network_sender<MyNetEntity> sender;
MyKey key; MyNetInfo info; MyData data;

sender(key, info, data, [](const boost::system::error_code& ec){ /* handle */ });

// 或者直接调用静态方法
network_sender<MyNetEntity>::send_packet(key, info, data, handler);
```

## 注意事项
- `NetEntity` 的生命周期与 `Getter` 的实现密切相关，确保 `get_ins()` 返回的指针在调用期间有效。
- 如果需要线程安全的动态实例获取，可以自定义 `Getter` 与 `Mutex`。
- 自定义 `Checker` 能增强发送前的校验（例如权限、状态或路由选择），提高健壮性。

## 参考
- 源码： [yggr/network/network_sender.hpp](yggr/network/network_sender.hpp#L1-L200)

---
