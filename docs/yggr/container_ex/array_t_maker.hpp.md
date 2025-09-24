---
# 文件：array_t_maker.hpp

## 简介

`array_t_maker.hpp` 是 yggdrasil 项目中用于数组类型萃取和类型生成的工具头文件。它通过一组模板结构体，方便地为任意类型 T 和长度 N 生成数组、数组引用、数组指针等类型，简化泛型编程中对数组类型的处理。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/base/yggrdef.h>`：基础定义。
  - `<boost/type_traits/remove_reference.hpp>`：类型萃取辅助（虽然本文件未直接用到）。
- **核心结构体**：
  - `array_reference_t_maker<T, N>`：生成类型 `T(&)[N]`，即长度为 N 的 T 类型数组的引用类型。
  - `array_const_reference_t_maker<T, N>`：生成类型 `const T(&)[N]`，即长度为 N 的 const T 类型数组的引用类型。
  - `array_pointer_t_maker<T, N>`：生成类型 `T(*)[N]`，即长度为 N 的 T 类型数组的指针类型。
  - `array_const_pointer_t_maker<T, N>`：生成类型 `const T(*)[N]`，即长度为 N 的 const T 类型数组的指针类型。
  - `array_t_maker<T, N>`：生成类型 `T[N]`，即长度为 N 的 T 类型数组。
- **别名**：
  - 通过 `using` 语句将上述结构体提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/array_t_maker.hpp>

typedef yggr::array_reference_t_maker<int, 5>::type      int_array_ref;   // int (&)[5]
typedef yggr::array_const_reference_t_maker<int, 5>::type const_int_array_ref; // const int (&)[5]
typedef yggr::array_pointer_t_maker<int, 5>::type        int_array_ptr;   // int (*)[5]
typedef yggr::array_const_pointer_t_maker<int, 5>::type  const_int_array_ptr; // const int (*)[5]
typedef yggr::array_t_maker<int, 5>::type                int_array;       // int[5]
```

## 适用场景

- 泛型编程中需要根据类型和长度自动生成数组相关类型。
- 需要对数组进行引用、指针等操作时，统一类型定义，提升代码可读性和可维护性。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

