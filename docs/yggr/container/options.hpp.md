---
# 文件：options.hpp

## 简介

`options.hpp` 是 yggdrasil 项目中用于定义容器选项（options）相关类型和配置的头文件。该文件为 tree、vector、deque 等容器提供了选项类型的定义和兼容性适配，支持不同 Boost 版本下的灵活扩展。


## 主要内容

### 1. 头文件保护

- 宏定义：`__YGGR_CONTAINER_OPTIONS_HPP__`

### 2. 依赖包含

- 依赖 yggrdef.h 和（Boost 1.56+）`boost/container/options.hpp`。

### 3. tree 选项

- 低版本 Boost（<1.56）下自定义 `tree_type_enum`、`tree_opt`、`tree_assoc_defaults`。
- 高版本直接使用 Boost.Container 的相关类型。

### 4. vector 选项

- 低版本 Boost（<1.67）下自定义 `vector_opt`、`vector_null_opt`，支持自定义增长因子和存储大小类型。
- 高版本直接使用 Boost.Container 的相关类型。

### 5. deque 选项

- 低版本 Boost（<1.71）下自定义 `deque_opt`、`deque_null_opt`，支持自定义块大小和块字节数（两者不能同时指定）。
- 高版本直接使用 Boost.Container 的相关类型。

### 6. 其他导出

- 导出 `ordered_unique_range_t`、`ordered_range_t`、`ordered_range` 等 Boost.Container 的辅助类型。

## 用法说明

- 适用于需要自定义容器选项（如树类型、vector增长策略、deque块大小等）的场景。
- 直接包含本头文件，并使用 `yggr::container` 命名空间下的相关类型即可。
- 支持与 Boost.Container 的选项类型无缝对接，便于跨版本兼容。

## 设计说明

- 通过条件编译和类型萃取机制，兼容多版本 Boost，保证项目的可移植性和可维护性。
- 采用现代 C++ 技术，保证类型安全和接口丰富性。

---

如需详细了解各选项类型的具体实现和用法，请参考源码及相关依赖头文件。

