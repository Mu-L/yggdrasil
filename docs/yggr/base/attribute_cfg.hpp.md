---
# attribute_cfg.hpp 文档

## 文件简介

attribute_cfg.hpp 主要用于统一管理和封装 C++ 属性（attribute）相关的宏定义，便于在 Yggdrasil 工程中跨平台、跨编译器地使用如 `[[nodiscard]]`、`[[no_unique_address]]` 等现代 C++ 属性。该文件自动适配 Boost 配置，保证属性宏在不同环境下的兼容性。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- 必须先包含 `<yggr/base/yggrdef.h>`
- `<boost/config.hpp>`
- `<boost/detail/workaround.hpp>`

---

## 主要内容

### 1. 头文件包含保护

- 若未先包含 `yggrdef.h`，则编译报错，确保类型和基础配置一致。

### 2. 属性宏定义

- **YGGR_ATTRIBUTE_UNUSED**  
  用于标记未使用的变量或函数，防止编译器警告。若 Boost 支持 `BOOST_ATTRIBUTE_UNUSED`，则定义为空宏。

- **YGGR_ATTRIBUTE_NODISCARD**  
  用于标记函数返回值不可忽略。  
  - 若 Boost 未定义 `BOOST_ATTRIBUTE_NODISCARD`，则为空宏。
  - 若 Boost 定义且编译器支持，则使用 `BOOST_ATTRIBUTE_NODISCARD`。
  - 针对 GCC 7 及以下且非 C++11 的特殊情况，做了兼容处理。

- **YGGR_ATTRIBUTE_NO_UNIQUE_ADDRESS**  
  用于标记成员变量可优化为无唯一地址（C++20 特性）。  
  - 若 Boost 未定义 `BOOST_ATTRIBUTE_NO_UNIQUE_ADDRESS`，则为空宏。
  - 若 Boost 定义，则使用 `BOOST_ATTRIBUTE_NO_UNIQUE_ADDRESS`。

---

## 用法示例

````cpp
#include <yggr/base/attribute_cfg.hpp>

class Foo {
    YGGR_ATTRIBUTE_NO_UNIQUE_ADDRESS int x;
};

YGGR_ATTRIBUTE_NODISCARD int bar();

void func(YGGR_ATTRIBUTE_UNUSED int unused_param) {
    // ...
}
````

---

## 注意事项

- 需先包含 `<yggr/base/yggrdef.h>`，否则编译报错。
- 该文件仅定义属性相关宏，不直接实现功能，需配合实际代码使用。
- 属性宏会根据 Boost 和编译器能力自动适配，保证跨平台兼容性。

---

 

