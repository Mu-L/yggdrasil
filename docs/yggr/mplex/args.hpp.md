# 文件：args.hpp 文档

路径：`yggr/mplex/args.hpp`

## 概要
`args.hpp` 提供了一个在编译时从模板参数列表中安全获取第 N 个类型的元编程工具 `get_arg`。它基于 Boost.MPL 实现，并在索引越界或参数为空的情况下允许指定备用类型（`Failed`）。该工具常用于模板元编程场景中，需要从类型列表中提取某一位置的参数或在缺失时使用默认类型。

主要功能：
- 在编译期从 `Params` 类型序列中获取第 `N` 个类型。
- 当 `Params` 为空或 `N` 超出范围时，返回用户指定的 `Failed` 类型（默认为 `null_type`）。


## 依赖
- 项目内部：`yggr/base/yggrdef.h`、`yggr/mplex/null_t.hpp`（其中定义了 `null_type` 等）。
- Boost.MPL：`boost/mpl/if.hpp`、`boost/mpl/size.hpp`、`boost/mpl/at.hpp`。

请确保这些头文件在编译环境中可用。


## 命名空间
- 所有实现位于 `yggr::mplex` 命名空间。


## API 说明

模板：get_arg

原型：

template<typename Params, size_type N, typename Failed = null_type>
struct get_arg
    : public detail::get_arg_detail<Params, N, Failed>
{
};

行为：
- `Params`：应为一个 Boost.MPL 类型序列（例如 `boost::mpl::vector<...>`）。
- `N`：待访问的索引（0-based），类型为 `size_type`（在项目中定义，通常为 `std::size_t` 的别名）。
- `Failed`：当无法取得第 N 个类型时返回的替代类型，默认是 `null_type`。

返回：继承自 `detail::get_arg_detail<Params, N, Failed>`，其 `typedef`（通常是 `type`）为结果类型。使用方式为 `typename get_arg<Params, N, Failed>::type`。


实现细节（内部类型）：

- `detail::wrap_at_c<Failed, T, N, is_validate>`：
  - 若 `is_validate`（即 `N < boost::mpl::size<T>::value`）为 `true`，则继承 `boost::mpl::at_c<T, N>`，从而暴露 `type` 为 `T` 中的第 N 个类型。
  - 若 `is_validate` 为 `false`（即越界），则特化为 `wrap_at_c<Failed, T, N, false>`，其中 `typedef Failed type;`。

- `detail::get_arg_detail<Params, N, Failed>`：
  - 首先判断 `Params` 是否为空（`!!(boost::mpl::size<Params>::value)`）。
  - 若不为空，使用 `wrap_at_c` 提取第 N 个类型或 `Failed`（取决于越界与否）。
  - 若 `Params` 是 `null_type`，则特化 `get_arg_detail<null_type, N, Failed>` 将 `type` 定义为 `Failed`。

因此，`get_arg` 将在以下几种场景中返回可预测的类型：
- `Params` 非空且 `N` 在范围内：返回 `Params` 中第 N 个类型。
- `Params` 非空但 `N` 越界：返回 `Failed`。
- `Params` 为 `null_type`（即没有参数）：返回 `Failed`。


## 使用示例

假设有一个类型序列：

```cpp
#include <boost/mpl/vector.hpp>
#include <yggr/mplex/args.hpp>

using params = boost::mpl::vector<int, double, std::string>;

// 获取第 0 个类型
using t0 = typename yggr::mplex::get_arg<params, 0>::type; // int

// 获取第 2 个类型
using t2 = typename yggr::mplex::get_arg<params, 2>::type; // std::string

// 获取越界时使用默认类型（例如 long）
using t3 = typename yggr::mplex::get_arg<params, 3, long>::type; // long (Failed)

// 当 Params 为 null_type
using t_none = typename yggr::mplex::get_arg<yggr::mplex::null_type, 0, short>::type; // short
```

注意：`size_type` 的定义在项目其他处（例如 `yggr/base/yggrdef.h`），在使用时请确保引入正确的 `size_type`。


## 合约（Contract）
- 输入：
  - `Params`：Boost.MPL 类型序列或 `null_type`。
  - `N`：索引（从 0 开始）。
  - `Failed`（可选）：当无法取得第 N 个类型时使用的替代类型。
- 输出：`typename get_arg<Params, N, Failed>::type` 表示的类型。
- 错误模式：该元函数在编译期进行分支，不会在运行时抛出异常；错误通常体现在编译期类型不匹配或未包含所需的 MPL 头时的编译错误。


## 边界情况与注意事项
- `Params` 不是 Boost.MPL 序列（或不提供 `boost::mpl::size`/`boost::mpl::at` 支持）会导致编译错误；请确保 `Params` 满足 Boost.MPL 序列概念。
- `N` 必须是合理的编译时常量（`size_type`），非编译时常量将导致无法实例化。
- `Failed` 类型可以是任意类型；当 `Failed` 被使用时请确保它满足调用上下文的要求。


## 测试建议
- 编写静态断言（`static_assert` 或 Boost.MPL 的静态检查）来验证常见场景：
  - 正常索引在范围内返回预期类型。
  - 越界时返回 `Failed`。
  - `Params` 为 `null_type` 时返回 `Failed`。

示例测试（C++11）：

```cpp
#include <type_traits>
#include <boost/mpl/vector.hpp>
#include <yggr/mplex/args.hpp>

using params = boost::mpl::vector<int, float>;
static_assert(std::is_same<yggr::mplex::get_arg<params, 0>::type, int>::value, "t0==int");
static_assert(std::is_same<yggr::mplex::get_arg<params, 1>::type, float>::value, "t1==float");
static_assert(std::is_same<yggr::mplex::get_arg<params, 2, long>::type, long>::value, "t2==long (Failed)");
```


