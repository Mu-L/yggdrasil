---
# array_to_params_caller.hpp

该头文件属于 yggdrasil 项目，实现了将数组元素作为参数传递给可调用对象（如函数、函数对象、lambda 等）的工具。支持 `std::array` 和 `boost::array`，并兼容 C++11 及更早版本。

## 主要功能

- **to_params_call**：将数组的每个元素作为独立参数传递给 handler。
- 支持 `std::array`（C++11 及以上）和 `boost::array`。
- 自动推断 handler 的返回类型。
- 兼容可变参数模板和预处理器宏两种实现方式。

## 主要接口

```cpp
template<typename Handler, typename Val, std::size_t N>
typename boost::enable_if<
    is_callable<Handler>,
    typename func::foo_t_info<Handler>::result_type
>::type
to_params_call(const Handler& handler, std::array<Val, N>& arr);

template<typename Handler, typename Val, std::size_t N>
typename boost::enable_if<
    is_callable<Handler>,
    typename func::foo_t_info<Handler>::result_type
>::type
to_params_call(const Handler& handler, boost::array<Val, N>& arr);
```

- **参数说明**：
  - `handler`：可调用对象（函数、函数对象、lambda 等）。
  - `arr`：`std::array` 或 `boost::array`，元素类型为 `Val`，长度为 `N`。
- **返回值**：handler 的返回类型。

## 实现细节

- 对于支持 C++11 可变参数模板的编译器，使用 `index_sequence` 展开数组元素。
- 对于不支持可变参数模板的编译器，使用预处理器宏生成展开代码。
- 内部通过 `array_to_params_call_helper<N>` 实现参数展开。

## 典型用法

```cpp
std::array<int, 3> arr = {1, 2, 3};
auto sum = [](int a, int b, int c) { return a + b + c; };
int result = yggr::caller::to_params_call(sum, arr); // result == 6
```

## 依赖

- yggrdef.h
- array.hpp
- integer_sequence.hpp（C++11）
- is_callable.hpp
- foo_t_info.hpp
- `boost/utility/enable_if.hpp`

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法或扩展说明，请参考源代码注释和 yggdrasil 项目文档。

