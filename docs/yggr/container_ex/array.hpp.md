---
# 文件：array.hpp

## 简介

`array.hpp` 是 yggdrasil 项目中用于增强原生数组和自定义数组类型操作的头文件。它为 C++ 原生数组、`std::array`、`boost::array` 及自定义数组类型提供了统一的引用包装、比较、转换、填充、元素访问等高级功能，极大提升了数组在泛型编程中的灵活性和可用性。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：依赖于 Boost、yggr 基础设施、类型萃取、元编程等多种库。
- **核心功能**：
  1. **native_array_ref / native_array_cref**  
     - 为原生数组类型 `T[N]` 提供引用包装类，支持隐式转换、指针转换、比较（==, !=, <, <=, >, >=）等操作。
     - 支持与原生数组、其他包装类之间的比较。
  2. **make_array_ref / make_array_cref**  
     - 工厂函数，快速生成数组引用包装对象，支持原生数组、`std::array`、`boost::array`。
  3. **get**  
     - 泛型元素访问函数，支持通过索引值或类型安全索引类型访问原生数组、`std::array`、`boost::array`、自定义数组类型的元素。
     - 支持常量、非常量、右值引用等多种访问方式。
  4. **to_array**  
     - 将原生数组或其他数组类型转换为 `yggr::array` 或自定义数组类型，支持拷贝和移动语义。
  5. **fill**  
     - 填充原生数组或自定义数组类型的所有元素为指定值。
  6. **tuple_size / tuple_element**  
     - 为原生数组和自定义数组类型提供元组大小和元素类型的类型萃取，便于与元组相关的泛型编程。

## 用法示例

```cpp
#include <yggr/container_ex/array.hpp>

int arr[3] = {1, 2, 3};
auto ref = yggr::container_ex::make_array_ref(arr);
auto cref = yggr::container_ex::make_array_cref(arr);

// 比较
bool eq = (ref == arr);

// 元素访问
int v = yggr::container_ex::get<1>(arr);

// 填充
yggr::container_ex::fill(arr, 0);

// 转换为 yggr::array
auto yarr = yggr::container_ex::to_array(arr);
```

## 适用场景

- 需要对原生数组、`std::array`、`boost::array` 及自定义数组类型进行统一操作时。
- 泛型编程中需要数组的引用包装、比较、转换、填充等高级功能。
- 需要与元组相关的类型萃取和元素访问。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



