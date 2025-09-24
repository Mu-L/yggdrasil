---
tag_of.hpp 文档

---

## 文件说明

**文件路径**tag_of.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件为 Boost.Fusion 框架扩展了 `tag_of` 和 `sequence_tag`，使其支持 `yggr_tuple` 及其相关类型的类型标签和序列标签。  
其核心功能是通过模板特化，将 `yggr_tuple` 及其 cons 结构与 Fusion 框架的类型系统对接，保证其能被 Fusion 识别和处理。

### 主要结构

- **boost::fusion::traits::tag_of**
  - 针对 `yggr::tuples::tuple` 和 `yggr::tuples::cons` 的特化，类型定义为 `yggr_tuple_tag`。
- **boost::mpl::sequence_tag**
  - 针对 `yggr::tuples::tuple`、`yggr::tuples::cons` 及其 const 版本的特化，类型定义为 `fusion_sequence_tag`。

### 依赖

- tuple.hpp：定义了 `yggr_tuple` 及其 cons 结构。
- foo_params.hpp：用于元组参数宏定义。
- Boost.Fusion 和 Boost.MPL 相关头文件。

### 用法场景

该实现用于在 Boost.Fusion 框架下，将 `yggr_tuple` 及其 cons 结构作为序列类型进行识别和泛型编程，兼容 Fusion 的相关算法和接口。

---



