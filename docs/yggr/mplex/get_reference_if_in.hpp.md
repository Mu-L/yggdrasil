# 文件：get_reference_if_in.hpp 文档

路径：`yggr/mplex/get_reference_if_in.hpp`

## 概要
`get_reference_if_in` 是一个编译期元编程工具模板，用于根据一个给定的类型序列（`RefableCont`）判断某个源类型 `Src`（去掉引用与 cv）是否存在于该序列中：
- 若存在，则 `nctype` 和 `ctype` 分别表示 `src_type&`（非常量引用）和 `const src_type&`（常量引用）；
- 若不存在，则 `nctype` 与 `ctype` 都为用户提供的 `Default` 类型。

常用于需要根据类型列表决定是否使用引用类型（而不是值类型或其它替代类型）的模板元编程场景，例如通用包装器、序列元素访问或重载选择。


## 头文件依赖
- `yggr/base/yggrdef.h`（项目基础定义）
- Boost.TypeTraits：`boost::is_same`、`boost::remove_reference`、`boost::remove_cv`
- Boost.MPL：`boost::mpl::if_`、`boost::mpl::find`、`boost::mpl::end`


## 命名空间
位于 `yggr::mplex` 命名空间。


## 模板原型与成员

模板原型：

```cpp
template<typename Src, typename Default,
         typename RefableCont,
         typename Pred = boost::is_same< boost::mpl::_1,
                        typename boost::remove_cv<typename boost::remove_reference<Src>::type>::type >
>
struct get_reference_if_in;
```

主要公共 typedefs：
- `default_type`：别名为模板参数 `Default`。
- `cvr_src_type`：原始传入 `Src`（可能带引用和 cv）。
- `refable_cont_type`：模板参数 `RefableCont`，表示要查询的类型序列（通常是 Boost.MPL 序列，如 `boost::mpl::vector<...>`）。
- `pred_type`：用于在序列中匹配元素的谓词类型（默认为比较序列元素与 `Src` 去掉引用与 cv 后的类型是否相同）。
- `src_type`：由 `boost::remove_reference` 与 `boost::remove_cv` 去掉引用和 cv 的最终基础类型。
- `refable_end_iter_type`：`boost::mpl::end<refable_cont_type>::type`（序列末迭代器类型）。
- `refable_finded_iter_type`：`boost::mpl::find_if<refable_cont_type, pred_type>::type`（在序列中第一个满足 `pred_type` 的迭代器类型）。

输出类型：
- `nctype`：若 `refable_finded_iter_type` 等于 `refable_end_iter_type`（表示未找到），则 `nctype` = `Default`；否则 `nctype` = `src_type&`。
- `ctype`：同理，若找到则 `const src_type&`，否则 `Default`。


## 语义说明（用例）
- 用途：检查 `Src`（可能为 `T`, `T&`, `const T&` 等）的基础类型是否出现在 `RefableCont` 中，若出现则使用对应引用类型；否则退回到 `Default`。
- 典型场景：在实现通用容器/访问器模板时，对可被“引用”的元素返回引用类型，而对不可被引用或未列入支持列表的类型返回某个默认类型（例如 `null_type`、`void` 或包装类型）。

示例：

```cpp
#include <boost/mpl/vector.hpp>
#include <yggr/mplex/get_reference_if_in.hpp>

using list_t = boost::mpl::vector<int, double>;

// 情形 1: Src 为 int
using g1 = yggr::mplex::get_reference_if_in<int, void, list_t>;
// g1::nctype == int&  (因为 int 在 list_t 中)
// g1::ctype  == const int&

// 情形 2: Src 为 float
using g2 = yggr::mplex::get_reference_if_in<float, void, list_t>;
// g2::nctype == void  (因为 float 不在 list_t 中)
// g2::ctype  == void

// 情形 3: Src 为 const int&
using g3 = yggr::mplex::get_reference_if_in<const int&, void, list_t>;
// g3::nctype == int&  (remove_cv/remove_reference 后为 int)
// g3::ctype  == const int&
```

注意：该模板并不会在运行时产生引用对象，它只在类型层面选择引用类型；实际能否安全使用该引用取决于调用处传入对象的生命周期与语义。


## Pred 默认行为与可定制性
- 默认谓词 `Pred` 是 `boost::is_same<boost::mpl::_1, src_type>`，也就是直接比较序列元素类型是否与 `Src` 的基础类型相同。
- 你可以传入自定义 `Pred`（例如检查可转换性、某个特征或模板匹配），从而改变匹配规则。例如要匹配所有可从序列元素转换到 `src_type` 的情形，可实现一个相应的谓词。


## 实现要点
- 使用 `boost::mpl::find_if` 在 `RefableCont` 中查找满足 `Pred` 的元素。
- 通过比较找到的迭代器与 `boost::mpl::end<...>::type` 判断是否找到。
- 使用 `boost::mpl::if_`（或 `boost::mpl::if_` 的类型别名程序）来在编译期选择 `Default` 或引用类型。
- `src_type` 使用 `boost::remove_reference` 与 `boost::remove_cv` 保证引用与 cv 被清除后再做匹配与构造引用类型。


## 注意事项与陷阱
- 引用生命周期：`nctype`/`ctype` 只是类型级别的引用（`T&` / `const T&`）；在实际函数/类中返回或保存这些引用时，请确保被引用对象的生命周期足够长，否则会产生悬挂引用。
- `Default` 的选择：`Default` 应该是一个合法的类型占位（例如 `void` 不总是可用作类型别名位置），常见的可用 `Default` 包括项目中的 `null_type`、`boost::mpl::void_`、或用户自定义的占位类型。
- `RefableCont` 必须是一个支持 Boost.MPL 算法的序列（例如 `boost::mpl::vector<...>`）；若传入非 MPL 序列会导致编译错误。
- `Pred` 的语义需要小心：默认 `Pred` 比较的是 `boost::mpl::_1`（序列元素）与 `src_type`，确保序列元素类型与 `src_type` 在语义上可比较。


## 边界情况
- 当 `RefableCont` 为空序列或 `find_if` 未找到匹配，返回 `Default`。
- 对于带引用与 cv 的 `Src`，模板正确地移除引用与 cv 再进行匹配，保证 `Src` 的不同引用/常量修饰不会影响匹配基础类型。


## 测试建议
- 用 `boost::mpl::vector` 编写多组静态断言：
  - 测试 `Src` 在序列中（包括 `T`, `T&`, `const T&`）时 `nctype`/`ctype` 为所期望的引用类型。
  - 测试 `Src` 不在序列时 `nctype`/`ctype` 为 `Default`。
- 测试自定义 `Pred`，例如使用 `boost::is_base_of` 或 `boost::is_convertible` 风格的谓词，确保匹配逻辑可替换。

