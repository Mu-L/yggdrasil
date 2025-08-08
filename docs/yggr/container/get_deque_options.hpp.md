---
# get_deque_options.hpp 文档

## 概述

`get_deque_options.hpp` 是 yggdrasil 项目中用于适配 Boost 版本下 deque 容器选项的辅助头文件。该文件通过模板结构体 `get_deque_options`，根据 Boost 版本自动选择合适的 deque 配置选项类型，保证在不同 Boost 版本下的兼容性和统一性。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含 `<yggr/container/options.hpp>`，用于获取相关选项定义。
- 在 `yggr::container` 命名空间下定义模板结构体 `get_deque_options<TplArgOpt>`，用于根据模板参数和 Boost 版本选择 deque 配置类型。
- 对于 Boost 1.71.0 之前的版本，`type` 为 `deque_null_opt`（无选项）。
- 对于 Boost 1.71.0 及之后的版本，`type` 为 `boost::container::get_deque_opt<TplArgOpt>::type`，支持更多自定义选项。

## 适用场景

- 需要在不同 Boost 版本下统一适配 deque 容器选项的场景。
- 泛型容器、模板库开发中对 deque 配置选项的自动适配需求。

## 使用示例

```cpp
#include <yggr/container/get_deque_options.hpp>

typedef yggr::container::get_deque_options<MyOpt>::type my_deque_opt;
```

---

本文件为 yggdrasil 容器适配体系的 Boost 兼容性辅助组件，便于在不同 Boost 版本下安全、统一地获取 deque 容器选项类型。

