---
# 文件：container_compare_t.hpp

## 简介

`container_compare_t.hpp` 是 yggdrasil 项目中用于容器比较器类型萃取的元编程工具头文件。它通过类型萃取技术，自动从容器类型中提取 `key_compare` 和 `value_compare` 类型，便于泛型编程中对容器比较器的统一访问和适配。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/container_ex/has_compare_t.hpp>`：判断容器是否有 `key_compare` 或 `value_compare` 类型。
  - `<utility>`：标准库工具。
- **核心结构体与功能**：
  1. **container_key_compare_t_detail<T, has_key_compare>**
     - 若 T 有 `key_compare`，则 `type` 为 `T::key_compare`。
     - 否则，继承自 `mplex::null_type`。
  2. **container_value_compare_t_detail<T, has_value_compare>**
     - 若 T 有 `value_compare`，则 `type` 为 `T::value_compare`。
     - 否则，继承自 `mplex::null_type`。
  3. **container_key_compare_t<Container>**
     - 对外统一接口，继承自 `container_key_compare_t_detail<Container>`，自动提取容器的 `key_compare` 类型。
  4. **container_value_compare_t<Container>**
     - 对外统一接口，继承自 `container_value_compare_t_detail<Container>`，自动提取容器的 `value_compare` 类型。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/container_compare_t.hpp>
#include <set>

typedef yggr::container_key_compare_t<std::set<int>>::type key_cmp; // std::set<int>::key_compare
typedef yggr::container_value_compare_t<std::set<int>>::type value_cmp; // std::set<int>::value_compare
```

## 适用场景

- 泛型编程中需要自动获取容器的比较器类型（如 `std::set`、`std::map` 等）。
- 需要对不同容器的比较器进行统一适配和处理。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



