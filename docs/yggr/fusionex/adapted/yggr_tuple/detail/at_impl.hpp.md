---
at_impl.hpp 文档

---

## 文件说明

**文件路径**at_impl.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件为 Boost.Fusion 框架扩展了 `at_impl`，使其支持 `yggr_tuple` 类型的元素访问。  
其核心功能是通过模板特化，允许在编译期安全地获取 `yggr_tuple` 中指定索引的元素类型和引用。

### 主要结构

- **boost::fusion::extension::at_impl<yggr_tuple_tag>**
  - 针对 `yggr_tuple_tag` 的特化，实现了 `apply` 内嵌模板结构体。
  - `apply<Sequence, N>`：
    - `element`：获取元组第 N 个元素的类型。
    - `type`：根据 `Sequence` 是否为 const，选择合适的访问类型（const 或非 const）。
    - `call(Sequence& seq)`：返回元组第 N 个元素的引用。

### 依赖

- tuple.hpp：定义了 `yggr_tuple` 及相关元组操作。
- Boost MPL、类型萃取与类型判断相关头文件。

### 用法场景

该实现用于在 Boost.Fusion 框架下，将 `yggr_tuple` 作为序列类型进行元素访问和泛型编程，兼容 Boost.Fusion 的算法和接口。

---



