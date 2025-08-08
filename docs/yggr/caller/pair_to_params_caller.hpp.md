---
# pair_to_params_caller.hpp

该头文件属于 yggdrasil 项目，实现了将 `std::pair` 的两个成员作为独立参数传递给可调用对象（如函数、函数对象、lambda 等）的工具。用于简化 pair 数据结构与函数参数之间的适配。

## 主要功能

- **to_params_call**：将 `std::pair` 的 `first` 和 `second` 成员作为参数传递给 handler。
- 自动推断 handler 的返回类型。
- 支持非常量和常量的 `std::pair`。

## 主要接口

```cpp
template<typename Handler, typename T1, typename T2>
typename boost::enable_if<
    is_callable<Handler>,
    typename func::foo_t_info<Handler>::result_type
>::type
to_params_call(const Handler& handler, std::pair<T1, T2>& params);

template<typename Handler, typename T1, typename T2>
typename boost::enable_if<
    is_callable<Handler>,
    typename func::foo_t_info<Handler>::result_type
>::type
to_params_call(const Handler& handler, const std::pair<T1, T2>& params);
```

- **参数说明**：
  - `handler`：可调用对象（函数、函数对象、lambda 等）。
  - `params`：`std::pair<T1, T2>` 类型的参数对。
- **返回值**：handler 的返回类型。

## 实现细节

- 使用 `boost::enable_if` 和 `is_callable` 限定 handler 必须是可调用对象。
- 直接将 `params.first` 和 `params.second` 作为参数传递给 handler。

## 典型用法

```cpp
std::pair<int, std::string> p(42, "hello");
auto handler = [](int a, const std::string& b) { /* ... */ };
yggr::caller::to_params_call(handler, p); // handler(42, "hello")
```

## 依赖

- is_callable.hpp
- foo_t_info.hpp
- `<utility>`（std::pair）
- Boost.Utility

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法或扩展说明，请参考源代码注释和 yggdrasil 项目文档。

