---
# 文件：container_key_t.hpp

## 简介

`container_key_t.hpp` 是 yggdrasil 项目中用于容器键类型（key_type）萃取的元编程工具头文件。它通过类型萃取技术，自动从容器类型中提取 `key_type`，并在没有 `key_type` 的情况下回退到映射值类型，便于泛型编程中对容器键类型的统一访问和适配。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/container_ex/has_key_t.hpp>`：判断容器是否有 `key_type`。
  - `<yggr/container_ex/container_mapped_value_t.hpp>`：获取映射容器的 key 类型。
- **核心结构体与功能**：
  1. **container_key_t_detail<Container, b_has_key_t>**
     - 若容器有 `key_type`，则 `type` 为 `Container::key_type`。
     - 否则，继承自 `container_mapped_key_t<Container>`，用于映射容器（如 `std::map`）。
  2. **container_key_t<Container>**
     - 对外统一接口，继承自 `container_key_t_detail<Container>`，自动提取容器的键类型。
     - 同时定义 `value_type`，为容器的元素类型（`boost::range_value<Container>::type`）。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/container_key_t.hpp>
#include <map>
#include <vector>

typedef yggr::container_key_t<std::map<int, double>>::type map_key; // int
typedef yggr::container_key_t<std::vector<int>>::type vec_key; // int（回退到映射值类型或其他逻辑）
```

## 适用场景

- 泛型编程中需要自动获取容器的键类型（如 `std::map`、`std::set` 等）。
- 需要对不同容器的键类型进行统一适配和处理。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



