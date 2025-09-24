---
is_view_impl.hpp 文档

---

## 文件说明

**文件路径**is_view_impl.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件为 Boost.Fusion 框架扩展了 `is_view_impl`，使其支持 `yggr_tuple` 类型的视图判定。  
其核心功能是通过模板特化，声明 `yggr_tuple` 在 Fusion 框架下不是视图类型。

### 主要结构

- **boost::fusion::extension::is_view_impl<yggr_tuple_tag>**
  - 针对 `yggr_tuple_tag` 的特化，实现了 `apply` 内嵌模板结构体。
  - `apply<T>`：
    - 继承自 `mpl::false_`，表示 `yggr_tuple` 不是 Fusion 视图类型。

### 依赖

- Boost MPL 布尔类型定义。

### 用法场景

该实现用于在 Boost.Fusion 框架下，将 `yggr_tuple` 明确标识为非视图类型，保证其行为符合 Fusion 的相关接口和算法要求。

---



