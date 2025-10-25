# 文件：get_reference_if_same.hpp 文档

路径：`yggr/mplex/get_reference_if_same.hpp`

## 概要
`get_reference_if_same` 是一个编译期元编程工具模板，用于比较两个类型：给定源类型 `Src`（可能带引用/const/volatile 修饰）和候选类型 `Cmp`，
当去除 `Src` 的引用与 cv 修饰后若与 `Cmp` 相同，则选择引用形式（`src_type&` 或 `const src_type&`）；否则返回 `Cmp` 本身作为替代类型。

该工具在需要根据类型相等性在编译期选用“引用类型”或保留比较类型作为占位的场景中非常实用，例如泛型包装器、访问器或函数重载选择。


## 头文件依赖
- `yggr/base/yggrdef.h`（项目基础宏/类型定义）
- Boost.TypeTraits：`boost::is_same`、`boost::remove_reference`、`boost::remove_cv`
- Boost.MPL：`boost::mpl::if_`


## 命名空间
位于 `yggr::mplex` 命名空间。


## 模板原型与成员

模板定义（简化）：

```cpp
template<typename Src, typename Cmp>
struct get_reference_if_same;
```

内部类型别名：
- `cvr_src_type`：原始传入的 `Src`（可能为带引用或 cv）。
- `cmp_type`：别名为 `Cmp`。
- `src_type`：通过 `boost::remove_reference` 和 `boost::remove_cv` 得到的 `Src` 的基础类型。

输出类型（主要 API）：
- `nctype`（non-const 类型分支）:
  - 若 `src_type` 与 `cmp_type` 相同（`boost::is_same<src_type, cmp_type>::type` 为 true），则 `nctype = src_type&`。
  - 否则 `nctype = cmp_type`。

- `ctype`（const 类型分支）:
  - 若相同则 `ctype = const src_type&`。
  - 否则 `ctype = cmp_type`。

换言之，模板在编译期根据类型是否“相同”决定是返回引用类型还是保留比较类型作为占位类型。


## 语义与用例
- 目的：当希望为与某一指定类型相同的源类型返回引用（以便修改或避免拷贝），而对不同类型返回一个通用占位类型时使用。
- 典型场景：实现一个泛型访问器或容器，若内部元素类型与请求类型相同则返回引用，否则返回默认的占位类型（例如 `null_type`、包装类型或 `Cmp`）。

示例：

```cpp
#include <type_traits>
#include <yggr/mplex/get_reference_if_same.hpp>

// 假设我们需要根据 Src 是否与 int 相同来选择类型
using G1 = yggr::mplex::get_reference_if_same<int, float>;
// 因为 int 与 float 不同，G1::nctype == float, G1::ctype == float

using G2 = yggr::mplex::get_reference_if_same<int, int>;
// 因为 src_type (int) 与 cmp_type (int) 相同，G2::nctype == int&, G2::ctype == const int&

using G3 = yggr::mplex::get_reference_if_same<const long&, long>;
// 去除引用/const 后为 long，与 cmp_type(long) 相同，G3::nctype == long&, G3::ctype == const long&
```

注意：这些别名仅代表类型选择；实际返回引用时必须注意对象的生命周期。


## 实现要点
- `src_type` 使用 `boost::remove_reference` 和 `boost::remove_cv` 得到基础类型，保证 `Src` 的引用与 cv 修饰不会影响相等性判断。
- 判断使用 `boost::is_same<src_type, cmp_type>::type`，并通过 `boost::mpl::if_` 在编译期选择两种分支。
- `nctype` 与 `ctype` 分别对应非常量引用和常量引用的分支。


## 注意事项与陷阱
- 引用安全性：当 `nctype` 表示 `src_type&` 且在运行时代码中你返回或保存该引用时，必须保证被引用对象在使用期间仍然有效；否则会出现悬挂引用。
- `Cmp` 的语义：若 `Cmp` 是占位类型（例如 `null_type`）或非引用类型，则在“不同”分支中直接使用 `Cmp`，需要确保该类型在使用环境中是合理的（例如可以作为返回类型或模板参数）。
- 对于模板参数 `Src` 为复杂模板参数（例如带 cv/ref 的模板实例），`remove_reference` / `remove_cv` 的结果与期望的一致性需确认（在 constexpr/alias 模板复杂场景下建议写单元测试）。


## 边界情况
- `Src` 与 `Cmp` 在类型别名上可能看似相同但不完全相同（例如 `typedef int32_t myint;`），`boost::is_same` 判断会基于实际类型别名解析，而非语义上相容性；如需更宽松匹配，应改用 `std::is_convertible` 或自定义谓词。
- 当 `Cmp` 自身是引用类型或带修饰时，行为是直接返回 `cmp_type`（不自动移除其修饰）；如果希望对 `Cmp` 也做相同的 remove_cv/remove_ref 处理，应在使用处提前处理。


## 测试建议
- 编写静态断言来覆盖典型情形：
  - 相同基本类型（`int` vs `int`） -> `nctype` 为 `int&`。
  - 不同类型（`int` vs `double`） -> 返回 `cmp_type`。
  - 含 cv/ref 的 `Src`（`const T&`）与 `Cmp` 匹配的情形。
- 若需要更复杂的匹配语义（例如可转换性或基类关系），替换 `boost::is_same` 为合适的 trait 并验证行为。

