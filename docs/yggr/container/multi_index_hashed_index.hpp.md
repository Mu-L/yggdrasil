---
# multi_index_hashed_index.hpp 文档

## 概述

`multi_index_hashed_index.hpp` 是 yggdrasil 项目中对 Boost.MultiIndex 哈希索引（`hashed_unique`/`hashed_non_unique`）的适配与扩展头文件。该文件统一引入并适配 Boost.MultiIndex 的哈希索引类型，提供 emplace、insert、extract、节点句柄等兼容性接口，并在低版本 Boost 下补充了哈希索引的比较器（==/!=）支持，便于泛型编程和高效多索引容器操作。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含基础定义、类型展开、SFINAE、算法、配置、节点句柄 traits、范围 size 支持等相关头文件。
- 统一引入 `boost::multi_index::hashed_unique` 和 `hashed_non_unique`，并提升为 `yggr::container` 命名空间成员。
- 提供哈希索引的 emplace、emplace_hint、insert、extract 等接口，兼容 C++11 及更早标准，并根据 Boost 版本自动适配。
- 对于 Boost 1.74.0 之前的版本，提供节点句柄 insert/extract 的 hacking 支持。
- 对于 Boost 1.56.0 之前的版本，补充哈希索引的比较器（==/!=）实现，保证不同版本下的容器可比性。
- 支持哈希索引的范围 size 操作，便于与标准库和 boost 生态无缝集成。
- 通过宏和类型萃取，支持泛型编程和多索引容器类型自动推断。

## 适用场景

- 需要在项目中统一使用 Boost.MultiIndex 哈希索引的场景。
- 泛型编程、模板库开发等对哈希索引类型有适配和扩展需求的场景。
- 需要高效、统一的哈希索引 emplace、insert、extract、节点句柄、比较等操作。

## 使用示例

```cpp
#include <yggr/container/multi_index_hashed_index.hpp>

yggr::container::hashed_unique<...> idx;
auto it = yggr::container::emplace(idx, ...);
```

---

本文件为 yggdrasil 容器适配体系的多索引哈希索引适配与扩展组件，便于在模板库和泛型容器开发中统一处理哈希索引的构造、操作和兼容性问题。

