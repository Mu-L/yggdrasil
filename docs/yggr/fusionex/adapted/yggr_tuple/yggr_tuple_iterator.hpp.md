---
yggr_tuple_iterator.hpp 文档

---

## 文件说明

**文件路径**yggr_tuple_iterator.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件为 Boost.Fusion 框架实现了 `yggr_tuple` 及其相关类型的迭代器 `yggr_tuple_iterator`，使其支持 Fusion 算法和接口的遍历操作。  
其核心功能是通过模板和类型萃取，支持对 `yggr_tuple` 及其 cons 结构的前向遍历、解引用、类型推断和距离计算。

### 主要结构

- **boost::fusion::yggr_tuple_iterator**
  - 适配 `yggr::tuples::cons` 结构，实现前向遍历（forward_traversal_tag）。
  - 提供 `value_of`、`deref`、`next`、`distance` 等元编程接口。
  - 针对 `null_type` 和空元组做了特化，保证边界安全。
- **boost::fusion::yggr_tuple_null_iterator**
  - 用于空元组或 `null_type` 的迭代器特化，实现相等性判断等。

### 依赖

- tuple.hpp：定义了 `yggr_tuple` 及其 cons 结构。
- Boost.Fusion 迭代器框架、类型萃取、MPL 元编程相关头文件。

### 用法场景

该实现用于在 Boost.Fusion 框架下，将 `yggr_tuple` 作为序列类型进行迭代器操作，支持泛型算法、遍历、距离计算等功能，兼容 Fusion 的相关接口。

---



