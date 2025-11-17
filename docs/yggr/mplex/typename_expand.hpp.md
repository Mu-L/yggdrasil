# `yggr::mplex::typename_expand`（文件：`yggr/mplex/typename_expand.hpp`）

## 概要
- **目的**：将一个模板实例的类型模板参数展开为一个可索引的元序列（基于 `boost::mpl::vector`），并提供按索引安全访问（含越界安全）的接口。该工具便于在模板元编程中检索某个模板实例的第 N 个类型参数或获取参数个数。
- **位置**：`yggr/mplex/typename_expand.hpp`（与该文档同目录）
- **依赖项**：`yggr/ppex/typedef.hpp`、`yggr/mplex/null_t.hpp`、Boost.MPL（`vector`, `size`, `at`, `at_c`, `size_t`, `less`）以及项目的 `YGGR_PP_*` 预处理宏（用于无变参模板下的回退实现）。

## 主要实现要点
- `detail::_typename_expand<T>`
  - 默认情形：继承自空的 `boost::mpl::vector<>`，并定义 `size_type = boost::mpl::size_t<0>`。
  - C++11（有变参模板）：当 `T` 匹配 `Other_Cont<Args...>` 时，特化继承自 `boost::mpl::vector<Args...>`，并将 `size_type` 设为 `sizeof...(Args)`。
  - C++03 回退：使用预处理器生成多种参数数目的特化，每种特化对应不同的 `boost::mpl::vector<...>` 与 `size_type`。

- `detail::_safe_arg` / `_safe_arg_c`
  - 目的是实现“越界安全”的按索引访问：若索引 N 小于序列大小则返回对应 `boost::mpl::at` 或 `boost::mpl::at_c` 的结果，否则返回 `mplex::null_type`。
  - `_safe_arg` 使用类型形式的索引 `N`（`boost::mpl::less<N, size_type>::value` 做判断），`_safe_arg_c` 使用编译期整型常量 `std::size_t N` 做判断。

- `typename_expand<T>`（对外接口）
  - 继承自 `detail::_typename_expand<T>`，并提供以下成员模板以方便访问：
    - `template<typename N> struct arg : public boost::mpl::at<base_type, N> { };` —— 按类型索引获取参数类型（返回一个 MPL 包装类型，访问真实类型请使用 `::type`）。
    - `template<std::size_t N> struct arg_c : public boost::mpl::at_c<base_type, N> { };` —— 按整型常量索引获取类型。
    - `template<typename N> struct safe_arg` 与 `template<std::size_t N> struct safe_arg_c` —— 越界安全版本，越界时返回 `mplex::null_type`。
  - 额外类型：`typename_expand<T>::size_type` 表示模板参数数量（MPL 的 `size_t`）。

- 便捷别名/工具：
  - `typename_expand_size<T>` —— 直接继承 `typename_expand<T>::size_type`，便于获取参数个数。
  - `typename_expand_t_get<T, N>` / `typename_expand_get<T, N>` —— 分别按类型索引或整型索引取出 `::type`，方便在代码中直接别名化使用。
  - `typename_expand_t_get_safe` / `typename_expand_get_safe` —— 安全取值版本，越界返回 `null_type`。

## 使用示例
```cpp
#include <type_traits>
#include <boost/mpl/assert.hpp>
#include <yggr/mplex/typename_expand.hpp>

// 示例类型：
using P = std::pair<int, double>;

// 获取参数个数（MPL 风格）：
using size_mpl = yggr::mplex::typename_expand<P>::size_type; // mpl::size_t<2>
static_assert(size_mpl::value == 2, "pair has two template params");

// 通过整型常量索引获取第 0 个参数类型：
using first_t = yggr::mplex::typename_expand_get<P, 0>::type; // int
static_assert(std::is_same<first_t, int>::value, "first is int");

// 通过类型索引获取第 1 个参数类型（需要传入 mpl::size_t<1>）：
using second_t = yggr::mplex::typename_expand_t_get<P, boost::mpl::size_t<1> >::type; // double
static_assert(std::is_same<second_t, double>::value, "second is double");

// 越界安全访问（索引 5 超出范围，返回 null_type）：
using safe_out = yggr::mplex::typename_expand_get_safe<P, 5>::type; // mplex::null_type
static_assert(std::is_same<safe_out, yggr::mplex::null_type>::value, "out of range -> null_type");
```

说明：示例使用 `std::pair<int,double>`，因为它是带两个类型模板参数的典型容器/聚合类型；其他模板实例（例如 `std::vector<T, Alloc>`）同样适用。

## 兼容性与注意事项
- C++11 优先使用变参模板实现，代码更简洁；若宏 `YGGR_NO_CXX11_VARIADIC_TEMPLATES` 被定义，则回退到预处理器生成的多重特化实现。回退实现依赖 `YGGR_PP_TEMPLATE_PARAMS_LEN()` 提供的最大参数数上限。
- `typename_expand` 适用于以“类型型模板参数”为主的模板实例（`template<typename ...>`）。若模板含有非类型参数或更复杂的模板模板参数，可能需要扩展匹配模式或增补回退宏。
- 返回的索引访问类型通常是一个 MPL 包装类型，要取出真实类型请使用 `::type`。
- `null_type` 用于表示“无类型/越界”情形；在后续元编程中应对该类型做特殊处理或判定。
