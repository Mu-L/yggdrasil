---
# 文件：has_iterator_t.hpp

## 简介

`has_iterator_t.hpp` 是 yggdrasil 项目中用于检测类型是否拥有各种迭代器类型（如 iterator、const_iterator、reverse_iterator、const_reverse_iterator）的元编程工具头文件。它通过 SFINAE 技术和类型萃取，实现在编译期判断任意类型 T 是否定义了这些迭代器类型，便于泛型编程中自动适配带有或不带有迭代器的类型。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/type_traits/native_t.hpp>`：类型原生化工具。
  - Boost MPL：元编程布尔类型和逻辑运算。
- **核心结构体与功能**：
  1. **detail::_has_non_const_iterator_t / _has_const_iterator_t / _has_non_const_reverse_iterator_t / _has_const_reverse_iterator_t**
     - 通过 SFINAE 检测类型是否分别拥有 `iterator`、`const_iterator`、`reverse_iterator`、`const_reverse_iterator` 成员类型。
     - 若存在，`chk_foo` 返回 `true_type`，否则返回 `false_type`。
     - `type` 为 `boost::mpl::bool_`，值为 true 表示存在该成员类型，false 表示不存在。
  2. **has_non_const_iterator_t / has_const_iterator_t / has_non_const_reverse_iterator_t / has_const_reverse_iterator_t**
     - 对外统一接口，分别继承自对应的 detail 检测结构体的 `type`，可直接用于类型判断。
  3. **has_iterator_t**
     - 只要上述四种迭代器类型中有任意一种存在，则为 true。
     - 便于统一判断类型是否为“可迭代容器”。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/has_iterator_t.hpp>
#include <vector>
#include <set>
#include <string>

static_assert(yggr::has_iterator_t<std::vector<int>>::value, "vector 有迭代器");
static_assert(!yggr::has_iterator_t<int>::value, "int 没有迭代器");
```

## 适用场景

- 泛型编程中需要自动判断类型是否带有迭代器（如 STL 容器）。
- 需要根据类型特性自动适配不同的模板实现。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



