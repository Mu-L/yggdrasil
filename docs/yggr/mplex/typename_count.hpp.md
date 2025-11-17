# `yggr::mplex::typename_count`（文件：`yggr/mplex/typename_count.hpp`）

## 概要
- **目的**：在编译期计算一个模板实例中“类型模板参数”的数量（即对 `Src<Args...>` 中 `Args...` 的个数进行计数），并以 `boost::mpl::size_t<N>` 的形式暴露结果，以便在模板元编程中使用。
- **位置**：`yggr/mplex/typename_count.hpp`（与该文档同目录）
- **适用场景**：需要在编译期根据模板实例的参数个数做分支、静态断言或选择不同实现的场景，例如为不同参数数目的容器或元类型选择不同处理逻辑。

## 主要实现与说明
- 主要类型：
  - `template<typename T> struct typename_count` —— 导出接口，继承自 `detail::typename_count_cal<T>`。
  - `detail::typename_count_cal` 在默认情况下继承自 `boost::mpl::size_t<0>`（当匹配失败时表示 0）。

- C++11（变参模板）实现：
  - 对于 `Src<Args...>` 的特化：
    ```cpp
    template<template<typename ..._Args> class Src, typename ...Args>
    struct typename_count_cal< Src<Args...> >
      : public boost::mpl::size_t<sizeof...(Args)> {};
    ```
  - 当 `T` 匹配 `Src<Args...>` 时，`typename_count<T>::value` 将等于 `sizeof...(Args)`。

- C++03 回退实现（无 variadic templates）：
  - 通过预处理器循环（`BOOST_PP_LOCAL_ITERATE()`）生成多种参数个数的特化，每种特化将继承 `boost::mpl::size_t<__n__>`，其中 `__n__` 为参数个数。
  - 回退实现依赖项目内宏 `YGGR_PP_TEMPLATE_PARAMS_LEN()`（表示生成的最大模板参数数），以及 `YGGR_PP_TEMPLATE_PARAMS_TYPES` 等辅助宏。

- 依赖项：
  - `boost::mpl::size_t` 用于以类型级别封装常量值，适用于 Boost.MPL 的元编程风格。
  - 若在无 variadic 支持下使用回退，需确保项目的预处理宏设置能覆盖所需的最大模板参数数目。

## 使用示例
```cpp
#include <type_traits>
#include <yggr/mplex/typename_count.hpp>

// 假设 T 为 std::vector<int, Alloc>
using T = std::vector<int, std::allocator<int>>;

// 获取模板参数数量（C++11 实现下）：
constexpr std::size_t n = yggr::mplex::typename_count<T>::value; // 2
static_assert(n == 2, "vector has two template parameters");

// 在 MPL 上下文中可以直接使用：
using mpl_n = yggr::mplex::typename_count<T>; // mpl::size_t<2>
```

说明：当 `T` 不是模板实例（例如普通类型或非模板模板参数形式），`typename_count<T>::value` 默认为 0（由默认继承的 `boost::mpl::size_t<0>` 提供）。

## 注意事项与兼容性
- C++11 的变参实现更简洁且不依赖预处理宏；当启用 `YGGR_NO_CXX11_VARIADIC_TEMPLATES` 时，代码会回退到预处理器生成的多重特化。
- 回退实现只能生成到 `YGGR_PP_TEMPLATE_PARAMS_LEN()` 定义的上限；如果你需要支持超过该上限的模板参数数量，需要调整该宏并重新生成/编译。
- `typename_count` 仅统计“类型型模板参数”的数量（实现匹配形式为 `template<typename ...>`）；对于含非类型参数或模板模板参数的模板（如 `template<class T, int N>`）可能不完全适配，除非回退宏被扩展为支持这些形式。
