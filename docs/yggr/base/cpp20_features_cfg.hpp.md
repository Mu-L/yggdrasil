---
# cpp20_features_cfg.hpp 文档

## 文件简介

cpp20_features_cfg.hpp 负责检测和配置 C++20 相关标准库特性的可用性，主要用于判断 C++98 绑定器（binders）等旧特性在 C++20 及以上环境下的支持情况，并定义相应的兼容性宏。该文件确保 Yggdrasil 工程在不同编译器、标准库和 Boost 版本下对 C++20 特性的正确适配。

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

### 2. C++98 Binders（绑定器）支持检测

- 检查 Boost 是否定义了 `BOOST_NO_CXX98_BINDERS`。
- 若未定义，则进一步检测 MSVC 标准库版本（`_CPPLIB_VER`）：
  - 若 `_CPPLIB_VER >= 650`（即 Visual Studio 2015 及以上），并且：
    - `_HAS_AUTO_PTR_ETC == 0`，则定义 `YGGR_NO_CXX98_BINDERS`
    - 或 `_HAS_DEPRECATED_ADAPTOR_TYPEDEFS == 0`，则定义 `YGGR_NO_CXX98_BINDERS`
- 若 Boost 已定义 `BOOST_NO_CXX98_BINDERS`，则直接定义 `YGGR_NO_CXX98_BINDERS`。

### 3. 预留扩展

- 文件末尾注释 `// append other...`，用于后续扩展更多 C++20 特性检测与宏定义。

---

## 用法说明

- 通过检测宏 `YGGR_NO_CXX98_BINDERS`，可在代码中安全判断是否可以使用 C++98 绑定器（如 `std::bind1st`、`std::bind2nd` 等），避免因环境不支持导致的编译错误。

````cpp
#ifndef YGGR_NO_CXX98_BINDERS
#include <functional> // 可安全使用 C++98 绑定器
#endif
````

---

## 注意事项

- 推荐所有涉及 C++98 绑定器等旧特性的代码均通过这些宏进行条件编译，保证跨平台和跨标准兼容性。
- 宏的具体定义会根据编译器、标准库和 Boost 版本自动适配，无需手动干预。
- 该文件为 C++20 及以后特性适配的基础，可根据实际需求扩展更多特性检测。

---

 

