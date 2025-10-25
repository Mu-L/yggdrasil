# 文件：integer_log2.hpp 文档

路径：`yggr/mplex/integer_log2.hpp`

## 概要
`integer_log2.hpp` 提供了一个编译期元编程工具 `integer_log2<N>`，用于在编译期计算一个无符号整数常量 N 的以 2 为底的对数（严格意义上：当且仅当 N 为 2 的幂时，返回整数 log2(N)；否则返回失败类型）。

该工具采用 Boost.MPL 风格的类型计算，输出是一个 `boost::mpl::size_t<value>`（当成功）或失败类型 `integer_log2_failed`（当失败）。库中对 "可计算性" 进行了检查，只有满足条件（N 为 2 的幂）时才产生有效结果。

文件对外暴露的符号包括：
- `detail::integer_log2_failed`（作为失败占位类型，别名为 `yggr::mplex::integer_log2_failed` 可通过 using 引入）
- 模板 `integer_log2<N>`：当 N 为 2 的幂时继承自 `boost::mpl::size_t<log2(N)>`，否则继承自失败类型。


## 依赖
- `yggr/base/yggrdef.h`（项目基础定义）
- `yggr/mplex/static_assert.hpp`（可能用于其它元编程断言）
- `yggr/mplex/null_t.hpp`（定义 `null_type`，作为失败占位符）
- Boost.MPL：`boost/mpl/if.hpp`、`boost/mpl/bool.hpp`、`boost/mpl/size_t.hpp`


## 命名空间
实现位于 `yggr::mplex`，实现细节放在 `yggr::mplex::detail` 命名空间内。


## API 说明

模板：integer_log2

原型：

template<std::size_t N>
struct integer_log2
    : public detail::integer_log2_cal< typename detail::integer_log2_chk<N>::type, N >::type
{
};

语义与约束：
- 输入：编译期常量无符号整数 N（模板非类型参数）。
- 输出：如果 N 为 2 的幂（例如 1,2,4,8,...），则 `integer_log2<N>::type` 为 `boost::mpl::size_t<V>`，其中 `V == log2(N)`（log2(1)=0, log2(2)=1, ...），因而可通过 `integer_log2<N>::value` 或 `integer_log2<N>::type::value` 取得该整数值。
- 失败情形：如果 N 不是 2 的幂，或者 N == 0，则 `integer_log2<N>` 继承自 `integer_log2_failed`（`null_type`），表示不可计算。

注意：库将失败类型命名为 `integer_log2_failed`。


## 实现细节（核心模板说明）

实现分为三个主要组件（在 `detail` 命名空间中）：

1. `integer_log2_chk<N>`
   - 功能：检测 N 是否为 2 的幂。
   - 递归行为：
     - 如果 `N == 1`：特化返回 `boost::mpl::true_`。
     - 如果 `N == 0`：特化返回 `boost::mpl::false_`（0 被视为不可计算）。
     - 否则：当 `N % 2 == 0`（偶数）时，递归判断 `N >> 1`；否则返回 `boost::mpl::false_`。
   - 结果：`integer_log2_chk<N>::type` 为 `boost::mpl::true_` 当且仅当 N 为 2 的幂。

2. `integer_log2_cal<Chk, N>`
   - 功能：在 `Chk` 为 `boost::mpl::true_` 时计算 log2(N)，否则返回失败类型。
   - 特化：
     - `integer_log2_cal<boost::mpl::false_, N>` 继承自 `integer_log2_failed` 表示计算失败。
     - `integer_log2_cal<boost::mpl::true_, N>` 递归地继承自 `boost::mpl::size_t<(1 + integer_log2_cal<boost::mpl::true_, (N >> 1)>::type::value)>`。
     - 基例：`integer_log2_cal<boost::mpl::true_, 1>` 继承自 `boost::mpl::size_t<0>`（log2(1) = 0）。

3. 顶层模板 `integer_log2<N>` 将 `integer_log2_chk<N>` 的结果作为 `Chk` 传递给 `integer_log2_cal`，并继承后者的 `::type`，从而最终为用户提供 `::value` 或失败类型。


## 使用示例

可通过 `::value` 在编译期获取结果（在成功情形下）：

```cpp
#include <type_traits>
#include <yggr/mplex/integer_log2.hpp>

static_assert(yggr::mplex::integer_log2<1>::value == 0, "log2(1)==0");
static_assert(yggr::mplex::integer_log2<2>::value == 1, "log2(2)==1");
static_assert(yggr::mplex::integer_log2<4>::value == 2, "log2(4)==2");
static_assert(yggr::mplex::integer_log2<8>::value == 3, "log2(8)==3");

// 非 2 的幂会导致继承失败类型（integer_log2_failed），不能直接访问 ::value
// 例如：
// yggr::mplex::integer_log2<3> 继承自 integer_log2_failed
```

如果需要在元编程中根据是否成功选择分支，建议使用 Boost.MPL 的类型判断或 `std::is_same`（视失败类型而定）：

```cpp
#include <type_traits>
#include <boost/mpl/size_t.hpp>
#include <yggr/mplex/integer_log2.hpp>

// 判断是否计算成功（失败类型为 null_type）
using result3 = yggr::mplex::integer_log2<3>;
using failed_t = yggr::mplex::integer_log2_failed;
static_assert(std::is_same<result3, failed_t>::value, "3 is not power of two -> failed");
```


## 合约（Contract）
- 输入：编译期常量 `N`（std::size_t）。
- 输出：
  - 当 N 为 2 的幂时，`integer_log2<N>` 表示 `boost::mpl::size_t<log2(N)>`，可通过 `::value` 取得整数值。
  - 当 N 不是 2 的幂（或 N == 0）时，`integer_log2<N>` 为 `integer_log2_failed`（即 `null_type`），表示不可计算。
- 错误模式：对非 2 的幂调用 `::value` 将导致编译错误，因为失败类型不含 `::value`。


## 边界情况与注意事项
- N == 0：明确被处理为 `false`（`integer_log2_chk<0>` 特化返回 false），因此 `integer_log2<0>` 为失败类型。
- 非 2 的幂：会得到失败类型；这是设计上的选择以明确只对 2 的幂有定义。
- 名称拼写：源文件使用了 `integer_log2_failed`（注意拼写），文档中保留该名称以避免混淆，但在未来修改代码时可考虑改为 `integer_log2_failed` 以修正拼写。


## 测试建议
- 为一系列 N 值编写静态断言：
  - 成功样例：1,2,4,8,16,32 等，确认 `::value` 与预期一致。
  - 失败样例：0,3,5,6,7,9 等，确认类型为 `integer_log2_failed`。
- 在使用 `integer_log2` 的上层元编程工具中加入类型检查分支（例如使用 `boost::mpl::if_` 或 `std::conditional`）以避免在失败情形下直接访问 `::value`。



