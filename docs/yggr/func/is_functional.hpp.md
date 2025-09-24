---
is_functional.hpp 文档

---

# 文件：is_functional.hpp

## 简介
该头文件为 yggdrasil 项目中函数对象类型检测工具，主要用于在编译期判断类型 T 是否为 STL 风格的一元或二元函数对象（即是否继承自 `std::unary_function` 或 `std::binary_function`），并据此提供类型萃取和适配能力。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- null_t.hpp
- has_functional_member_t.hpp
- Boost MPL 相关头文件
- `<functional>`

### 主要模板
#### 1. `is_base_of_unary_function<T>`
- 检查类型 T 是否为 STL 风格一元函数对象（拥有 `argument_type` 和 `result_type`，并继承自 `std::unary_function`）。

#### 2. `is_base_of_binary_function<T>`
- 检查类型 T 是否为 STL 风格二元函数对象（拥有 `first_argument_type`、`second_argument_type` 和 `result_type`，并继承自 `std::binary_function`）。

#### 3. `is_functional<T>`
- 检查类型 T 是否为一元或二元函数对象。

### 实现原理
- 通过 SFINAE 和类型萃取，结合 Boost MPL，自动判断类型继承关系和成员类型。
- C++17 及以上标准下，所有判断均为 `false_`（因标准库已移除相关基类）。

### 用法说明
- 该工具适用于泛型编程、类型萃取、函数对象适配等场景，可用于静态断言、类型选择等元编程需求。
- 通过 `is_functional<T>::value` 获取检测结果。

---



