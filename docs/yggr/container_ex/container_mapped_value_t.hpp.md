---
# 文件：container_mapped_value_t.hpp

## 简介

`container_mapped_value_t.hpp` 是 yggdrasil 项目中用于容器映射值类型和键类型萃取的元编程工具头文件。它通过类型萃取技术，自动从容器类型中提取映射容器的 value（如 `std::map` 的 mapped_type）和 key（如 `std::map` 的 key_type），便于泛型编程中对容器键值类型的统一访问和适配。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/container_ex/has_mapped_t.hpp>`：判断容器是否有 mapped_type。
  - `<boost/range/value_type.hpp>`：获取容器的元素类型。
- **核心结构体与功能**：
  1. **detail::get_mapped_value_t<T> / get_mapped_key_t<T>**
     - 默认 `type` 为 T 本身。
     - 若 T 为 Pair（如 `std::pair<F, S>`），则 `get_mapped_value_t` 的 `type` 为 S，`get_mapped_key_t` 的 `type` 为 F。
  2. **container_mapped_value_t<Container>**
     - 若容器有 mapped_type，则 `type` 为元素类型的 mapped value，否则为元素类型本身。
     - 同时定义 `value_type`，为容器的元素类型。
  3. **container_mapped_key_t<Container>**
     - 若容器有 mapped_type，则 `type` 为元素类型的 key，否则为元素类型本身。
     - 同时定义 `value_type`，为容器的元素类型。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/container_mapped_value_t.hpp>
#include <map>
#include <vector>

typedef yggr::container_mapped_value_t<std::map<int, double>>::type map_mapped; // double
typedef yggr::container_mapped_key_t<std::map<int, double>>::type map_key;      // int
typedef yggr::container_mapped_value_t<std::vector<int>>::type vec_val;         // int
typedef yggr::container_mapped_key_t<std::vector<int>>::type vec_key;           // int
```

## 适用场景

- 泛型编程中需要自动获取容器的 value_type、mapped_type 或 key_type（如 `std::map`、`std::vector` 等）。
- 需要对不同容器的键值类型进行统一适配和处理。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



