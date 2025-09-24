---
yggr_tuple.hpp 文档

---

## 文件说明

**文件路径**yggr_tuple.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件为 Boost.Fusion 框架提供了 `yggr_tuple` 相关的全部适配器接口的统一头文件。  
通过包含本文件，可以一次性获得 `yggr_tuple` 在 Fusion 框架下的所有适配支持，包括类型标签、序列判定、遍历、访问、长度等功能。

### 主要结构

- 依次包含了以下适配器实现头文件：
  - tag_of.hpp：类型标签与序列标签适配
  - is_view_impl.hpp：视图类型判定适配
  - is_sequence_impl.hpp：序列类型判定适配
  - category_of_impl.hpp：遍历类别适配
  - begin_impl.hpp：起始迭代器适配
  - end_impl.hpp：末尾迭代器适配
  - size_impl.hpp：长度适配
  - at_impl.hpp：元素访问适配
  - value_at_impl.hpp：元素类型适配

### 用法场景

只需包含本头文件，即可让 `yggr_tuple` 及其相关类型在 Boost.Fusion 框架下作为序列类型使用，支持泛型算法、遍历、访问等操作。

---
