---
foo_t_maker_vmacro.hpp 文档

---

# 文件：foo_t_maker_vmacro.hpp

## 简介
该头文件为 yggdrasil 项目中函数类型元编程工具的宏实现部分，主要用于自动生成函数指针类型和成员函数指针类型的元信息。通过大量宏和模板元编程，支持变参、const/volatile 修饰、参数数量可变等复杂场景。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- typedef.hpp、symbol_if.hpp、foo_params.hpp
- args.hpp、null_t.hpp、cv_mark.hpp
- Boost MPL 相关头文件
- `boost/type_traits/add_pointer.hpp`

### 主要宏与辅助结构
- 通过宏 `_YGGR_TMP_PP_VECTOR_ARGS_GET`、`YGGR_PP_FOO_TYPEINFO_HELPERS`、`YGGR_PP_MEMBER_FOO_TYPEINFO_HELPERS` 等，自动生成不同参数数量和类型的函数/成员函数类型定义。
- 支持参数数量上限可配置（`YGGR_PP_FOO_TYPEINFO_PARAMS_LIMIT_LEN`）。
- 通过 Boost MPL 实现类型列表、查找、擦除等元操作。

### 主要模板
#### 1. `foo_t_maker`
- 用于生成普通函数指针类型的元信息。
- 支持变参、参数类型自动推导、参数数量自动裁剪。
- 提供 `foo_type`、`foo_pointer_type`、`type`、`arg<N>` 等类型定义和参数数量常量。

#### 2. `member_foo_t_maker`
- 用于生成成员函数指针类型的元信息。
- 支持 const/volatile 修饰、参数类型自动推导、参数数量自动裁剪。
- 提供 `foo_type`、`foo_pointer_type`、`type`、`arg<N>` 等类型定义和参数数量常量。

#### 3. 辅助模板
- `foo_t_maker_helper`、`member_foo_t_maker_helper`：通过宏展开自动生成不同参数数量的特化版本。

### 用法说明
- 适用于需要根据参数类型和数量自动生成函数/成员函数指针类型的场景，常用于泛型编程、回调、类型萃取等高级用法。
- 通过 `foo_t_maker` 和 `member_foo_t_maker` 可获得对应的函数类型、指针类型及参数信息。

---



