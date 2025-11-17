# `yggr::network::network_config::network_direct_def`（文件：`network_direct_def.hpp`）

## 概述
- 目的：定义网络适配器方向（发送/接收/双向）相关的常量别名，便于在网络配置或适配器注册处使用统一的标志。
- 位置：`yggr/network/network_config/network_direct_def.hpp`（本文档与源文件同目录）。
- 背景：常量基于 `yggr::adapter::adapter_register_type_def` 中的枚举值，用于表示适配器在数据流向（从源/到源/双向）上的能力。

## 主要类型与常量
在 `network_direct_def` 结构中定义了三个静态常量：
- `E_send_enable`：映射到 `adapter::adapter_register_type_def::E_from_src`。表示允许“从源发送”（send enabled）。
- `E_recv_enable`：映射到 `adapter::adapter_register_type_def::E_to_src`。表示允许“到源接收”（recv enabled）。
- `E_both_enable`：映射到 `adapter::adapter_register_type_def::E_both`。表示双向同时启用。

此外，文件在 `yggr::network` 命名空间中提供了一个类型别名：
- `typedef network_config::network_direct_def network_direct_def_type;`

这些常量用于注册/配置适配器时指示数据流向权限或能力。

## 使用示例（伪代码）
```cpp
using yggr::network::network_config::network_direct_def;

// 检查是否启用发送
if(flags & network_direct_def::E_send_enable) {
    // 进行发送相关注册或初始化
}

// 在注册适配器时使用
adapter_register.register_adapter(adapter_obj, network_direct_def::E_both_enable);
```

## 注意事项
- 这些常量只是对 `adapter::adapter_register_type_def` 中定义值的重命名/转发；若 `adapter_register_type_def` 中的值发生变更，`network_direct_def` 的语义也会随之变化。
- 在跨模块使用时，优先直接参考 `adapter_register_type_def` 的定义以确保语义准确，`network_direct_def` 主要作为方便的别名以利于网络模块使用。

