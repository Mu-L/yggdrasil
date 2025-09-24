---
# 文件：allocator_t.hpp

## 简介

`allocator_t.hpp` 是 yggdrasil 项目中用于类型萃取（type traits）的一个头文件，主要用于从类型 T 中提取其分配器类型（allocator_type），以便在泛型编程中自动适配带有或不带有分配器的类型。

## 主要内容

- **命名空间**：所有内容均位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/base/yggrdef.h>`：基础定义。
  - `<yggr/mplex/null_t.hpp>`：空类型定义。
  - `<yggr/container_ex/has_allocator_t.hpp>`：判断类型是否有 allocator_type。
  - `<memory>`：标准库内存分配相关。
- **核心结构体**：
  - `allocator_t_detail<T, has_allocator>`：模板特化结构体，根据类型 T 是否有 `allocator_type` 进行不同处理。
    - `has_allocator = true` 时，`type` 为 `T::allocator_type`。
    - `has_allocator = false` 时，继承自 `mplex::null_type`，表示无分配器。
  - `allocator_t<T>`：对外统一接口，继承自 `allocator_t_detail<T, has_allocator_t<T>::value>`，自动判断并提取分配器类型。
- **别名**：
  - `using container_ex::allocator_t;` 便于外部直接使用 `allocator_t`。

## 用法示例

```cpp
#include <yggr/container_ex/allocator_t.hpp>

struct MyTypeWithAllocator {
    using allocator_type = std::allocator<int>;
};

struct MyTypeWithoutAllocator {};

// 提取分配器类型
using Alloc1 = yggr::allocator_t<MyTypeWithAllocator>::type; // std::allocator<int>
using Alloc2 = yggr::allocator_t<MyTypeWithoutAllocator>::type; // mplex::null_type
```

## 适用场景

- 泛型容器或算法中，需要自动适配带有或不带有分配器的类型。
- 需要类型萃取和 SFINAE 技术的高级 C++ 模板编程。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

