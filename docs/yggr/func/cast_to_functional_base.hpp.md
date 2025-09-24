---
cast_to_functional_base.hpp 文档

---

# 文件：cast_to_functional_base.hpp

## 简介
该头文件为 yggdrasil 项目中函数对象类型兼容性工具，主要用于将类型 T 自动转换为对应的 STL 函数基类（如 `std::unary_function`、`std::binary_function`）的继承结构，便于与标准库算法和旧式接口兼容。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- null_t.hpp
- functional_args_size.hpp
- Boost MPL 相关头文件

### 主要模板
#### 1. `cast_to_functional_base<T>`
- 根据类型 T 的参数个数和是否为函数对象，自动继承自对应的 `make_base_functional` 特化（如一元、二元函数）。
- 若 T 不是函数对象或参数数量不匹配，则继承自 `mplex::null_type`。

#### 2. `detail::make_base_functional_if`
- 内部辅助模板，根据参数数量和类型特性选择继承结构。
- 针对 C++17 之前的环境，分别为一元和二元函数对象做了特化。

### 用法说明
- 该工具适用于需要自动为自定义函数对象补充 STL 兼容基类的场景，便于与标准库算法、容器等配合使用。
- 支持自动检测参数数量和类型特性，兼容 C++11/14/17 及更早标准。

---



