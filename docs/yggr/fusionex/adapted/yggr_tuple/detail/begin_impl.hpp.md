---
begin_impl.hpp 文档

---

## 文件说明

**文件路径**begin_impl.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件为 Boost.Fusion 框架扩展了 `begin_impl`，使其支持 `yggr_tuple` 类型的序列起始迭代器获取。  
其核心功能是通过模板特化，允许在编译期安全地获取 `yggr_tuple` 的起始迭代器类型，并提供相应的构造方法。

### 主要结构

- **boost::fusion::extension::begin_impl<yggr_tuple_tag>**
  - 针对 `yggr_tuple_tag` 的特化，实现了 `apply` 内嵌模板结构体。
  - `apply<Sequence>`：
    - `type`：定义为 `yggr_tuple_iterator<Sequence>`，即元组的迭代器类型。
    - `call(Sequence& v)`：返回指向元组起始位置的迭代器。

### 依赖

- yggr_tuple_iterator.hpp：定义了 `yggr_tuple_iterator` 迭代器类型。

### 用法场景

该实现用于在 Boost.Fusion 框架下，将 `yggr_tuple` 作为序列类型进行迭代器操作，兼容 Boost.Fusion 的算法和接口。

---



