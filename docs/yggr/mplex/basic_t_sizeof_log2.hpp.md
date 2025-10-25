# 文件：basic_t_sizeof_log2.hpp 文档

路径：`yggr/mplex/basic_t_sizeof_log2.hpp`

## 概要
`basic_t_sizeof_log2.hpp` 提供了一个编译期工具 `basic_t_sizeof_log2`，用于计算类型 `T` 的 `sizeof(T)` 的以 2 为底的对数（log2）的整数形式，作为编译期常量类型（继承自 `integer_log2<sizeof(T)>::type`）。

该工具仅在 `T` 可检查为算术类型或枚举类型时有效（使用 `boost::is_arithmetic<T>` 或 `::yggr::is_enum<T>` 判定）。否则会退化为失败类型 `basic_t_sizeof_log2_failed`。

主要用途：在模板元编程中根据类型大小选择对齐、索引位宽、缓冲区分割级别或生成与类型大小相关的常量（例如位操作、层数计算等）。


## 依赖
- `yggr/base/yggrdef.h`（项目基础定义，包含 `size_type` 等）
- `yggr/type_traits/is_enum.hpp`（项目内对枚举的检测）
- `yggr/mplex/integer_log2.hpp`（用于计算整数的 log2，返回一个类型或失败类型）
- `boost/type_traits/is_arithmetic.hpp`（用于检测算术类型）

请确保这些头在编译配置中可用。


## 命名空间
实现位于 `yggr::mplex::detail`，并通过 `yggr::mplex::basic_t_sizeof_log2` 暴露给外部。


## API 说明

类型别名/模板：

- `using detail::basic_t_sizeof_log2_failed;`
  - 该类型表示计算失败时返回的失败类型，别名自 `integer_log2_failed`（注意 `integer_log2` 模块中定义的失败类型）。

- template<typename T> struct basic_t_sizeof_log2
  - 继承自 `detail::basic_t_sizeof_log2_detail<T>::type`。
  - 当 `T` 可检查为算术类型或枚举时，继承自 `integer_log2<sizeof(T)>::type`，该类型通常是一个包含编译期常量的类型（例如 `boost::mpl::integral_c<std::size_t, V>` 或类似类型），可通过 `::value` 访问结果数值或通过 `::type` 继续元编程。
  - 当 `T` 不可检查（例如类类型且非枚举）时，继承自 `basic_t_sizeof_log2_failed`，表示不可用/失败。

使用（示意）：

```cpp
using v_t = yggr::mplex::basic_t_sizeof_log2<int>;
static_assert(v_t::value == /* 例如 sizeof(int)=4 -> log2(4)=2 */ 2, "log2(sizeof(int)) should be 2");
```

注意：实际 `.value` 的语义和存在性依赖于 `integer_log2<...>::type` 的实现（通常是 MPL 风格的 integral constant），建议查看 `yggr/mplex/integer_log2.hpp` 的定义以确认访问方式。


## 实现细节

- `typedef integer_log2_failed basic_t_sizeof_log2_failed;`
  - 将 `integer_log2` 模块的失败类型（拼写可能为 `integer_log2_failed`，保留原始命名）重新命名为 `basic_t_sizeof_log2_failed`，便于上层使用。

- `basic_t_sizeof_log2_detail<T, checkable>`：
  - 模板二分支：
    - 当 `checkable` 为 `false`（即 `T` 既不是算术类型也不是枚举），`basic_t_sizeof_log2_detail<T, false>` 继承自 `basic_t_sizeof_log2_failed`，表示不适用/失败。
    - 当 `checkable` 为 `true`，`basic_t_sizeof_log2_detail<T, true>` 继承自 `integer_log2<sizeof(T)>::type`，使用 `sizeof(T)` 的值去计算整数 log2。

- 顶层模板 `basic_t_sizeof_log2<T>` 继承自 `detail::basic_t_sizeof_log2_detail<T>::type`，将内部决策结果暴露给用户。


## 合约（Contract）
- 输入：模板参数 `T`（任意类型）。
- 输出：编译期常量类型，表示 `sizeof(T)` 的对数值（或失败类型）。通常可使用 `typename basic_t_sizeof_log2<T>::value` 或 `::value` 访问数值，具体取决于 `integer_log2` 的返回类型。
- 失败模式：当 `T` 不是算术类型也不是枚举类型时，结果类型为 `basic_t_sizeof_log2_failed`（代表不可用）。
- 不会抛出运行时异常——这是完全的编译期工具。


## 边界情况与注意事项
- `integer_log2` 的行为决定了对非 2 的幂的 `sizeof` 值如何处理：
  - 如果 `integer_log2` 计算的是向下取整的 log2（floor），那么例如 `sizeof(T)=3` 会返回 `1`（因为 floor(log2(3))==1）。
  - 如果 `integer_log2` 在遇到非正数或不适用的值时会返回失败类型，则 `basic_t_sizeof_log2` 也会对应返回失败类型。请参考 `yggr/mplex/integer_log2.hpp` 以确认具体行为。

- 对于自定义类（非枚举）类型，尽管 `sizeof(T)` 总是可在编译期获得，但该实现有意限制在算术或枚举类型上进行检查，可能是出于语义或安全考虑（例如仅对 POD/原始类型使用该工具）。如果你确实需要对任意类型求 `sizeof` 并取 log2，可考虑调整 `checkable` 判定或提供单独的工具。

- `basic_t_sizeof_log2_failed` 的确切类型与语义位于 `integer_log2` 实现中；在使用前应确认该失败类型是否可以与其它元编程组件兼容。


## 使用示例

```cpp
#include <type_traits>
#include <yggr/mplex/basic_t_sizeof_log2.hpp>

using t_char = yggr::mplex::basic_t_sizeof_log2<char>;
static_assert(t_char::value == 0, "sizeof(char)==1 -> log2==0");

using t_int = yggr::mplex::basic_t_sizeof_log2<int>;
// 假设 sizeof(int)==4 -> log2(4)==2
static_assert(t_int::value == 2, "sizeof(int)==4 -> log2==2");

// 对于类类型（非枚举、非算术），结果为失败类型
struct Foo { double a; };
using t_foo = yggr::mplex::basic_t_sizeof_log2<Foo>;
// t_foo 可能为 basic_t_sizeof_log2_failed，使用前需检查。

// 若需要在模板中安全使用，可写静态选择：
#include <boost/mpl/if.hpp>
#include <yggr/mplex/basic_t_sizeof_log2.hpp>

// 伪代码：根据是否为失败类型选择分支（具体检测方法请根据项目中失败类型的定义调整）
```


## 测试建议
- 为常见算术类型编写静态断言：`char`, `short`, `int`, `long`, `float`, `double` 等，验证 `::value` 符合预期。
- 测试枚举类型，确认枚举被视为可检查类型并正确计算。
- 测试非算术非枚举类型（如自定义类、结构体），确认得到 `basic_t_sizeof_log2_failed`。
- 测试当 `sizeof(T)` 为非 2 的幂时 `integer_log2` 的行为，以确定是否需要额外的断言或处理。


