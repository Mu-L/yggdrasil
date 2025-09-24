---
# 文件：has_key_t.hpp

## 简介

`has_key_t.hpp` 是 yggdrasil 项目中用于检测类型是否拥有 `key_type` 成员类型的元编程工具头文件。该文件本身只是对 `yggr::type_traits::has_key_t` 的简单封装和引入，便于在 `yggr::container_ex` 命名空间下统一使用键类型检测功能。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/type_traits/has_key_t.hpp>`：实际实现了 `has_key_t` 检测逻辑。
- **核心功能**：
  - 通过 `using ::yggr::has_key_t;`，将 `has_key_t` 类型提升到 `yggr::container_ex` 命名空间，便于后续统一调用。
- **无额外实现**，仅为命名空间适配和接口转发。

## 用法示例

```cpp
#include <yggr/container_ex/has_key_t.hpp>
#include <map>
#include <vector>

static_assert(yggr::container_ex::has_key_t<std::map<int, double>>::value, "map 有 key_type");
static_assert(!yggr::container_ex::has_key_t<std::vector<int>>::value, "vector 没有 key_type");
```

## 适用场景

- 泛型编程中需要自动判断类型是否带有 `key_type`（如 STL 的 map/set）。
- 需要根据类型特性自动适配不同的模板实现。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



