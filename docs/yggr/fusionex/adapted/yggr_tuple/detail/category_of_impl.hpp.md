---
category_of_impl.hpp 文档

---

## 文件说明

**文件路径**category_of_impl.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件为 Boost.Fusion 框架扩展了 `category_of_impl`，使其支持 `yggr_tuple` 类型的遍历类别声明。  
其核心功能是通过模板特化，声明 `yggr_tuple` 在 Fusion 框架下属于 `forward_traversal_tag`（前向遍历）类别。

### 主要结构

- **boost::fusion::extension::category_of_impl<yggr_tuple_tag>**
  - 针对 `yggr_tuple_tag` 的特化，实现了 `apply` 内嵌模板结构体。
  - `apply<T>`：
    - `type`：定义为 `forward_traversal_tag`，表示该元组支持前向遍历。

### 用法场景

该实现用于在 Boost.Fusion 框架下，将 `yggr_tuple` 作为前向遍历序列进行算法操作，兼容 Boost.Fusion 的相关接口和算法。

---



