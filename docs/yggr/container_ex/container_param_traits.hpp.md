---
# 文件：container_param_traits.hpp

## 简介

`container_param_traits.hpp` 是 yggdrasil 项目中用于容器参数类型萃取的元编程工具头文件。它通过模板特化，为不同类型的容器参数（尤其是原生数组）提供统一的类型包装，便于泛型编程中安全、简洁地传递和处理容器参数。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/container_ex/array.hpp>`：提供 `native_array_cref` 等数组包装类型。
- **核心结构体与功能**：
  1. **container_param_traits<Container>**
     - 默认情况下，`type` 为原始类型本身。
  2. **container_param_traits<T[N]>**
     - 针对原生数组类型 `T[N]`，`type` 为 `native_array_cref<T[N]>`，即数组常量引用包装类型。
  3. **container_param_traits<native_array_cref<T[N]>>**
     - 针对已包装的数组常量引用，`type` 仍为 `native_array_cref<T[N]>`，保证类型一致性。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/container_param_traits.hpp>

typedef yggr::container_param_traits<std::vector<int>>::type vec_param; // std::vector<int>
typedef yggr::container_param_traits<int[5]>::type arr_param;           // native_array_cref<int[5]>
```

## 适用场景

- 泛型编程中需要统一处理容器参数类型，尤其是原生数组与自定义容器混用时。
- 需要保证数组参数以安全的引用方式传递，避免退化为指针。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



