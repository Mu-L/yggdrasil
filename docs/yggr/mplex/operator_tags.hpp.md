# 文件：operator_tags.hpp 文档

路径：`yggr/mplex/operator_tags.hpp`

## 概要
`operator_tags.hpp` 定义了一套用于描述“操作符（operator）属性”的元编程标签系统。通过宏 `YGGR_PP_MAKE_OPERATOR_TAG` 生成的 `op_tag_*` 结构体把每个操作符的几个属性（是否为后置/前置、是否可变、参数个数）编码为一个 `boost::mpl::vector`。

该文件还提供了一组 trait/辅助 metafunction：
- `is_operator_tag<T>`：检查类型是否为由宏生成的 operator tag（通过检测 `T::base_type` 是否为符合约定的 MPL vector）。
- `operator_is_after<Tag>`：获取 tag 表示的 “是否为后置（postfix）”（布尔类型，来自 base_type 的第 0 项）。
- `operator_is_mutable<Tag>`：获取 tag 的 “是否是可变操作（例如 += 可改变左值）”（来自 base_type 的第 1 项）。
- `operator_parms_size<Tag>`：获取操作符参数数量（来自 base_type 的第 2 项）。

宏和 traits 结合，使得上层代码可以用统一的方式查询和分发与操作符相关的行为。


## 主要宏：YGGR_PP_MAKE_OPERATOR_TAG

原型（在头文件中以宏形式使用）：

YGGR_PP_MAKE_OPERATOR_TAG(__name__, __is_after__, __is_mutable__, __param_size__)

作用：在 `yggr::mplex` 命名空间中生成：
- 一个名为 `op_tag___name__` 的结构体，继承自 `boost::mpl::vector< boost::mpl::bool_<__is_after__>, boost::mpl::bool_<__is_mutable__>, boost::mpl::int_<__param_size__> >`。
- 在同一命名空间生成一个函数 `make_op_tag___name__()`，返回对应的 `op_tag___name__` 值（用于方便构造临时 tag 实例）。

参数语义：
- `__name__`：标签的简短名称（宏会拼接成 `op_tag_##__name__`）。
- `__is_after__`：0/1，指示操作符是前置（0）还是后置（1）。例如 `a++` 为后置。
- `__is_mutable__`：0/1，指示操作是否会修改左值（例如 `+=`、`++a` 为可变/会修改）。
- `__param_size__`：整数，表示该操作符需要多少参数（例如一元运算为 1，二元为 2）。

示例：
- `YGGR_PP_MAKE_OPERATOR_TAG(plus, 0, 0, 2)` 表示二元加法 `+`，前置/非后置（在二元情形该字段语义可忽略）、不可变（不改变左值）、参数个数 2。
- `YGGR_PP_MAKE_OPERATOR_TAG(tail_increment, 1, 1, 1)` 表示后置递增 `a++`（后置、可变、1 个参数）。


## Traits 与辅助 metafunction

实现细节：
- 在 `detail` 命名空间中提供了对 MPL 类型的检测工具：
  - `is_operator_tag_bool_t<T>`：判断 `T` 是否 `boost::mpl::bool_<B>`。
  - `is_operator_tag_int_t<T>`：判断 `T` 是否 `boost::mpl::int_<N>`。
  - `is_operator_tag_vector_t<T>`：判断 `T` 是否为 `boost::mpl::vector<T1, T2, T3>` 且 `T1`、`T2`、`T3` 分别为上述布尔/整型包装类型。

- `is_operator_tag<T>`：对 `T::base_type` 进行上述向量格式检测，若匹配则返回 `true`（`boost::mpl::true_`），否则 `false`。

- `operator_is_after<Tag>`、`operator_is_mutable<Tag>`、`operator_parms_size<Tag>`：
  - 通过 `boost::mpl::at_c<typename Tag::base_type, index>::type` 访问对应元素（索引 0/1/2）。
  - 每个 metafunction 内部使用 `BOOST_MPL_ASSERT((is_operator_tag<Tag>))` 强制在编译期断言 `Tag` 是合法的 operator tag，从而在误用时提供更早和更清晰的编译期错误。

返回类型：这些 metafunction 的结果类型本身就是 MPL 的布尔或整型封装（例如 `boost::mpl::bool_<>`、`boost::mpl::int_<>`），因此可以直接用于 MPL 计算或通过 `::value` 获取数值用于普通静态断言。


## 文件尾部内置的常用 operator tags

该头文件示例性地通过宏定义了一系列常见操作符标签，例如：
- 一元运算：`op_tag_positive`, `op_tag_negate`, `op_tag_logic_not`, `op_tag_bitwise_not` 等。
- 自增/自减：`op_tag_head_increment`（++a）、`op_tag_tail_increment`（a++）、`op_tag_head_decrement`、`op_tag_tail_decrement`。
- 赋值与复合赋值：`op_tag_set`、`op_tag_plus_set`、`op_tag_minus_set` 等。
- 二元算术与位运算：`op_tag_plus`, `op_tag_minus`, `op_tag_multiplies`, `op_tag_divides`, `op_tag_modulus`, `op_tag_bitwise_and`/`_set`，左右移/右移等。
- 关系运算：`op_tag_equal_to`, `op_tag_not_equal_to`, `op_tag_less` 等。

这些宏调用给出了库内约定的 operator 标签集合，方便上层统一引用（例如在表达式树、操作符分发或策略选择中）。


## 使用示例

简单静态断言：

```cpp
#include <type_traits>
#include <boost/mpl/at.hpp>
#include <yggr/mplex/operator_tags.hpp>

// 检查某个 tag 是否有效
static_assert(yggr::mplex::is_operator_tag<yggr::mplex::op_tag_plus>::value, "op_tag_plus should be an operator tag");

// 获取参数数量
static_assert(yggr::mplex::operator_parms_size<yggr::mplex::op_tag_plus>::value == 2, "plus has 2 parms");

// 判断是否为后置
static_assert(yggr::mplex::operator_is_after<yggr::mplex::op_tag_tail_increment>::value == 1, "tail_increment is after/postfix");
```

在运行时代码中，可以使用 `make_op_tag_<name>()` 构造临时 tag 实例以传递给模板或函数（例如用于创建描述节点）。


## 设计意图与契约
- 目的：把操作符的元信息（是否后置、是否修改左值、参数个数）以类型级别信息表示，便于在编译期做策略选择、静态检查或作为表达式/AST 构造时的标签。
- 合约：由 `YGGR_PP_MAKE_OPERATOR_TAG` 生成的 `op_tag_xxx` 类型必须具有 `typedef base_type`，且 `base_type` 必须为 3 元素的 `boost::mpl::vector`：
  - index 0: `boost::mpl::bool_`（is_after），
  - index 1: `boost::mpl::bool_`（is_mutable），
  - index 2: `boost::mpl::int_`（param count）。
- `operator_*` metafunctions 在编译期断言上述合约，从而在误用时产生可读的静态断言失败。


## 测试建议
- 为每个内置的 `op_tag_*` 增加静态断言，验证 `is_operator_tag` 为 true，`operator_parms_size`、`operator_is_after`、`operator_is_mutable` 与预期匹配。
- 测试 `is_operator_tag` 对错误类型的识别（例如普通类型或缺少 `base_type` 的结构），确保静态断言或 SFINAE 分支能拦截误用。
- 在表达式构造的单元测试中使用 `make_op_tag_*()` 以验证运行时创建/传递 tag 的可用性（如果上层 API 需要运行时 tag 对象）。
