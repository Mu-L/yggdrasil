---
# 文件：has_get_allocator_function.hpp

## 简介

`has_get_allocator_function.hpp` 是 yggdrasil 项目中用于检测类型是否拥有 `get_allocator` 成员函数的元编程工具头文件。它通过 SFINAE 技术和类型萃取，实现在编译期判断任意类型 T 是否定义了 `get_allocator` 成员函数（返回类型为 `allocator_t<T>::type`），便于泛型编程中自动适配带有或不带有分配器接口的类型。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/container_ex/allocator_t.hpp>`：分配器类型萃取工具。
  - Boost MPL：元编程布尔类型和条件判断。
- **核心结构体与功能**：
  1. **detail::_has_get_allocator_function<Container>**
     - 通过 SFINAE 检测 `Container` 是否有 `allocator_t<T>::type get_allocator() const` 成员函数。
     - 若存在，`chk_foo` 返回 `true_type`，否则返回 `false_type`。
     - `type` 为 `boost::mpl::bool_`，值为 true 表示存在该成员函数，false 表示不存在。
  2. **has_get_allocator_function<Container>**
     - 对外统一接口，继承自 `_has_get_allocator_function<Container>::type`，可直接用于类型判断。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/has_get_allocator_function.hpp>
#include <vector>
#include <string>

static_assert(yggr::has_get_allocator_function<std::vector<int>>::value, "vector 有 get_allocator()");
static_assert(!yggr::has_get_allocator_function<int>::value, "int 没有 get_allocator()");
```

## 适用场景

- 泛型编程中需要自动判断类型是否带有分配器接口（如 STL 容器）。
- 需要根据类型特性自动适配不同的模板实现。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



