---
# packet_info_to_params_caller.hpp

该头文件属于 yggdrasil 项目，实现了将 `packet::packet_info` 类型的数据包内容作为参数传递给可调用对象（如函数、函数对象、lambda 等）的工具。其核心思想是将 `packet_info` 内部的元组（tuple）解包为独立参数，自动调用目标 handler。

## 主要功能

- **to_params_call**：将 `packet::packet_info` 的内容解包为参数，传递给 handler。
- 支持 C++11 可变参数模板和宏展开两种实现方式，兼容不同编译器。
- 自动推断 handler 的返回类型。

## 主要接口

```cpp
template<typename Handler, typename ...T>
typename boost::enable_if<
    is_callable<Handler>,
    typename func::foo_t_info<Handler>::result_type
>::type
to_params_call(const Handler& handler, packet::packet_info<T...>& t);

template<typename Handler, typename ...T>
typename boost::enable_if<
    is_callable<Handler>,
    typename func::foo_t_info<Handler>::result_type
>::type
to_params_call(const Handler& handler, const packet::packet_info<T...>& t);
```

- **参数说明**：
  - `handler`：可调用对象（函数、函数对象、lambda 等）。
  - `t`：`packet::packet_info` 类型的数据包对象，内部包含一个元组（tuple）。
- **返回值**：handler 的返回类型。

## 实现细节

- 通过 `static_cast` 将 `packet_info` 转换为其内部的元组类型，然后调用 `tuple_to_params_caller.hpp` 中的 `to_params_call` 实现参数展开。
- 对于不支持可变参数模板的编译器，使用宏生成对应的模板参数和类型。

## 典型用法

```cpp
using info_t = yggr::packet::packet_info<int, double, std::string>;
info_t info(1, 2.5, "hello");
auto handler = [](int a, double b, const std::string& c) { /* ... */ };
yggr::caller::to_params_call(handler, info); // handler(1, 2.5, "hello")
```

## 依赖

- packet_info.hpp
- tuple_to_params_caller.hpp
- is_callable.hpp
- foo_t_info.hpp
- Boost.TypeTraits、Boost.Utility

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法或扩展说明，请参考源代码注释和 yggdrasil 项目文档。

