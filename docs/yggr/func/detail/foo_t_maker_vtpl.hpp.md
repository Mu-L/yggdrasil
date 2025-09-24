---
foo_t_maker_vtpl.hpp 文档

---

# 文件：foo_t_maker_vtpl.hpp

## 简介
该头文件为 yggdrasil 项目中函数类型元编程工具的可变参数模板实现部分，主要用于通过可变参数模板自动生成函数指针类型和成员函数指针类型的元信息。相比宏实现，代码更现代、类型推导更灵活。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- integer_sequence.hpp
- args.hpp、null_t.hpp、cv_mark.hpp
- Boost MPL 相关头文件

### 主要模板与结构
#### 1. `foo_t_maker`
- 用于生成普通函数指针类型的元信息，支持任意数量和类型的参数（通过可变参数模板）。
- 自动裁剪参数列表中遇到的 `null_type` 及其后续参数。
- 提供 `foo_type`、`foo_pointer_type`、`type`、`arg<N>` 等类型定义和参数数量常量。

#### 2. `member_foo_t_maker`
- 用于生成成员函数指针类型的元信息，支持 const/volatile 修饰和任意参数数量。
- 自动裁剪参数列表中遇到的 `null_type` 及其后续参数。
- 提供 `foo_type`、`foo_pointer_type`、`type`、`arg<N>` 等类型定义和参数数量常量。

#### 3. 辅助模板
- `foo_t_maker_helper`、`member_foo_t_maker_helper`：通过 `index_sequence` 展开参数类型，生成对应的函数/成员函数类型。

### 特点与优势
- 使用 C++11/14 可变参数模板和 `index_sequence`，代码更简洁、类型推导更强大。
- 支持参数数量和类型灵活变化，适合泛型编程和类型萃取场景。
- 兼容 const/volatile 成员函数类型。

### 用法说明
- 通过 `foo_t_maker<R, Args...>` 可获得普通函数指针类型及参数信息。
- 通过 `member_foo_t_maker<R, C, cv_mark, Args...>` 可获得成员函数指针类型及参数信息。

---



