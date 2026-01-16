# network_data_id_def.hpp 文档

## 概述
- 文件： [yggr/network/network_data_id_def.hpp](yggr/network/network_data_id_def.hpp#L1-L200)
- 描述：定义网络数据 ID 的常量起始值，用于为用户自定义的数据类型分配唯一 ID 范围。
- 目的：提供统一的起始偏移量，避免与库或系统保留 ID 冲突。

## 内容摘要
源码只包含一个简单的 struct：

```cpp
struct network_data_def
{
    YGGR_STATIC_CONSTANT(u32, E_user_id_start = 0x10000000);
};
```

- `E_user_id_start`：类型为 `u32` 的静态常量，值为 `0x10000000`（十进制 268435456）。

## 语义与用途
- 该常量表示用户可用的网络数据 ID 的起始值（即用户自定义 ID 应从该值开始或在此基础上偏移）。
- 在协议、消息或序列化框架中，可使用该常量来区分内置/系统级 ID 与用户扩展 ID，避免冲突。

## 示例
- 直接使用：

```cpp
using yggr::network::network_data_def;
u32 my_id = network_data_def::E_user_id_start + 1; // 用户自定义第一个 ID
```

- 在注册系统中检查：

```cpp
if(id >= network_data_def::E_user_id_start) {
    // 这是用户自定义的 ID
}
```

## 注意事项
- 常量定义位于 `yggr::network` 命名空间内；引用时请注意命名空间或使用 `using`。
- 如果项目中存在多个模块定义自己的用户 ID 范围，请确保各模块使用不同偏移或通过集中注册表管理以避免重叠。

## 参考
- 源码： [yggr/network/network_data_id_def.hpp](yggr/network/network_data_id_def.hpp#L1-L200)

---
