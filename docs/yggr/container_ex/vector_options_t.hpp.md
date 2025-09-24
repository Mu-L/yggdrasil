---
# 文件：vector_options_t.hpp

## 简介

`vector_options_t.hpp` 是 yggdrasil 项目中用于从类型 T 中萃取 vector 容器选项的元编程工具头文件。它通过类型展开和模板特化，自动获取带有特定模板参数数量（如 3 个参数）的类型的 vector 选项类型，便于泛型编程中对 vector 容器参数的统一访问和适配。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/mplex/typename_expand.hpp>`：类型展开工具。
  - `<yggr/range_ex/range_size_ex.hpp>`：获取容器大小类型。
  - `<yggr/container/get_vector_options.hpp>`：获取 vector 选项的工具。
- **核心结构体与功能**：
  1. **detail::vector_options_t_detail<T, tpl_arg_size>**
     - 默认继承自 `mplex::null_type`，表示无法获取选项。
     - 当类型 T 的模板参数数量为 3 时，`type` 为 `container::get_vector_options<tpl_arg_options_type, now_size_type>::type`，即通过类型展开获取第 3 个模板参数和当前容器大小类型作为 vector 选项类型。
  2. **vector_options_t<T>**
     - 对外统一接口，继承自 `vector_options_t_detail<T>`，自动提取类型 T 的 vector 选项类型。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/vector_options_t.hpp>

// 假设 MyVector<T, Alloc, Options> 是一个有3个模板参数的类型
typedef yggr::vector_options_t<MyVector<int, MyAlloc, MyOptions>>::type options_type; // MyOptions
```

## 适用场景

- 泛型编程中需要自动获取自定义 vector 容器的选项类型（如第三个模板参数）。
- 需要对不同 vector 容器的选项参数进行统一适配和处理。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



