---
# index_generator.hpp 文档

## 概述

`index_generator.hpp` 是 yggdrasil 项目中用于多索引容器（如 Boost.MultiIndex）索引生成的适配头文件。该文件通过引入并重命名 Boost.MultiIndex 的相关工具类型和宏，方便在 yggdrasil 项目中统一定义和管理多索引容器的索引类型、成员、成员函数等，提升代码的可读性和可维护性。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含 `<yggr/base/yggrdef.h>` 和 Boost.MultiIndex 相关头文件。
- 在 `yggr::container` 命名空间下引入并重命名了 Boost.MultiIndex 的常用类型和工具，包括：
  - `indexed_by`、`identity`、`member`、`member_offset`
  - `mem_fun`、`const_mem_fun`、`mem_fun_explicit`、`const_mem_fun_explicit`
  - `global_fun`
  - `composite_key` 及其相关比较、哈希类型
- 定义了宏 `YGGR_INDEX_GENERATOR_MEMBER`、`YGGR_INDEX_GENERATOR_MEM_FUN`、`YGGR_INDEX_GENERATOR_CONST_MEM_FUN`，分别对应 Boost.MultiIndex 的成员和成员函数索引宏，便于统一书写风格。

## 适用场景

- 需要在项目中大量使用 Boost.MultiIndex 多索引容器时，统一索引定义方式。
- 泛型容器、数据表、索引结构等需要灵活定义多种索引的场景。

## 使用示例

```cpp
#include <yggr/container/index_generator.hpp>

// 定义多索引容器时可直接使用 yggr::container 命名空间下的类型和宏
```

---

本文件为 yggdrasil 多索引容器适配体系的基础组件，便于统一管理和扩展 Boost.MultiIndex 相关功能。

