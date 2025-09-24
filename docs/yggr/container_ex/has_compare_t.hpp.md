---
# 文件：has_compare_t.hpp

## 简介

`has_compare_t.hpp` 是 yggdrasil 项目中用于检测类型是否拥有 `key_compare` 或 `value_compare` 成员类型的元编程工具头文件。它通过 SFINAE 技术和类型萃取，实现在编译期判断任意类型 T 是否定义了 `key_compare` 或 `value_compare`，便于泛型编程中自动适配带有或不带有比较器的类型。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/type_traits/native_t.hpp>`：类型原生化工具。
  - Boost MPL：元编程布尔类型和条件判断。
- **核心结构体与功能**：
  1. **detail::_has_key_compare_t<Container>**
     - 通过 SFINAE 检测 `Container::key_compare` 是否存在。
     - 若存在，`chk_foo` 返回 `true_type`，否则返回 `false_type`。
     - `type` 为 `boost::mpl::bool_`，值为 true 表示存在 `key_compare`，false 表示不存在。
  2. **detail::_has_value_compare_t<Container>**
     - 通过 SFINAE 检测 `Container::value_compare` 是否存在。
     - 逻辑同上。
  3. **has_key_compare_t<Container> / has_value_compare_t<Container>**
     - 对外统一接口，分别继承自 `_has_key_compare_t<Container>::type` 和 `_has_value_compare_t<Container>::type`，可直接用于类型判断。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/has_compare_t.hpp>
#include <set>
#include <vector>

static_assert(yggr::has_key_compare_t<std::set<int>>::value, "set 有 key_compare");
static_assert(!yggr::has_key_compare_t<std::vector<int>>::value, "vector 没有 key_compare");
```

## 适用场景

- 泛型编程中需要自动判断类型是否带有比较器（如 STL 的 set/map）。
- 需要根据类型特性自动适配不同的模板实现。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



