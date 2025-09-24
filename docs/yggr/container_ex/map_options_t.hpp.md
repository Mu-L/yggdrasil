---
# 文件：map_options_t.hpp

## 简介

`map_options_t.hpp` 是 yggdrasil 项目中用于从类型 T 中萃取 map/multimap 容器选项的元编程工具头文件。它通过类型展开和模板特化，自动获取带有特定模板参数数量（如 5 个参数）的类型的 map 选项类型，便于泛型编程中对 map、multimap 容器参数的统一访问和适配。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/mplex/typename_expand.hpp>`：类型展开工具。
  - `<yggr/container/get_map_options.hpp>`：获取 map 选项的工具。
- **核心结构体与功能**：
  1. **detail::map_options_t_detail<T, tpl_arg_size>**
     - 默认继承自 `mplex::null_type`，表示无法获取选项。
     - 当类型 T 的模板参数数量为 5 时，`type` 为 `container::detail::get_tree_options<...>::type`，即通过类型展开获取第 5 个模板参数作为 map 选项类型。
  2. **map_options_t<T> / multimap_options_t<T>**
     - 对外统一接口，继承自 `map_options_t_detail<T>`，自动提取类型 T 的 map 或 multimap 选项类型。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/map_options_t.hpp>

// 假设 MyMap<K, V, Cmp, Alloc, Options> 是一个有5个模板参数的类型
typedef yggr::map_options_t<MyMap<int, double, MyCmp, MyAlloc, MyOptions>>::type options_type; // MyOptions
```

## 适用场景

- 泛型编程中需要自动获取自定义 map/multimap 容器的选项类型（如第五个模板参数）。
- 需要对不同 map/multimap 容器的选项参数进行统一适配和处理。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



