---
# noexcept_cfg.hpp 文档

## 文件简介

noexcept_cfg.hpp 负责根据 Boost 配置、C++ 标准版本和编译器能力，自动检测并定义一组与 `noexcept` 相关的宏。通过这些宏，Yggdrasil 工程可以在不同 C++ 标准下安全地使用 `noexcept`，并兼容旧标准或不支持 `noexcept` 的环境。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- 必须先包含 `<yggr/base/yggrdef.h>`
- `<boost/config.hpp>`
- `<yggr/base/yggr_cpp_ver_config.hpp>`

---

## 主要内容

### 1. 头文件包含保护

- 若未先包含 `yggrdef.h`，则编译报错，确保类型和基础配置一致。

### 2. noexcept 支持检测与宏定义

- 检测 Boost 是否定义 `BOOST_NO_CXX11_NOEXCEPT`，若不支持 `noexcept`，则：
  - 定义 `YGGR_NO_CXX11_NOEXCEPT`
  - `YGGR_NOEXCEPT` 为空
  - `YGGR_NOEXCEPT_OR_NOTHROW` 为 `throw()`
  - `YGGR_NOEXCEPT_IF(Predicate)` 为空
  - `YGGR_NOEXCEPT_EXPR(Expression)` 为 `false`
- 若支持 `noexcept`，则：
  - `YGGR_NOEXCEPT` 为 `noexcept`
  - `YGGR_NOEXCEPT_OR_NOTHROW` 为 `noexcept`
  - `YGGR_NOEXCEPT_IF(Predicate)` 为 `noexcept((Predicate))`
  - `YGGR_NOEXCEPT_EXPR(Expression)` 为 `noexcept((Expression))`

### 3. 针对不同 C++ 标准的 noexcept 宏

- 针对 C++11、C++14、C++17、C++20、C++23，分别定义了对应的 `YGGR_CXX??_NOEXCEPT` 及其变体宏。
- 若当前标准支持，则为 `YGGR_NOEXCEPT`，否则为空。
- 变体包括：
  - `YGGR_CXX??_NOEXCEPT_OR_NOTHROW`
  - `YGGR_CXX??_NOEXCEPT_IF(Predicate)`
  - `YGGR_CXX??_NOEXCEPT_EXPR(Expression)`

---

## 用法示例

````cpp
#include <yggr/base/noexcept_cfg.hpp>

void foo() YGGR_NOEXCEPT;
void bar() YGGR_CXX17_NOEXCEPT_OR_NOTHROW;
template<typename T>
void baz() YGGR_NOEXCEPT_IF(std::is_nothrow_move_constructible<T>::value);
````

---

## 注意事项

- 推荐所有需要 `noexcept` 的代码均通过这些宏进行条件编译，保证跨平台和跨标准兼容性。
- 宏会根据实际编译环境自动适配，无需手动干预。

---

 

