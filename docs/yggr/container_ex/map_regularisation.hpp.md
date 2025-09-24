---
# 文件：map_regularisation.hpp

## 简介

`map_regularisation.hpp` 是 yggdrasil 项目中用于标准化（正规化）map/multimap 容器类型的元编程工具头文件。它通过类型萃取和模板特化，自动生成“正规化”的 map 或 multimap 类型，确保类型参数（键类型、值类型、比较器、分配器、选项等）都为标准形式，便于泛型编程和容器适配。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/range_ex/range_value_ex.hpp>`：获取容器的元素类型。
  - `<yggr/container_ex/allocator_t.hpp>`：获取容器的分配器类型。
  - `<yggr/container_ex/container_compare_t.hpp>`：获取容器的比较器类型。
  - `<yggr/container_ex/container_mapped_value_t.hpp>`：获取容器的映射值类型。
  - `<yggr/container_ex/container_key_t.hpp>`：获取容器的键类型。
  - `<yggr/container_ex/map_options_t.hpp>`：获取 map 选项类型。
- **核心结构体与功能**：
  1. **detail::map_regularisation_detail<T>**
     - 默认继承自 `mplex::null_type`，表示无法正规化。
     - 针对 `MapOrMMap<K, T, C, A>` 形式的模板类型，正规化为 `MapOrMMap<键类型, 映射值类型, 比较器类型, 分配器类型>`。
     - 针对 `MapOrMMap<K, T, C, A, O>` 形式的模板类型，正规化为 `MapOrMMap<键类型, 映射值类型, 比较器类型, 分配器类型, 选项类型>`。
     - 所有类型参数均通过相关萃取工具自动获取。
  2. **map_regularisation<T>**
     - 对外统一接口，继承自 `map_regularisation_detail<T>`，自动生成正规化的 map 或 multimap 类型。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/map_regularisation.hpp>

// 假设 MyMap<K, V, Cmp, Alloc> 或 MyMap<K, V, Cmp, Alloc, Options> 是自定义 map 类型
typedef yggr::map_regularisation<MyMap<int, double, MyCmp, MyAlloc>>::type norm_type1; // MyMap<键类型, 映射值类型, 比较器类型, 分配器类型>
typedef yggr::map_regularisation<MyMap<int, double, MyCmp, MyAlloc, MyOptions>>::type norm_type2; // MyMap<键类型, 映射值类型, 比较器类型, 分配器类型, 选项类型>
```

## 适用场景

- 泛型编程中需要自动生成标准化的 map/multimap 容器类型，确保类型参数一致性。
- 需要对不同参数形式的 map/multimap 容器进行统一适配和处理。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



