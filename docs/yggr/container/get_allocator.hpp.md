---
# get_allocator.hpp 文档

## 概述

`get_allocator.hpp` 是 yggdrasil 项目中用于统一获取容器分配器的适配头文件。该文件通过类型萃取和 SFINAE 技术，自动判断容器类型是否有分配器及 `get_allocator` 方法，并提供统一的 `get_allocator` 和 `create_empty_object_of_allocator` 泛型接口，便于泛型编程和容器适配。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含分配器类型萃取、分配器检测、SFINAE 相关头文件。
- 通过 `boost::enable_if`、`boost::disable_if`、`boost::mpl` 等工具，自动判断容器类型特性。
- 提供 `get_allocator(const T&)` 泛型函数，根据容器类型特性自动选择：
  - 有分配器类型且有 `get_allocator` 方法：直接调用
  - 有分配器类型但无 `get_allocator` 方法：返回默认分配器对象
  - 无分配器类型：返回默认分配器对象
- 提供 `create_empty_object_of_allocator(const T&)` 泛型函数，根据分配器类型是否为 `null_type`，自动选择构造方式：
  - 分配器为 `null_type`：直接默认构造
  - 否则：用分配器构造

- 将 `get_allocator` 和 `create_empty_object_of_allocator` 提升到 yggr 命名空间，便于全局统一调用。

## 适用场景

- 需要对不同容器类型统一获取分配器的场景。
- 泛型算法、模板库开发中对分配器适配的需求。
- 需要根据分配器类型自动选择对象构造方式的场景。

## 使用示例

```cpp
#include <yggr/container/get_allocator.hpp>

std::vector<int> v;
auto alloc = yggr::get_allocator(v);

auto empty_obj = yggr::create_empty_object_of_allocator(v);
```

---

如需扩展支持自定义容器，请确保实现了分配器类型萃取和 `get_allocator` 检测。

