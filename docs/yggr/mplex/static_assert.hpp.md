# static_assert.hpp

文件路径: `yggr/mplex/static_assert.hpp`

## 概述

本头文件为本项目提供了一个跨编译器/跨标准的静态断言包装宏（`YGGR_MPLEX_STATIC_ASSERT`）以及一个用于触发不可达/失败断言的宏 `YGGR_MPLEX_FXIED_ASSERT_FALSE()`。

目的是在既支持现代 C++ 的编译器（支持 `static_assert`）和不支持或需要使用 Boost.MPL 的编译器间，统一静态断言的写法并兼容模板/constexpr 的限制。

## 依赖

- `yggr/base/yggrdef.h`
- `yggr/ppex/concat.hpp` （用于在宏里做标识符拼接）
- Boost.MPL：`boost/mpl/assert.hpp`、`boost/mpl/bool.hpp`
- 标准断言：`<cassert>`

## 提供的宏

- `YGGR_MPLEX_STATIC_ASSERT( __x__ )`
  - 行为（根据编译器特性）：
    - 若宏检测到 `__cpp_static_assert` 已定义且版本符合条件（实现的检查：`#if defined(__cpp_static_assert) \n #\tif !(__cpp_static_assert) < 200410`），它将展开为 `static_assert( yggr::traits< YGGR_PP_CONCAT __x__ >::type::value )`。这里使用了 `YGGR_PP_CONCAT` 宏来把参数拼接成一个类型名并传入 `yggr::traits<...>::type::value`。
    - 否则（老环境或未检测到新的 `static_assert` 支持），它将被定义为 `BOOST_MPL_ASSERT`（来自 Boost.MPL）。
  - 语义意图：允许以统一方式在元编程上下文中断言某个类型 trait 的 `::type::value` 为真。使用者通过传入一个形式上可以被 `YGGR_PP_CONCAT` 拼接成模板参数的 token 来构造断言表达式。

- `YGGR_MPLEX_FXIED_ASSERT_FALSE()`
  - 在 `_MSC_VER`（MSVC）下：展开为 `BOOST_MPL_ASSERT((boost::mpl::false_))`，以触发 Boost.MPL 类型级断言。
  - 在其他编译器下：展开为 `assert((false))`（运行时断言）。注：注释指出 "gcc still check BOOST_MPL_ASSERT((boost::mpl::false_))"，但代码对非 MSVC 选择了运行时 `assert(false)`，可能是为了避免某些编译器对 `BOOST_MPL_ASSERT` 的行为差异。
  - 注意：宏名拼写为 `YGGR_MPLEX_FXIED_ASSERT_FALSE`，明显是 `FIXED` 的拼写错误（`FXIED`）。该名字在仓库中被使用时要留意拼写一致性。

## 设计与实现要点

1. 为什么要有这个包装？
   - C++11 之后引入了关键字 `static_assert`，但在模板元编程或旧编译器环境下仍常使用 `BOOST_MPL_ASSERT`。本文件通过检测 `__cpp_static_assert` 来选择合适实现，旨在：
     - 在支持 `static_assert` 的实现上使用编译器内置静态断言（通常会生成更直观的编译器错误信息）。
     - 在不支持或不稳定的环境中回退到 `BOOST_MPL_ASSERT`。

2. 关于 `__cpp_static_assert` 的检测
   - 这里的条件写法略显奇特：`#if !(__cpp_static_assert) < 200410`。意图是判断 `__cpp_static_assert` 的值是否达到某个日期宏，但该比较写法在预处理器表达式中可能导致可读性问题。大部分编译器会把 `__cpp_static_assert` 视为整数宏（若定义），但边界条件需要在不同编译器上验证其行为是否如预期。

