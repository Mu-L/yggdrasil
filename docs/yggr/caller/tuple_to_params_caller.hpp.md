---
# tuple_to_params_caller.hpp

该头文件属于 yggdrasil 项目，实现了将 tuple（元组）类型的内容作为独立参数传递给可调用对象（如函数、函数对象、lambda 等）的工具。支持 `std::tuple`、`boost::tuple` 以及 `yggr::tuple`，并兼容 C++11 及更早版本。

## 主要功能

- **to_params_call**：将 tuple 的每个元素作为独立参数传递给 handler。
- 支持 `std::tuple`、`boost::tuple`、`yggr::tuple` 及其 cons 结构。
- 自动推断 handler 的返回类型。
- 兼容可变参数模板和预处理器宏两种实现方式。

## 主要接口

```cpp
// std::tuple
template<typename Handler, typename ...T>
typename boost::enable_if<
    is_callable<Handler>,
    typename func::foo_t_info<Handler>::result_type
>::type
to_params_call(const Handler& handler, std::tuple<T...>& t);

// boost::tuple
template<typename Handler, typename ...T>
typename boost::enable_if<
    is_callable<Handler>,
    typename func::foo_t_info<Handler>::result_type
>::type
to_params_call(const Handler& handler, boost::tuple<T...>& t);

// yggr::tuple
template<typename Handler, typename ...T>
typename boost::enable_if<
    is_callable<Handler>,
    typename func::foo_t_info<Handler>::result_type
>::type
to_params_call(const Handler& handler, yggr::tuple<T...>& t);
```

- **参数说明**：
  - `handler`：可调用对象（函数、函数对象、lambda 等）。
  - `t`：tuple 类型对象，可以是 `std::tuple`、`boost::tuple`、`yggr::tuple` 或其 cons 结构。
- **返回值**：handler 的返回类型。

## 实现细节

- 对于支持 C++11 可变参数模板的编译器，使用 `index_sequence` 展开 tuple 元素。
- 对于不支持可变参数模板的编译器，使用预处理器宏生成展开代码。
- 内部通过 `tuple_to_params_call_helper<N>` 实现参数展开。
- 支持常量和非常量 tuple。

## 典型用法

```cpp
std::tuple<int, double, std::string> t(1, 2.5, "hello");
auto handler = [](int a, double b, const std::string& c) { /* ... */ };
yggr::caller::to_params_call(handler, t); // handler(1, 2.5, "hello")
```

## 依赖

- yggrdef.h
- bind.hpp
- is_callable.hpp
- foo_t_info.hpp
- tuple.hpp
- integer_sequence.hpp（C++11）
- Boost.TypeTraits、Boost.Utility

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法或扩展说明，请参考源代码注释和 yggdrasil 项目文档。