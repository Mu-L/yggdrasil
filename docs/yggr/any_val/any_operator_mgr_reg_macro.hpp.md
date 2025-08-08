---
# 文件：any_operator_mgr_reg_macro.hpp

## 简介

any_operator_mgr_reg_macro.hpp 是 yggdrasil 项目中用于简化 `any_operator_mgr` 操作符注册与注销的宏定义头文件。通过一系列宏，用户可以方便地为 `any` 类型或类似类型注册、注销一元和二元操作符，并支持对不安全类型和特定平台（如 MinGW）进行条件编译处理。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改、分发和商业用途，但需保留原作者版权声明和许可信息。

 <!-- ## 作者 -->

 <!-- - xu yang -->

## 主要内容

- 头文件保护宏，防止重复包含。
- 包含依赖头文件：
  - yggrdef.h
- 针对 MinGW 平台的条件编译注释（用于减少库体积，避免 32 位 MinGW 的链接器内存溢出）。
- 一系列操作符注册与注销相关的宏定义，支持一元、二元、可变操作符及其不安全版本。

## 主要宏定义

### 注册宏

- `YGGR_PP_ANY_VAL_REGISTER_UNARY_OPERATOR`
- `YGGR_PP_ANY_VAL_REGISTER_MUTABLE_UNARY_OPERATOR`
- `YGGR_PP_ANY_VAL_REGISTER_UNARY_OPERATOR_UNSAFE`
- `YGGR_PP_ANY_VAL_REGISTER_MUTABLE_UNARY_OPERATOR_UNSAFE`
- `YGGR_PP_ANY_VAL_REGISTER_BINARY_OPERATOR`
- `YGGR_PP_ANY_VAL_REGISTER_MUTABLE_BINARY_OPERATOR`
- `YGGR_PP_ANY_VAL_REGISTER_BINARY_OPERATOR_UNSAFE`
- `YGGR_PP_ANY_VAL_REGISTER_MUTABLE_BINARY_OPERATOR_UNSAFE`

这些宏根据条件编译参数（如 `YGGR_ANY_VAL_OP_NOT_INIT_BASE_TYPE`、`YGGR_ANY_VAL_OP_EXCLUDE_UNSAFE_TYPE`）自动切换为实际注册调用或直接返回 `true`，以适应不同平台和安全需求。

### 注销宏

- `YGGR_PP_ANY_VAL_UNREGISTER_UNARY_OPERATOR`
- `YGGR_PP_ANY_VAL_UNREGISTER_MUTABLE_UNARY_OPERATOR`
- `YGGR_PP_ANY_VAL_UNREGISTER_UNARY_OPERATOR_UNSAFE`
- `YGGR_PP_ANY_VAL_UNREGISTER_MUTABLE_UNARY_OPERATOR_UNSAFE`
- `YGGR_PP_ANY_VAL_UNREGISTER_BINARY_OPERATOR`
- `YGGR_PP_ANY_VAL_UNREGISTER_MUTABLE_BINARY_OPERATOR`
- `YGGR_PP_ANY_VAL_UNREGISTER_BINARY_OPERATOR_UNSAFE`
- `YGGR_PP_ANY_VAL_UNREGISTER_MUTABLE_BINARY_OPERATOR_UNSAFE`

注销宏与注册宏类似，用于注销已注册的操作符。

## 用法示例

```cpp
// 注册一元操作符
YGGR_PP_ANY_VAL_REGISTER_UNARY_OPERATOR(pmgr, foo_name, param);

// 注销二元操作符
YGGR_PP_ANY_VAL_UNREGISTER_BINARY_OPERATOR(pmgr, foo_name, left, right);
```

## 平台与安全性支持

- 针对 MinGW 平台和不安全类型的特殊处理，避免因类型不安全或平台限制导致的问题。
- 通过宏控制是否注册/注销不安全类型的操作符。

## 依赖

- yggrdef.h

---

如需详细功能和实现细节，请参考相关实现文件和 `any_operator_mgr` 相关文档。

