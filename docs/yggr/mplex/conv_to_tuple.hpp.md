# 文件：conv_to_tuple.hpp 文档

路径：`yggr/mplex/conv_to_tuple.hpp`

## 概要
`conv_to_tuple.hpp` 提供了将一个 "类型序列容器"（通常是 Boost.MPL 或自定义的元序列）转换为 tuple 风格类型的工具。它根据编译器是否支持 C++11 可变模板参数采用不同的实现分支：

- 当支持 variadic templates 时，通过包含 `yggr/mplex/detail/conv_to_tuple_vtpl.hpp` 提供基于变参模板的实现。
- 当不支持 variadic templates 时，通过包含 `yggr/mplex/detail/conv_to_tuple_vmacro.hpp` 使用预处理器宏展开的替代实现。

该头文件暴露了两个映射模板：

- `conv_to_yggr_tuple<Vector, Null_T = ::yggr::tuples::null_type>`：将 `Vector` 转换为 `::yggr::tuple` 类型（以 `Null_T` 作为空尾标记）。
- `conv_to_boost_tuple<Vector, Null_T = boost::tuples::null_type>`：将 `Vector` 转换为 `::boost::tuple` 类型（以 `Null_T` 作为空尾标记）。

这些模板均继承自更通用的 `conv_to_tuple< TupleTemplate, Vector, Null_T >`（在 `detail` 分支实现中定义），因此调用方可把 `conv_to_yggr_tuple<...>` 当作对应的 tuple 类型直接使用。


## 依赖
- `yggr/base/yggrdef.h`（项目基础宏和类型定义）
- 视编译器特性而异：
  - `yggr/mplex/detail/conv_to_tuple_vtpl.hpp`（variadic 实现，需要 C++11）
  - `yggr/mplex/detail/conv_to_tuple_vmacro.hpp`（预处理实现，兼容旧编译器）
- `::yggr::tuple` 与 `::boost::tuple` 的头（在使用时需要包含对应的 tuple 头），以及 `::yggr::tuples::null_type` / `boost::tuples::null_type`。


## 命名空间
- 模板位于 `yggr::mplex` 命名空间。


## API 说明

模板：conv_to_yggr_tuple

原型：

template<typename Vector, typename Null_T = ::yggr::tuples::null_type>
struct conv_to_yggr_tuple
    : public conv_to_tuple< ::yggr::tuple, Vector, Null_T>
{};

说明：将 `Vector`（通常表示一组类型，例如 `boost::mpl::vector<int,float>`）转换为 `::yggr::tuple<int,float>`，`Null_T` 用于尾部填充或表示空位，默认使用 `::yggr::tuples::null_type`。

模板：conv_to_boost_tuple

原型：

template<typename Vector, typename Null_T = boost::tuples::null_type>
struct conv_to_boost_tuple
    : public conv_to_tuple< ::boost::tuple, Vector, Null_T>
{};

说明：与 `conv_to_yggr_tuple` 等价，但目标类型为 `::boost::tuple`，默认空尾类型为 `boost::tuples::null_type`。


## 实现分支说明

- 如果你的编译器支持 C++11 变参模板，代码会包含 `detail/conv_to_tuple_vtpl.hpp`，这通常会更简洁、安全且对任意长度的类型序列都能正常工作。
- 否则，包含 `detail/conv_to_tuple_vmacro.hpp`，该实现通常使用 Boost.Preprocessor 或项目预处理宏在预定最大参数数目内生成展开的逻辑。

因此，`conv_to_tuple.hpp` 本身仅起到选择实现分支和暴露两个具体目标 tuple 类型的桥接作用。


## 使用示例

```cpp
#include <boost/tuple/tuple.hpp>
#include <boost/mpl/vector.hpp>
#include <yggr/mplex/conv_to_tuple.hpp>

using v = boost::mpl::vector<int, double, char>;
using bt = yggr::mplex::conv_to_boost_tuple<v>::type; // 或直接使用 yggr::mplex::conv_to_boost_tuple<v>

// bt 等价于 boost::tuple<int, double, char>

// 对 yggr 的 tuple
using yt = yggr::mplex::conv_to_yggr_tuple<v>::type;
// yt 等价于 yggr::tuple<int, double, char>
```

注意：是否能直接使用 `::type` 或直接使用 `conv_to_yggr_tuple<v>` 取决于 `conv_to_tuple` 在 `detail` 实现中如何暴露结果（通常会直接继承对应的 tuple 类型，因此 `conv_to_yggr_tuple<v>` 即为目标 tuple 类型）。


## 合约（Contract）
- 输入：`Vector`——一个类型序列（例如 Boost.MPL 序列或项目自定义的序列类型）。
- 输出：目标 tuple 类型 `::yggr::tuple<...>` 或 `::boost::tuple<...>`，其元素为 `Vector` 中的类型，可能以 `Null_T` 填充尾部或作为空标记。
- 错误模式：若 `Vector` 不被 `conv_to_tuple` 识别或超过了预处理实现的最大参数数量（在非 variadic 的实现中），则编译错误会在实例化时发生。


## 边界情况与注意事项
- 在非 variadic 的实现中，`conv_to_tuple` 能处理的最大序列长度由 `conv_to_tuple_vmacro.hpp` 中定义的展开上限决定（通常与项目的预处理宏 `YGGR_PP_TEMPLATE_PARAMS_LEN()` 有关）。
- `Null_T` 参数允许在目标 tuple 的末尾用特定的 null_type 填充，这与 boost/yggr 的 tuple 设计一致。
- `conv_to_tuple.hpp` 不直接包含 `yggr::tuple` 或 `boost::tuple` 的定义头；在使用生成的 tuple 类型之前，调用方应包含相应库的头文件以确保类型可用。


## 测试建议
- 在支持 variadic 的编译器上，测试多种长度的 `boost::mpl::vector`（包括 0,1,5,10 个元素）并断言生成的 tuple 类型成员数与之相匹配。
- 在不支持 variadic 的编译器上（或通过定义 `YGGR_NO_CXX11_VARIADIC_TEMPLATES`），测试边界长度（最大可支持长度）和超长序列导致的编译错误行为。
- 测试 `Null_T` 不同值的效果，确认空位或填充行为如预期。

