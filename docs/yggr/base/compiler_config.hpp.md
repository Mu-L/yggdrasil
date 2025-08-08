---
# compiler_config.hpp 文档

## 文件简介

compiler_config.hpp 负责根据编译器、C++标准版本和 Boost 配置，自动检测和定义一系列兼容性宏。该文件用于屏蔽不同编译器和标准下的特性差异，保证 Yggdrasil 工程在多平台、多编译器环境下的可移植性和稳定性。

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

### 2. MSVC 安全警告屏蔽

- 对于 MSVC 2012 及以上版本，自动定义 `_SCL_SECURE_NO_WARNINGS`，屏蔽部分安全警告。

### 3. auto_ptr 支持检测

- C++17 及以上标准下，自动禁用 `auto_ptr`，定义 `YGGR_NO_AUTO_PTR` 和 `BOOST_NO_AUTO_PTR`。

### 4. 字符类型与字符串支持检测

- 检测并定义如下宏，适配不同标准和编译器对宽字符、UTF 字符类型的支持：
  - `YGGR_NO_CWCHAR`, `BOOST_NO_CWCHAR`：不支持宽字符头文件
  - `YGGR_NO_WSTRING`, `BOOST_NO_STD_WSTRING`：不支持宽字符串
  - `YGGR_NO_CHAR8_T`, `YGGR_NO_U8STRING_T`：不支持 `char8_t` 和 `u8string`
  - `YGGR_NO_CHAR16_T`, `YGGR_NO_U16STRING_T`：不支持 `char16_t` 和 `u16string`
  - `YGGR_NO_CHAR32_T`, `YGGR_NO_U32STRING_T`：不支持 `char32_t` 和 `u32string`
- 针对 Apple Clang 特定版本和 C++20 做了特殊兼容处理。

### 5. 容器特性支持检测

- 检测并定义如下容器相关宏：
  - `YGGR_NO_CXX11_HDR_ARRAY`：不支持 `<array>`
  - `YGGR_NO_CXX11_HDR_UNORDERED_SET`：不支持 `<unordered_set>`
  - `YGGR_NO_CXX11_HDR_UNORDERED_MAP`：不支持 `<unordered_map>`
  - `YGGR_NO_CXX11_STD_UNORDERED`：不支持 C++11 标准库 unordered 容器
  - `YGGR_HAS_CXX11_STD_HASH`：支持 C++11 标准库 hash

### 6. 语言特性支持检测

- 检测并定义如下语言特性相关宏：
  - `YGGR_NO_CXX11_VARIADIC_TEMPLATES`, `YGGR_NO_CXX14_VARIADIC_TEMPLATES`：不支持可变参数模板
  - `YGGR_NO_CXX11_DECLTYPE`：不支持 `decltype`
  - `YGGR_NO_CXX11_VARIADIC_MACROS`：不支持可变参数宏
  - `YGGR_NO_CXX11_HDR_INITIALIZER_LIST`：不支持 `<initializer_list>`
  - `YGGR_NO_CXX11_SMART_PTR`：不支持 C++11 智能指针
  - `YGGR_NO_CXX11_HDR_TUPLE`：不支持 `<tuple>`

---

## 用法说明

- 本文件会在工程编译初期自动检测编译器和标准特性，定义相关兼容性宏，供后续代码条件编译使用。
- 通过这些宏，可以安全地在不同平台和标准下屏蔽或启用特定特性。

---

## 注意事项

- 必须先包含 `<yggr/base/yggrdef.h>`，否则会编译报错。
- 不建议手动修改这些宏，若需自定义兼容性配置，请在更高层的配置文件中处理。

---

 

