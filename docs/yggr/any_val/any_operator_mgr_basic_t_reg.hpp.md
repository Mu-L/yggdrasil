---
# 文件：any_operator_mgr_basic_t_reg.hpp

## 简介

any_operator_mgr_basic_t_reg.hpp 是 yggdrasil 项目中用于管理和注册 `any` 类型基础操作符的辅助头文件。它为 `any_val` 提供了基础类型操作符的注册接口，便于对 `any` 类型进行各种算术、逻辑、位运算等操作的支持。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改、分发和商业用途，但需保留原作者版权声明和许可信息。

 <!-- ## 作者 -->

 <!-- - xu yang -->

## 主要内容

- 头文件保护宏，防止重复包含。
- 包含依赖头文件：
  - yggrdef.h
  - ptr_single.hpp
  - any_operator_mgr.hpp
- 定义命名空间 `yggr::any_val`。
- 声明结构体 `any_operator_mgr_basic_t_reg`，用于注册和初始化 `any` 类型的基础操作符。

## 结构体：any_operator_mgr_basic_t_reg

### 类型定义

- `any_operator_mgr_type`：`any_operator_mgr< ::yggr::any>`，用于管理 `any` 类型的操作符。
- `any_operator_mgr_single_type`：`yggr::ptr_single<any_operator_mgr_type>`，单例管理器类型。

### 静态成员函数

- `s_init()` / `s_init(bool binit_base)`：初始化操作符管理器，可选择是否初始化基础类型。
- `s_support_base()`：判断是否支持基础类型操作。
- 一系列 `s_register_base_type_*` 方法：注册各种基础类型的操作符，包括比较、算术、逻辑、位运算、自增自减等。
- 一系列 `prv_s_register_base_type_*` 方法：私有辅助注册函数，通常用于内部实现细节的分步注册。

### 支持的操作符注册（部分示例）

- 比较操作：`greater_equal`, `greater`, `less_equal`, `less`, `equal_to`, `not_equal_to`
- 位运算：`bitwise_not`, `bitwise_and`, `bitwise_or`, `bitwise_xor`, `bitwise_left_shift`, `bitwise_right_shift`
- 逻辑运算：`logic_not`, `logic_and`, `logic_or`
- 算术运算：`plus`, `minus`, `multiplies`, `divides`, `modulus`, `negate`, `posivite`
- 赋值与自增自减：`set`, `tail_increment`, `head_increment`, `tail_decrement`, `head_decrement`

## 用法说明

在需要为 `any` 类型注册基础操作符时，包含此头文件，并调用相关静态方法进行注册。例如：

```cpp
#include <yggr/any_val/any_operator_mgr_basic_t_reg.hpp>

yggr::any_val::any_operator_mgr_basic_t_reg::s_init();
```

## 依赖

- yggrdef.h
- ptr_single.hpp
- any_operator_mgr.hpp

---

如需详细功能和实现细节，请参考对应的实现文件和 `any_operator_mgr` 相关文档。

