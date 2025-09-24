---
is_sequence_impl.hpp 文档

---

## 文件说明

**文件路径**is_sequence_impl.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件为 Boost.Fusion 框架扩展了 `is_sequence_impl`，使其支持 `yggr_tuple` 类型的序列判定。  
其核心功能是通过模板特化，声明 `yggr_tuple` 在 Fusion 框架下被视为序列类型。

### 主要结构

- **boost::fusion::extension::is_sequence_impl<yggr_tuple_tag>**
  - 针对 `yggr_tuple_tag` 的特化，实现了 `apply` 内嵌模板结构体。
  - `apply<Sequence>`：
    - 继承自 `mpl::true_`，表示 `yggr_tuple` 是一个合法的 Fusion 序列类型。

### 依赖

- Boost MPL 布尔类型定义。

### 用法场景

该实现用于在 Boost.Fusion 框架下，将 `yggr_tuple` 识别为序列类型，从而支持 Fusion 的相关算法和接口。

---



