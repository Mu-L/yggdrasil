---
value_at_impl.hpp 文档

---

## 文件说明

**文件路径**value_at_impl.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件为 Boost.Fusion 框架扩展了 `value_at_impl`，使其支持 `yggr_tuple` 类型的元素类型获取。  
其核心功能是通过模板特化，允许在编译期获取 `yggr_tuple` 指定索引处元素的类型。

### 主要结构

- **boost::fusion::extension::value_at_impl<yggr_tuple_tag>**
  - 针对 `yggr_tuple_tag` 的特化，实现了 `apply` 内嵌模板结构体。
  - `apply<Sequence, N>`：
    - 继承自 `yggr::tuples::element<N::value, Sequence>`，用于获取元组第 N 个元素的类型。

### 依赖

- tuple.hpp：定义了 `yggr_tuple` 及其元素类型萃取。

### 用法场景

该实现用于在 Boost.Fusion 框架下，将 `yggr_tuple` 作为序列类型进行元素类型查询，兼容 Fusion 的相关算法和接口。

---



