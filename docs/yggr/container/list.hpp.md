---
# list.hpp 文档

## 概述

`list.hpp` 是 yggdrasil 项目中用于统一适配 `std::list` 和 `boost::container::list` 的容器适配头文件。该文件根据编译环境和 Boost 版本，自动选择合适的 list 实现，并为 list 容器提供 emplace、erase、remove、unique、swap 等统一接口和兼容性扩展，支持泛型编程和高效容器操作。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含基础定义、容器选择、SFINAE、类型萃取、辅助宏等相关头文件。
- 兼容 `std::list` 和 `boost::container::list`，并根据 Boost 版本自动适配。
- 提供统一的 emplace、emplace_front、emplace_back、erase、erase_if、remove、remove_if、unique 等接口，支持变参模板和宏展开，兼容 C++11 及更早标准。
- 支持 isomeric same 类型判断，保证不同模板参数下的 list 类型安全转换和操作。
- 对于 Boost 1.70 及以上版本，提供自定义 detail::list 实现，支持更多构造、赋值、swap、remove、unique 等操作，并与 boost::container::list 互操作。
- 提供 swap 支持和 range size 支持，便于与标准库和 boost 生态无缝集成。
- 通过宏和类型萃取，支持泛型编程和容器类型自动推断。

## 适用场景

- 需要跨平台、跨标准库环境下统一 list 容器类型的场景。
- 需要在项目中灵活切换标准库或 Boost 实现的 list。
- 泛型编程、模板库开发等对容器类型有适配和扩展需求的场景。
- 需要高效、统一的 list 容器操作接口（如 emplace、erase、remove、unique、swap 等）。

## 使用示例

```cpp
#include <yggr/container/list.hpp>

yggr::list<int> l;
l.push_back(1);
l.emplace_back(2);
l.remove(1);
l.unique();
```

---

本文件为 yggdrasil 容器适配体系的 list 适配与扩展组件，便于在模板库和泛型容器开发中统一处理 list 类型的构造、操作和兼容性问题。

