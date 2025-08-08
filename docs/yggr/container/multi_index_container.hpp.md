---
# multi_index_container.hpp 文档

## 概述

`multi_index_container.hpp` 是 yggdrasil 项目中对 Boost.MultiIndex 容器的适配与扩展头文件。该文件统一引入并适配 `boost::multi_index::multi_index_container`，并为多索引容器的类型推导、节点句柄、范围操作等提供辅助工具和宏，便于泛型编程和高效多索引容器操作。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含基础定义、类型展开、SFINAE、配置、节点句柄 traits、范围 size 支持等相关头文件。
- 统一引入 `boost::multi_index::multi_index_container`，并提升为 `yggr::container::multi_index_container`。
- 提供 `cast_to_indexed_by` 模板工具，将自定义模板类型转换为 `boost::multi_index::indexed_by` 类型，支持变参模板和宏展开，兼容 C++11 及更早标准。
- 支持节点句柄相关 hacking 和范围 size 支持，便于与标准库和 boost 生态无缝集成。
- 通过宏和类型萃取，支持泛型编程和多索引容器类型自动推断。

## 适用场景

- 需要在项目中统一使用 Boost.MultiIndex 多索引容器的场景。
- 泛型编程、模板库开发等对多索引容器类型有适配和扩展需求的场景。
- 需要高效、统一的多索引容器类型推导、节点句柄操作、范围 size 支持等。

## 使用示例

```cpp
#include <yggr/container/multi_index_container.hpp>

yggr::multi_index_container<MyType, MyIndex> c;
auto size = c.size();
```

---

本文件为 yggdrasil 容器适配体系的多索引容器适配与扩展组件，便于在模板库和泛型容器开发中统一处理多索引容器的类型推导、节点句柄和范围操作等问题。

