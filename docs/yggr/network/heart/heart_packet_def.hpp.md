# `yggr::network::heart::heart_packet_def`（文件：`heart_packet_def.hpp`）

## 概要
- **目的**：定义心跳相关的包 ID 范围（开始与结束常量），并提供用于在预处理/编译期检查包 ID 是否落在该范围内的宏 `YGGR_PP_CHECK_HEART_PACKET_ID`。
- **位置**：`yggr/network/heart/heart_packet_def.hpp`（与该文档同目录）
- **适用场景**：在注册/定义网络包（或任务包）时，用以保证心跳相关包 ID 在指定的保留区间内并便于宏式校验。

## 文件主要内容
```cpp
struct heart_packet_def
{
    YGGR_STATIC_CONSTANT(u32, E_id_start = 0x00008100);
    YGGR_STATIC_CONSTANT(u32, E_id_end   = 0x00008200);
};

#define YGGR_PP_CHECK_HEART_PACKET_ID( __id__ ) \
    YGGR_PP_IS_IN_RANGE(__id__, \
                        ::yggr::network::heart::heart_packet_def::E_id_start, \
                        ::yggr::network::heart::heart_packet_def::E_id_end )
```

- `E_id_start`：心跳包 ID 区间的起始值（包含）。
- `E_id_end`：心跳包 ID 区间的结束值（包含或按 `YGGR_PP_IS_IN_RANGE` 定义的语义）。
- `YGGR_PP_CHECK_HEART_PACKET_ID(__id__)`：调用 `YGGR_PP_IS_IN_RANGE` 宏判断 `__id__` 是否在 `[E_id_start, E_id_end]` 范围内。

> 注意：`YGGR_STATIC_CONSTANT` 与 `YGGR_PP_IS_IN_RANGE`、`YGGR_PP_CHECK_HEART_PACKET_ID` 等宏在项目其他头文件中定义；本文件依赖这些宏的正确实现。

## 用法示例
- 在定义心跳包时，使用宏检查 ID 是否在心跳保留区：
```cpp
// 假设在某处定义包时：
const u32 my_heart_pkg_id = 0x00008105;
static_assert(YGGR_PP_CHECK_HEART_PACKET_ID(my_heart_pkg_id), "heart packet id out of range");
```
- 在预处理/宏上下文中也可直接使用 `YGGR_PP_CHECK_HEART_PACKET_ID` 做静态检查或条件编译：
```cpp
#if YGGR_PP_CHECK_HEART_PACKET_ID(MY_PAK_ID)
    // 处理心跳包相关的宏逻辑
#endif
```

## 宏与实现依赖
- `YGGR_STATIC_CONSTANT`：用于声明类内的静态常量，项目中可能为了兼容不同编译器对 `static const` / `constexpr` 的处理而定义了该宏，请参考 `yggr/base/static_constant.hpp`。
- `YGGR_PP_IS_IN_RANGE`：预处理器宏，用于判断给定常量是否在一个闭区间内（宏实现位于 `yggr/ppex/range_checker.hpp`）。

