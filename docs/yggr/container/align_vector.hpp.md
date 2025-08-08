---
# align_vector.hpp 文档

## 概述

`align_vector.hpp` 是 yggdrasil 项目中的一个头文件，主要用于在 MSVC 2010 及更早版本下，为 `std::vector` 提供类型对齐包装。其核心思想是通过 `align_wrapper` 模板结构体对类型进行包裹，并为 `std::vector<align_wrapper<T>>` 提供特化实现，从而解决老版本 MSVC STL 在类型对齐和移动语义上的兼容性问题。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容

### 1. 头文件保护

使用宏 `__YGGR_CONTAINER_ALIGN_VECTOR_HPP__` 防止头文件重复包含。

### 2. 依赖

- `<vector>`：标准容器 vector
- `<yggr/base/yggrdef.h>`：yggdrasil 基础定义
- `<yggr/move/move.hpp>`、`<yggr/mplex/static_assert.hpp>`、`<yggr/container/basic_function_adapter.hpp>`：yggdrasil 内部工具
- `<boost/type_traits/is_same.hpp>`：类型判断
- 仅在 MSVC 2010 及更早版本下启用特殊实现

### 3. align_wrapper 模板

```cpp
template<typename T, typename Nil = void>
struct align_wrapper
{
public:
    typedef T value_type;
};
```
- 用于对类型 T 进行包裹，便于后续 vector 特化。

### 4. 宏定义

- `YGGR_ALIGN_WRAPPER(__x__)`：对类型进行 align_wrapper 包裹
- `YGGR_ALIGN_VECTOR(__x__, __alloc__)`：生成带对齐包装的 vector 类型

### 5. std::vector 特化

对 `std::vector<align_wrapper<T>, Alloc>` 进行特化，重载了构造、赋值、插入、删除、移动等操作，保证在老版本 MSVC 下的兼容性和正确性。

- 支持拷贝、移动构造与赋值
- 支持 push_back、emplace_back、insert、erase、swap、resize、reserve 等常用操作
- 内部实现了内存分配、元素构造、移动、销毁等底层细节
- 兼容 C++11 部分特性（如 data、shrink_to_fit 等）

### 6. 兼容性处理

- 仅在 `defined(_MSC_VER) && !(_MSC_VER >1600)` 条件下启用特化
- 其他编译器或新版本 MSVC 下，宏直接退化为普通 vector

### 7. 结尾

- 头文件保护宏结束

---

## 适用场景

- 主要用于 MSVC 2010 及更早版本，解决 STL vector 在类型对齐、移动语义等方面的兼容性问题。
- 新版本编译器或其他平台无需特殊处理，直接使用标准 vector。

## 使用示例

```cpp
// 定义一个对齐 vector
YGGR_ALIGN_VECTOR(MyType, std::allocator<MyType>) my_vec;
```

---

如需进一步了解具体实现细节，可查阅源码注释及相关 yggdrasil 工具头文件。

