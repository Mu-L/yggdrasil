---
# 文件：allocator_traits.hpp

## 简介

`allocator_traits.hpp` 是 yggdrasil 项目中用于分配器特性适配的头文件，主要作用是将 Boost 的 `allocator_traits` 引入到 `yggr::container_ex` 命名空间下，便于统一管理和使用分配器相关的 trait 功能。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/base/yggrdef.h>`：基础定义。
  - `<boost/container/allocator_traits.hpp>`：Boost 分配器特性实现。
- **核心定义**：
  - `using boost::container::allocator_traits;`  
    直接将 Boost 的 `allocator_traits` 类型引入 `yggr::container_ex` 命名空间，方便后续代码统一使用。

## 用法示例

```cpp
#include <yggr/container_ex/allocator_traits.hpp>
#include <vector>

typedef std::allocator<int> my_allocator;
typedef yggr::container_ex::allocator_traits<my_allocator> my_traits;

// 现在可以通过 my_traits 访问 allocator_traits 的所有静态方法和类型定义
```

## 适用场景

- 需要对自定义或标准分配器进行 trait 操作时，统一使用 `yggr::container_ex::allocator_traits`。
- 便于后续切换或扩展分配器特性实现（如从 Boost 切换到标准库实现）。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



