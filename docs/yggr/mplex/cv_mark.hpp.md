# 文件：cv_mark.hpp 文档

路径：`yggr/mplex/cv_mark.hpp`

## 概要
`cv_mark.hpp` 定义了一个用于表示类型 cv（const/volatile）修饰信息的元编程标记结构 `cv_mark_t`。该结构通过 Boost.MPL 的整型常量类型（`boost::mpl::integral_c<u32, ...>`）为不同的 cv 情形提供命名的编译期值，并通过宏 `YGGR_STATIC_CONSTANT` 暴露对应的数值常量。

这个文件常用于模板元编程场景中，需要用整数或类型级常量表示某个类型的 cv 修饰态，从而在 `switch`/选择/映射逻辑（例如 MPL map、索引表、位掩码判断等）中进行分支。


## 依赖
- `yggr/base/static_constant.hpp`（定义 `YGGR_STATIC_CONSTANT` 宏，用于声明静态常量）
- `boost/mpl/integral_c.hpp`（用于生成 MPL 风格的整型常量类型）


## 名称空间
实现位于 `yggr::mplex` 命名空间。


## API 说明（`cv_mark_t`）

`cv_mark_t` 是一个简单的聚合类型（struct），其内包含若干类型别名（MPL 整型常量类型）和静态常量：

- typedefs（类型级常量，均为 `boost::mpl::integral_c<u32, V>`）：
  - `cv_non_t`：无 cv 修饰，对应值 0。
  - `cv_const_t`：仅 const 修饰，对应值 1。
  - `cv_volatile_t`：仅 volatile 修饰，对应值 1 << 1（即 2）。
  - `cv_const_volatile_t`：const 与 volatile 同时存在，对应值 (cv_const_t::value | cv_volatile_t::value)（即 3）。
  - `cv_end_t`：结束标记，对应值 (cv_const_volatile_t::value + 1)（即 4），可用于界限或数组长度。

- 静态整数常量（通过 `YGGR_STATIC_CONSTANT(u32, NAME = ...)` 暴露）：
  - `E_cv_non`、`E_cv_const`、`E_cv_volatile`、`E_cv_const_volatile`、`E_cv_end`：对应上面的数值。

这些常量在编译期和运行期都可用（类型级常量用于 MPL/类型计算，静态常量用于常规 C++ 代码/模板参数化时的数值判断）。


## 语义与用途示例

1. 作为枚举/索引使用：
   - 用 `E_cv_non`/`E_cv_const`/... 作为数组或表的索引，按 cv 情形选择对应策略或类型。

2. 作为位掩码判断：
   - 使用 `cv_const_t::value` 与 `cv_volatile_t::value` 的位组合可以快速判断某个标记值是否包含 `const` 或 `volatile` 标记（适用于将修饰信息编码为位域的场景）。

示例（静态断言）：

```cpp
static_assert(yggr::mplex::cv_mark_t::E_cv_non == 0, "cv_non == 0");
static_assert(yggr::mplex::cv_mark_t::E_cv_const == 1, "cv_const == 1");
static_assert(yggr::mplex::cv_mark_t::E_cv_volatile == 2, "cv_volatile == 2");
static_assert(yggr::mplex::cv_mark_t::E_cv_const_volatile == 3, "cv_const_volatile == 3");
static_assert(yggr::mplex::cv_mark_t::E_cv_end == 4, "cv_end == 4");
```

示例（按索引选择类型）：

```cpp
// 伪代码：有一个类型数组或 typelist，按 cv 标记选择对应的包装类型
using wrapper_t = mpl_at_c<wrappers, yggr::mplex::cv_mark_t::E_cv_const>::type;
```


## 设计考虑与契约
- 输入/输出：该文件只定义常量和类型别名，不包含运行时行为或函数。其契约是为上层元编程/运行时代码提供一套一致的 cv 标记值。
- 可用性：类型级别常量（`boost::mpl::integral_c`）适合用于 MPL 计算；静态数值常量（`E_*`）适合用于普通模板/运行时代码。
- 失败/异常模式：该文件没有失败路径或异常；错误通常出现在误用（例如把这些常量解释为其它语义）上。


## 边界情况与注意事项
- 值范围：当前设计把 `const` 与 `volatile` 分别映射到位 0 与位 1，且把 `cv_end` 定义为 `cv_const_volatile + 1`，因此后续若需要扩展更多标记（例如 `restrict`、`atomic` 等）需确保与现有位定义兼容。
- 可移植性：使用 `u32`（由项目定义）作为底层类型，通常为 32 位无符号整数，满足大多数索引/位运算场景。
- 命名：`E_cv_*` 风格的常量名与类型别名的命名共同存在，避免歧义；在 API 文档中建议同时引用两类常量以便不同使用场景的读者理解。


## 测试建议
- 添加静态断言以验证常量数值（如上示例），确保未来改动不会意外改变这些基础值。
- 在依赖该标记的元编程逻辑上添加单元测试，覆盖不同 cv 情形的分支（无修饰/const/volatile/const volatile）。

