---
# 文件：is_container.hpp

## 简介

`is_container.hpp` 是 yggdrasil 项目中用于检测类型是否为容器（container）的元编程工具头文件。它通过类型萃取和特化，实现在编译期判断任意类型 T 是否满足容器的特征，便于泛型编程中自动适配容器相关的模板实现。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/container_ex/detail/is_container_detail.hpp>`：实际实现了容器检测逻辑。
- **核心结构体与功能**：
  1. **is_container<T>**
     - 继承自 `detail::is_container_helper<T>::type`，用于判断类型 T 是否为容器类型。
     - `type` 通常为 `boost::mpl::bool_`，可通过 `is_container<T>::value` 获取布尔结果。
- **别名**：
  - 通过 `using` 语句将 `is_container` 类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/is_container.hpp>
#include <vector>
#include <map>

static_assert(yggr::is_container<std::vector<int>>::value, "vector 是容器");
static_assert(yggr::is_container<std::map<int, double>>::value, "map 是容器");
static_assert(!yggr::is_container<int>::value, "int 不是容器");
```

## 适用场景

- 泛型编程中需要自动判断类型是否为容器（如 STL 容器）。
- 需要根据类型特性自动适配不同的模板实现。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



