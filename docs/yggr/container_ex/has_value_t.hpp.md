---
# 文件：has_value_t.hpp

## 简介

`has_value_t.hpp` 是 yggdrasil 项目中用于检测类型是否拥有 `value_type` 成员类型的元编程工具头文件。该文件本身只是对 `yggr::type_traits::has_value_t` 的简单封装和引入，便于在 `yggr::container_ex` 命名空间下统一使用值类型检测功能。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/type_traits/has_value_t.hpp>`：实际实现了 `has_value_t` 检测逻辑。
- **核心功能**：
  - 通过 `using ::yggr::has_value_t;`，将 `has_value_t` 类型提升到 `yggr::container_ex` 命名空间，便于后续统一调用。
- **无额外实现**，仅为命名空间适配和接口转发。

## 用法示例

```cpp
#include <yggr/container_ex/has_value_t.hpp>
#include <vector>
#include <map>

static_assert(yggr::container_ex::has_value_t<std::vector<int>>::value, "vector 有 value_type");
static_assert(yggr::container_ex::has_value_t<std::map<int, double>>::value, "map 有 value_type");
static_assert(!yggr::container_ex::has_value_t<int>::value, "int 没有 value_type");
```

## 适用场景

- 泛型编程中需要自动判断类型是否带有 `value_type`（如 STL 容器）。
- 需要根据类型特性自动适配不同的模板实现。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



