---
# 文件：get_element.hpp

## 简介

`get_element.hpp` 是 yggdrasil 项目中用于数组（`std::array`、`boost::array`）首尾元素访问的工具头文件。它为常见的定长数组容器提供了统一的首元素和尾元素获取接口，便于泛型编程中安全、简洁地访问数组两端的数据。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/utility/get_element_default.hpp>`：默认元素获取工具。
  - `<yggr/container/array.hpp>`：自定义数组类型支持。
- **核心函数**：
  1. **get_first_element / get_last_element**
     - 针对 `std::array<T, N>`（C++11 及以上）和 `boost::array<T, N>`，分别提供获取首元素和尾元素的重载函数。
     - 支持非常量和常量数组的访问。
     - 返回类型为元素的引用或常量引用。
- **别名**：
  - 通过 `using` 语句将上述函数提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/get_element.hpp>
#include <array>
#include <boost/array.hpp>

std::array<int, 3> arr1 = {1, 2, 3};
int first1 = yggr::get_first_element(arr1); // 1
int last1 = yggr::get_last_element(arr1);   // 3

boost::array<int, 3> arr2 = {4, 5, 6};
int first2 = yggr::get_first_element(arr2); // 4
int last2 = yggr::get_last_element(arr2);   // 6
```

## 适用场景

- 泛型编程中需要统一访问数组首尾元素，兼容 `std::array` 和 `boost::array`。
- 需要安全、简洁地获取定长数组的第一个和最后一个元素。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



