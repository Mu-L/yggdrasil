---
# deque.hpp 文档

## 概述

`deque.hpp` 是 yggdrasil 项目中用于双端队列（deque）容器适配的头文件。该文件根据项目配置，自动选择使用标准库（`std::deque`）或 Boost（`boost::deque`）实现，并对分配器等相关类型进行统一适配，方便在不同平台和库环境下无缝切换和泛型编程。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含 yggdrasil 基础定义和容器选择相关头文件。
- 根据宏定义（如 `YGGR_USE_BOOST_CONTAINER` 或 `YGGR_USE_STL_CONTAINER`），自动选择 `std::deque` 或 `boost::deque` 作为 `yggr::container::deque` 的实现。
- 适配分配器类型，保证容器在不同实现下的分配器一致性。
- 可能包含类型萃取、辅助工具或兼容性适配代码，便于泛型算法和容器操作。

## 适用场景

- 需要跨平台、跨标准库环境下统一双端队列容器类型的场景。
- 需要在项目中灵活切换标准库或 Boost 实现的 deque。
- 泛型编程、模板库开发等对容器类型有适配需求的场景。

## 使用示例

```cpp
#include <yggr/container/deque.hpp>

yggr::container::deque<int> dq;
dq.push_back(1);
dq.push_front(2);
```

---

如需进一步了解具体实现细节，可查阅源码及相关 yggdrasil 容器适配头文件。

