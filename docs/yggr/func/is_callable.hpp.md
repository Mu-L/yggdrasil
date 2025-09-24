---
is_callable.hpp 文档

---

# 文件：is_callable.hpp

## 简介
该头文件为 yggdrasil 项目中可调用类型检测工具，主要用于在编译期判断类型 F 是否为可调用对象（即是否重载了 `operator()`），并可排除函数指针类型的检测。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- has_operator_function.hpp
- Boost TypeTraits 相关头文件（`is_pointer`、`mpl::false_`）

### 主要模板
#### 1. `is_callable<F>`
- 检查类型 F 是否为可调用对象（拥有 `operator()`）。
- 适用于函数对象、Lambda、仿函数等类型。
- 不支持类成员函数指针（因其需对象调用）。

#### 2. `is_callable_exclude_function_pointer<F>`
- 检查类型 F 是否为可调用对象，但排除函数指针类型。
- 若 F 为指针类型，结果为 `false_`。

### 实现原理
- 通过 SFINAE 检测 `operator()` 是否存在。
- 利用 `boost::is_pointer` 区分指针类型。

### 用法说明
- 该工具适用于泛型编程、类型萃取、接口适配等场景，可用于静态断言、类型选择等元编程需求。
- 通过 `is_callable<F>::value` 或 `is_callable_exclude_function_pointer<F>::value` 获取检测结果。

---



