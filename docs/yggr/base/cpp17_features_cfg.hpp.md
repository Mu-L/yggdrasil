---
# cpp17_features_cfg.hpp 文档

## 文件简介

cpp17_features_cfg.hpp 负责检测和配置 C++17 相关标准库特性的可用性，主要用于判断 `<string_view>` 等 C++17 新增头文件和特性的支持情况，并定义相应的兼容性宏。该文件确保 Yggdrasil 工程在不同编译器、标准库和 Boost 版本下对 C++17 特性的正确适配。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- 必须先包含 `<yggr/base/yggrdef.h>`
- 依赖 Boost 配置相关宏

---

## 主要内容

### 1. 头文件包含保护

- 若未先包含 `yggrdef.h`，则编译报错，确保类型和基础配置一致。

### 2. C++17 `<string_view>` 支持检测

- 通过多重条件判断当前编译环境是否支持 `<string_view>`，并定义宏：
  - `YGGR_NO_CXX17_HDR_STRING_VIEW`：不支持 `<string_view>`
  - `BOOST_NO_CXX17_HDR_STRING_VIEW`：Boost 不支持 `<string_view>`
- 检查内容包括：
  - C++ 标准版本是否大于等于 C++17
  - 是否存在 `<string_view>` 头文件
  - 标准库和编译器版本（如 MSVC、libc++、libstdc++ 等）
  - Boost 对 `<string_view>` 的支持情况

### 3. C++98 function_base 支持检测

- 检查并定义：
  - `YGGR_NO_CXX98_FUNCTION_BASE`：不支持 C++98 function_base
- 主要针对 MSVC 2017 及以上，若 `_HAS_AUTO_PTR_ETC == 0`，则禁用 C++98 function_base。

---

## 用法说明

- 通过检测宏 `YGGR_NO_CXX17_HDR_STRING_VIEW`，可在代码中安全判断是否可以使用 `<string_view>`，避免因环境不支持导致的编译错误。
- 通过检测宏 `YGGR_NO_CXX98_FUNCTION_BASE`，可判断是否需要规避 C++98 function_base 相关代码。

````cpp
#ifndef YGGR_NO_CXX17_HDR_STRING_VIEW
#include <string_view>
#endif
````

---

## 注意事项

- 推荐所有涉及 C++17 新特性的代码均通过这些宏进行条件编译，保证跨平台和跨标准兼容性。
- 宏的具体定义会根据编译器、标准库和 Boost 版本自动适配，无需手动干预。

---

 

