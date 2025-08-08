---
# get_map_options.hpp 文档

## 概述

`get_map_options.hpp` 是 yggdrasil 项目中用于适配 map/multimap 容器选项的辅助头文件。该文件通过模板结构体 `get_map_options` 和 `get_multimap_options`，基于底层 `get_tree_options` 实现，为 map 和 multimap 容器提供统一的选项类型适配，便于泛型容器和模板库开发。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含 `<yggr/container/detail/get_tree_options.hpp>`，用于获取底层树型容器选项适配。
- 在 `yggr::container` 命名空间下定义：
  - `get_map_options<TplArgOpt>`：继承自 `detail::get_tree_options<TplArgOpt>`，用于 map 容器选项适配。
  - `get_multimap_options<TplArgOpt>`：继承自 `detail::get_tree_options<TplArgOpt>`，用于 multimap 容器选项适配。

## 适用场景

- 需要在泛型编程中统一适配 map、multimap 容器选项的场景。
- 需要基于底层树型容器选项扩展 map/multimap 配置的场景。

## 使用示例

```cpp
#include <yggr/container/get_map_options.hpp>

typedef yggr::container::get_map_options<MyOpt>::type my_map_opt;
typedef yggr::container::get_multimap_options<MyOpt>::type my_multimap_opt;
```

---

本文件为 yggdrasil 容器适配体系的 map/multimap 选项适配组件，便于在模板库和泛型容器开发中统一处理相关配置。

