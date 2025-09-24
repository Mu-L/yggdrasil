---
# 文件：is_static_container.hpp

## 简介

`is_static_container.hpp` 是 yggdrasil 项目中用于检测类型是否为“静态容器”（如原生数组、`boost::array`、`std::array` 等）的元编程工具头文件。它通过类型萃取和特化，实现在编译期判断任意类型 T 是否为静态容器，便于泛型编程中自动适配静态容器相关的模板实现。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/container_ex/has_value_t.hpp>`：检测类型是否有 `value_type`。
  - `<yggr/container_ex/has_iterator_t.hpp>`：检测类型是否有迭代器。
  - Boost TypeTraits：如 `boost::is_array`。
- **核心结构体与功能**：
  1. **detail::is_static_container_helper<T>**
     - 对于原生数组类型，直接继承自 `boost::is_array<T>`，判断是否为数组。
     - 对于类似 `C<T, N>` 形式的模板类型（如 `boost::array`、`std::array`），只有同时拥有 `value_type` 和迭代器类型时才判定为静态容器。
  2. **is_static_container<T>**
     - 对外统一接口，继承自 `is_static_container_helper<T>`，可通过 `is_static_container<T>::value` 获取布尔结果。
- **别名**：
  - 通过 `using` 语句将 `is_static_container` 类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/is_static_container.hpp>
#include <array>
#include <vector>

static_assert(yggr::is_static_container<int[5]>::value, "int[5] 是静态容器");
static_assert(yggr::is_static_container<std::array<int, 3>>::value, "std::array 是静态容器");
static_assert(!yggr::is_static_container<std::vector<int>>::value, "vector 不是静态容器");
```

## 适用场景

- 泛型编程中需要自动判断类型是否为静态容器（如原生数组、`boost::array`、`std::array`）。
- 需要根据类型特性自动适配不同的模板实现。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



