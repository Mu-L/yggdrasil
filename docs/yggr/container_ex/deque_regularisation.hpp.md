---
# 文件：deque_regularisation.hpp

## 简介

`deque_regularisation.hpp` 是 yggdrasil 项目中用于标准化（正规化）deque 容器类型的元编程工具头文件。它通过类型萃取和模板特化，自动生成“正规化”的 deque 类型，确保类型参数（元素类型、分配器、选项等）都为标准形式，便于泛型编程和容器适配。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/range_ex/range_value_ex.hpp>`：获取容器的元素类型。
  - `<yggr/container_ex/allocator_t.hpp>`：获取容器的分配器类型。
  - `<yggr/container_ex/deque_options_t.hpp>`：获取容器的选项类型。
- **核心结构体与功能**：
  1. **detail::deque_regularisation_detail<T>**
     - 默认继承自 `mplex::null_type`，表示无法正规化。
     - 针对 `Dq<T, A>` 形式的模板类型，正规化为 `Dq<元素类型, 分配器类型>`。
     - 针对 `Dq<T, A, O>` 形式的模板类型，正规化为 `Dq<元素类型, 分配器类型, 选项类型>`。
     - 其中元素类型、分配器类型、选项类型均通过相关萃取工具自动获取。
  2. **deque_regularisation<T>**
     - 对外统一接口，继承自 `deque_regularisation_detail<T>`，自动生成正规化的 deque 类型。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/deque_regularisation.hpp>

// 假设 MyDeque<T, Alloc> 或 MyDeque<T, Alloc, Options> 是自定义 deque 类型
typedef yggr::deque_regularisation<MyDeque<int, MyAlloc>>::type norm_type1; // MyDeque<元素类型, 分配器类型>
typedef yggr::deque_regularisation<MyDeque<int, MyAlloc, MyOptions>>::type norm_type2; // MyDeque<元素类型, 分配器类型, 选项类型>
```

## 适用场景

- 泛型编程中需要自动生成标准化的 deque 容器类型，确保类型参数一致性。
- 需要对不同参数形式的 deque 容器进行统一适配和处理。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