3. `YGGR_PP_CONCAT __x__` 的用法
   - 宏内部使用了 `YGGR_PP_CONCAT` 将传入参数拼接成 token，然后作为 `yggr::traits<...>` 的模板参数。调用者必须确保传入的 `__x__` 片段在拼接后构成合法的类型名或表达式。例如：

   ```cpp
   // 伪代码（具体取决于 YGGR_PP_CONCAT 的实现）
   YGGR_MPLEX_STATIC_ASSERT((some_trait< T >::value));
   // 可能变成 static_assert( yggr::traits<some_trait< T >::value>::type::value )
   ```

   - 注意这里的写法会让人迷惑：`YGGR_PP_CONCAT __x__` 与典型的 `YGGR_PP_CONCAT(__x__, other)` 用法不同，用户在使用该宏时应参看 `yggr/ppex/concat.hpp` 的定义，确保传参方式正确。

4. MSVC 与其他编译器的差异处理
   - 对 `YGGR_MPLEX_FXIED_ASSERT_FALSE()`，作者选择在 MSVC 下使用 `BOOST_MPL_ASSERT`，而在其他编译器使用运行时 `assert(false)`。这可能是出于对某些编译器在模板上下文报错不友好的考虑。但也意味着该宏在非 MSVC 下不会在编译期失败，而是产生运行时断言（并非静态断言）。

## 使用示例

- 使用 `YGGR_MPLEX_STATIC_ASSERT`（示例仅作说明，具体参数与 `YGGR_PP_CONCAT` 的要求有关）：

```cpp
// 伪示例：说明意图
YGGR_MPLEX_STATIC_ASSERT(( is_integral_trait< int > ));
// 若使用 static_assert 分支，期望检查 yggr::traits< is_integral_trait<int> >::type::value
// 若使用 Boost.MPL 分支，则相应地展开 BOOST_MPL_ASSERT(...)
```

- 触发失败断言：

```cpp
YGGR_MPLEX_FXIED_ASSERT_FALSE(); // 在 MSVC 上将是 BOOST_MPL_ASSERT((boost::mpl::false_))
```

## 建议与注意事项

1. 明确宏参数契约
   - 当前实现依赖 `YGGR_PP_CONCAT` 对传入 token 的拼接方式。建议在项目文档中补充 `YGGR_MPLEX_STATIC_ASSERT` 的参数格式示例，或者改用更直观的宏接口（例如传入一个完整的类型名或 trait 表达式）。

2. 修正或记录拼写
   - `YGGR_MPLEX_FXIED_ASSERT_FALSE` 的 `FXIED` 似为拼写错误，若在项目中广泛使用该名字保持一致也可以不用修正，但最好在文档中注明并在代码审查时考虑是否更正（更正会导致调用处需同步替换）。

3. 统一断言策略
   - 运行时 `assert(false)` 与编译期 `BOOST_MPL_ASSERT`/`static_assert` 并不是等价行为。若目标是保证在所有平台上都产生编译期错误，应将非 MSVC 分支也改为 `BOOST_MPL_ASSERT((boost::mpl::false_))`（当然要考虑特定编译器对 Boost.MPL 的支持和错误信息可读性）。

4. 测试覆盖
   - 推荐添加单元测试，验证以下场景：
     - 在开启 C++11+ 编译器并定义 `__cpp_static_assert` 的环境下，`YGGR_MPLEX_STATIC_ASSERT` 能正确触发编译期断言并得到可读的错误信息。
     - 在不定义/低版本 `__cpp_static_assert` 的环境下，宏退化为 `BOOST_MPL_ASSERT` 并如预期工作。
     - `YGGR_MPLEX_FXIED_ASSERT_FALSE()` 在不同编译器下的行为（MSVC 编译失败，其他环境在运行时触发断言）。

## 示例静态断言（建议放入测试文件）

```cpp
#include <yggr/mplex/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>

// 伪示例，具体取决于 YGGR_PP_CONCAT 的用法
// YGGR_MPLEX_STATIC_ASSERT(( boost::is_integral< int > ));

// 触发固定失败（视平台不同）：
// YGGR_MPLEX_FXIED_ASSERT_FALSE();
```

## 结论

`static_assert.hpp` 为项目封装了静态断言接口以兼容不同的编译器/标准，并在必要时回退到 Boost.MPL 的断言机制。文档中列出了使用时应注意的宏参数格式、拼写陷阱与平台差异，并建议补充测试以确保在目标编译器矩阵上的行为一致。

---

文档生成器: 自动生成（根据 `static_assert.hpp` 源码分析）
