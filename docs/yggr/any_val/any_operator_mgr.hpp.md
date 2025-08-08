---
# 文件：any_operator_mgr.hpp

## 简介

any_operator_mgr.hpp 是 yggdrasil 项目中用于管理和实现 `any` 类型（包括 `yggr::any` 和 `boost::any`）的操作符注册、调用与扩展的核心头文件。它通过操作符管理器类，实现了对 `any` 类型的算术、逻辑、位运算、比较、自增自减等操作的统一注册、注销和调用机制，并支持操作符的动态扩展。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改、分发和商业用途，但需保留原作者版权声明和许可信息。

 <!-- ## 作者 -->

 <!-- - xu yang -->

## 主要内容

- 头文件保护宏，防止重复包含。
- 包含大量依赖头文件，涵盖类型特征、元编程、智能指针、线程安全容器、字符串、元组、函数信息、操作符标签等。
- 定义了操作符注册、注销相关的宏，简化操作符的批量声明。
- 实现了 `basic_any_operator` 及其派生类，封装了各种一元、二元、可变操作符的调用逻辑。
- 实现了 `any_operator_mgr` 模板类，作为操作符管理器，支持操作符的注册、注销、查找和调用。
- 提供了 `operator_id_maker`，用于生成操作符唯一标识。
- 通过 `_YGGR_ANY_VAL_ANY_OPERATOR` 宏为 `yggr::any` 和 `boost::any` 自动生成了常用操作符的重载，使其可以像内置类型一样使用操作符。

## 主要类与结构

### 1. `basic_any_operator` 及其派生类

- `basic_any_operator<Any>`：基础操作符接口，支持一元、二元、可变等多种操作符的多态调用。
- `any_unary_operator`、`any_mutable_unary_operator`、`any_ref_ret_mutable_unary_operator`、`any_binary_operator`、`any_mutable_binary_operator`：分别实现不同类型操作符的具体逻辑。

### 2. `operator_id_maker`

- 用于根据操作符标签和参数类型生成唯一的操作符ID，便于操作符的注册和查找。

### 3. `any_operator_mgr`

- 模板类，负责管理某种 `any` 类型的所有操作符注册、注销和调用。
- 支持一元、二元、可变等多种操作符的注册与注销。
- 提供了 `call_*` 系列方法，统一调用已注册的操作符。
- 内部使用线程安全的哈希表存储操作符。

### 4. 操作符重载宏

- 通过 `_YGGR_ANY_VAL_ANY_OPERATOR` 宏，为 `yggr::any` 和 `boost::any` 自动生成了常用操作符的重载（如 `+`, `-`, `*`, `/`, `==`, `!=`, `++`, `--` 等），使其用法与内置类型一致。

## 用法示例

```cpp
#include <yggr/any_val/any_operator_mgr.hpp>

// 注册操作符
yggr::any_val::any_operator_mgr<yggr::any> mgr;
mgr.register_plus<int, int>();

// 使用操作符
yggr::any a = 1, b = 2;
yggr::any c = a + b; // 实际调用了操作符管理器中的 plus 操作
```

## 依赖

- any.hpp
- operator_wrap.hpp
- ptr_single.hpp
- safe_unordered_map.hpp
- operator_tags.hpp
- 以及 Boost、元编程、智能指针等相关库

---

如需详细功能和实现细节，请参考本文件实现及相关依赖头文件。

