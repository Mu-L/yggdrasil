---
# 文件：is_allocator.hpp

## 简介

`is_allocator.hpp` 是 yggdrasil 项目中用于检测类型是否为分配器（allocator）的元编程工具头文件。它通过类型萃取和特化，实现在编译期判断任意类型 T 是否满足分配器的特征，便于泛型编程中自动适配分配器相关的模板实现。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/container_ex/detail/is_allocator_detail.hpp>`：实际实现了分配器检测逻辑。
- **核心结构体与功能**：
  1. **is_allocator<T>**
     - 继承自 `detail::is_allocator_impl<T>::type`，用于判断类型 T 是否为分配器类型。
     - `type` 通常为 `boost::mpl::bool_`，可通过 `is_allocator<T>::value` 获取布尔结果。
- **别名**：
  - 通过 `using` 语句将 `is_allocator` 类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/is_allocator.hpp>
#include <memory>

static_assert(yggr::is_allocator<std::allocator<int>>::value, "std::allocator 是分配器");
static_assert(!yggr::is_allocator<int>::value, "int 不是分配器");
```

## 适用场景

- 泛型编程中需要自动判断类型是否为分配器（如 STL allocator）。
- 需要根据类型特性自动适配不同的模板实现。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



