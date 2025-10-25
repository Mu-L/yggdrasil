# 文件：index_t_value.hpp 文档

路径：`yggr/mplex/index_t_value.hpp`

## 概要
`index_t_value.hpp` 提供了一个小型的编译期适配工具 `index_t_value<T>`，用于把一个类型 `T`（必须提供 `T::value` 成员）的数值抽取为一个 Boost.MPL 的整型常量类型，且以库中统一的整型类型 `yggr::s64` 表示。

该头还定义了三个便捷宏：
- `YGGR_INDEX_T_VALUE_DEF(__type__, __value__)`：为给定类型显式定义 `index_t_value_detail<__type__>` 的特化，方便注册某些类型对应的索引值。
- `YGGR_INDEX_T_VALUE_GET(__type__)`：获得 `index_t_value<__type__>::value`，作为整数常量使用。
- `YGGR_INDEX_T_VALUE_GET_CAST(__cast_type__, __type__)`：以指定类型 `__cast_type__` 将该值静态转换并取得。

此工具多见于需要把类型级别索引或序号统一为有符号 64 位值以便运行时或其它元编程模块（例如数组索引、映射表索引或序号化机制）使用的场景。


## 依赖
- `yggr/base/yggrdef.h`（包含 `yggr::s64` 等项目基础类型别名）
- Boost.MPL：`boost/mpl/integral_c.hpp`（用于生成 MPL 的整型常量类型）


## 命名空间
位于 `yggr::mplex` 命名空间；实现细节在 `yggr::mplex::detail` 下。


## API 说明

模板与实现：

- detail::index_t_value_detail<T>
  - 默认实现通过继承 `boost::mpl::integral_c<yggr::s64, static_cast<yggr::s64>(T::value)>`，也就是把 `T::value` 强制转换为 `yggr::s64` 并封装为 MPL 的整型常量类型。
  - 用户可以通过 `YGGR_INDEX_T_VALUE_DEF` 宏为某些 `__type__` 提供显式特化（例如当 `T` 本身没有 `::value`，或希望覆盖默认值时）。

- template<typename T> struct index_t_value
  - 继承自 `detail::index_t_value_detail<T>::type`，从而暴露 `::value`（整型常量）给调用方。
  - 因为 `index_t_value` 继承自 `::type`，可像 MPL 整型常量一样使用，例如 `index_t_value<T>::value`。


宏说明：

- YGGR_INDEX_T_VALUE_DEF( __type__, __value__ )
  - 生成 `detail::index_t_value_detail<__type__>` 的显式偏特化，继承自 `boost::mpl::integral_c<yggr::s64, static_cast<yggr::s64>(__value__)>`。
  - 用法示例：

    YGGR_INDEX_T_VALUE_DEF(my_type_tag, 42);

  - 注意：该宏直接在 `yggr::mplex::detail` 命名空间中定义特化，确保类型名 `__type__` 是可用的且在宏调用处可见。

- YGGR_INDEX_T_VALUE_GET( __type__ )
  - 宏展开为 `yggr::mplex::index_t_value< __type__ >::value`，便于在代码中直接使用该整型常量。

- YGGR_INDEX_T_VALUE_GET_CAST( __cast_type__, __type__ )
  - 将 `index_t_value<__type__>::value` 静态转换为 `__cast_type__` 并返回结果，便于在需要特定整数类型的上下文（例如数组下标为 `std::size_t`）中使用。


## 使用示例

1) 直接从类型 `T` 的 `::value` 抽取（当 T 定义了 ::value 时）：

```cpp
struct my_tag { static const std::size_t value = 5; };

// 使用 index_t_value
using idx_t = yggr::mplex::index_t_value<my_tag>;
static_assert(idx_t::value == static_cast<yggr::s64>(5), "value match");

// 使用宏直接获得
auto v = YGGR_INDEX_T_VALUE_GET(my_tag); // v is a compile-time constant expression
```

2) 使用宏为不可直接读取的类型或外部类型注册值：

```cpp
// 当某个类型没有 ::value 或你想覆盖值时
YGGR_INDEX_T_VALUE_DEF(external_tag, 100);
static_assert(YGGR_INDEX_T_VALUE_GET(external_tag) == 100, "registered value");

// 获取并按需转换
std::size_t idx = YGGR_INDEX_T_VALUE_GET_CAST(std::size_t, external_tag);
```


## 设计契约与注意事项
- `T` 必须提供 `T::value` 可在编译期常量上下文中求值，或通过 `YGGR_INDEX_T_VALUE_DEF` 显式注册。
- `T::value` 将被 `static_cast<yggr::s64>(...)` 强制转换为 `yggr::s64`：
  - 若 `T::value` 超出 `yggr::s64` 的范围，可能发生截断或未定义行为（取决于源类型与转换规则）。建议确保被表示的索引值在 `yggr::s64` 的范围内。
- `index_t_value` 将结果以 `yggr::s64`（有符号 64 位）表示，这是项目在元编程中统一索引/序号的惯例；如需无符号类型或其他宽度类型，请使用 `YGGR_INDEX_T_VALUE_GET_CAST` 并传入合适的类型或在调用处显式转换。


## 边界情况与安全性
- 当 `T` 未提供 `::value` 且未通过 `YGGR_INDEX_T_VALUE_DEF` 注册特化，直接实例化 `index_t_value<T>` 会导致编译错误（因为尝试访问 `T::value`）。在这种情形下应使用宏注册或提供相应的特化实现。
- 注册宏 `YGGR_INDEX_T_VALUE_DEF` 定义特化时请注意命名空间与包含顺序，确保在使用 `YGGR_INDEX_T_VALUE_GET` 前已可见该特化。


## 测试建议
- 测试直接从类型 `T::value` 抽取的常见整数值（正数、0、边界值）；确认 `index_t_value<T>::value` 与 `static_cast<yggr::s64>(T::value)` 一致。
- 测试用 `YGGR_INDEX_T_VALUE_DEF` 为外部类型注册值，并确保 `YGGR_INDEX_T_VALUE_GET` 和 `YGGR_INDEX_T_VALUE_GET_CAST` 返回期望值及类型。
- 测试超出 `s64` 范围的值行为（建议不要使用超范围值，或在文档中注明限制）。

