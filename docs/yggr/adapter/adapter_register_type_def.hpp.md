---
# 文件：adapter_register_type_def.hpp

## 简介

该头文件定义了 `yggr::adapter::adapter_register_type_def` 结构体，用于适配器注册类型的常量定义。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。软件按“原样”提供，不附带任何明示或暗示的担保。

## 依赖

- yggrdef.h  
- static_constant.hpp

## 命名空间

- yggr
  - `adapter`

## 结构体：adapter_register_type_def

该结构体定义了四个静态常量，用于标识适配器注册的类型：

| 常量名         | 值           | 说明                   |
| -------------- | ------------ | ---------------------- |
| E_direct       | 0x00000000   | 标记值(无用)           |
| E_to_src       | 0x00000001   | 允许发送到源               |
| E_from_src     | 0x00000002   | 允许从源接收               |
| E_both         | 0x00000003   | 允许收发(E_to_src | E_from_src)|

这些常量可用于适配器注册相关的逻辑判断和类型区分。

## 示例用法

```cpp
#include <yggr/adapter/adapter_register_type_def.hpp>

u32 reg_type = yggr::adapter::adapter_register_type_def::E_both;
if (reg_type == yggr::adapter::adapter_register_type_def::E_both) {
    // 执行双向注册相关操作
}
```

## 结尾

该文件仅包含常量定义，无成员函数或复杂逻辑。适用于需要区分适配器注册类型的场景。

---

