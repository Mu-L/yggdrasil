# strict_sizeof.hpp

文件路径: `yggr/mplex/strict_sizeof.hpp`

## 概述

`strict_sizeof.hpp` 提供了一组元编程工具，用于在编译期以“严格”方式获取类型大小（以字节或位为单位）。它对类类型和某些特殊类型的处理更为保守：默认将类类型的记录大小视为 0，强制库用户显式为这些类型注册期望大小（通过宏 `YGGR_PP_REG_STRICT_SIZEOF`）或使用兼容版本 `compatible_strict_sizeof`。

设计目标：
- 防止对未知/不完全/特殊的类类型不安全地使用 `sizeof`（设计上通过把类类型的默认 `strict_sizeof_helper` 值设为 0 来强制显式注册）。
- 提供可替换（兼容）版本以在无法或不想注册时使用原生 `sizeof`。
- 提供以位为单位的包装（乘以 8）。

## 头文件依赖

- `yggr/base/yggrdef.h`
- Boost：`boost/static_assert.hpp`、`boost/type_traits/is_class.hpp`、`boost/mpl/size_t.hpp`

## 提供的宏与模板

- 宏 `YGGR_PP_REG_STRICT_SIZEOF( __type__, __size__ )`
  - 用法：在 `yggr::mplex::detail` 命名空间内为特定类型特化 `strict_sizeof_helper`，把该类型的“严格大小”作为 `boost::mpl::size_t<__size__>::type` 返回。
  - 例如：

    ```cpp
    YGGR_PP_REG_STRICT_SIZEOF(MyType, 16)
    // 相当于在 yggr::mplex::detail 中写了:
    // template<> struct strict_sizeof_helper<MyType> : public boost::mpl::size_t<16>::type {};
    ```

- 模板 `detail::strict_sizeof_helper<T>`
  - 默认实现：
    - 对于 class 类型（`boost::is_class<T>::value == true`）返回 `0`（使用 `boost::mpl::size_t<0>`），
    - 否则返回 `sizeof(T)`。
  - 目的是对类类型强制“未注册即视为未知（0）”，从而使 `strict_sizeof<T>` 在未注册时触发静态断言，提醒用户处理。

- 模板 `strict_sizeof<T>`
  - 返回 `detail::strict_sizeof_helper<T>::value`（以字节为单位），并且在内部有一个 `BOOST_STATIC_ASSERT((now_size_type::value));`，确保返回值非零（也就是：如果 `strict_sizeof_helper` 为 0，将导致编译错误）。
  - 作用：严格获取类型大小，只在明确注册或非 class 类型时生效。

- 模板 `compatible_strict_sizeof<T>`
  - 返回 `detail::strict_sizeof_helper<T>::value ? detail::strict_sizeof_helper<T>::value : sizeof(T)`。
  - 也会 `BOOST_STATIC_ASSERT` 结果非零。即如果 helper 为 0（例如默认的类类型），将退回到 `sizeof(T)`。
  - 作用：提供更兼容的行为，允许在未注册类型上仍使用 `sizeof`（但如果 `sizeof(T)` 无效（例如不完整类型），编译器会报错）。

- 模板 `strict_sizeof_bit<T>` 与 `compatible_strict_sizeof_bit<T>`
  - 上述两者分别乘以 8，返回以“位”为单位的大小（通过 `boost::mpl::size_t< bytes*8 >::type` 实现），并同样带有静态断言检查。

## 语义与使用策略

- 对于内置/非类类型（如整数、浮点、指针等）：
  - `strict_sizeof<T>::value` 等于 `sizeof(T)`（默认实现），并通过静态断言检查非零。

- 对于类类型（struct/class）：
  - 默认 `detail::strict_sizeof_helper<T>::value` 为 `0`。因此 `strict_sizeof<T>` 将触发 `BOOST_STATIC_ASSERT`，以强制用户意识到该类型需要显式注册大小。
  - 若不想注册，可以使用 `compatible_strict_sizeof<T>`，它会回退到 `sizeof(T)`（前提是 `sizeof(T)` 在该上下文是可用的）。

- 注册自定义大小：
  - 使用 `YGGR_PP_REG_STRICT_SIZEOF(MyType, 24)` 在 `yggr::mplex::detail` 中插入对 `MyType` 的特化，使 `strict_sizeof<MyType>::value == 24`。

## 示例

```cpp
#include <yggr/mplex/strict_sizeof.hpp>

// 基本类型
static_assert(yggr::mplex::strict_sizeof<int>::value == sizeof(int), "int size");

// 类类型（未注册） - 将导致编译期静态断言失败：
// struct Foo {};
// yggr::mplex::strict_sizeof<Foo>::value; // 触发 BOOST_STATIC_ASSERT

// 为类类型注册大小：
YGGR_PP_REG_STRICT_SIZEOF(
    MyRegisteredType, 16
)
// 现在:
// yggr::mplex::strict_sizeof<MyRegisteredType>::value == 16

// 兼容版本（不强制注册）：
// yggr::mplex::compatible_strict_sizeof<Foo>::value == sizeof(Foo)

// 位级别：
// yggr::mplex::strict_sizeof_bit<int>::value == sizeof(int) * 8
```

## 错误与边界情况

- 如果对一个不完整类型调用 `compatible_strict_sizeof<T>`，并且 `strict_sizeof_helper<T>::value` 为 0（即未注册），将退回到 `sizeof(T)` —— 这在对不完整类型上会导致编译错误（无效的 sizeof）。因此 `compatible_strict_sizeof` 并不能完全避免对不完整类型的错误。

- `strict_sizeof<T>` 默认对 class 类型触发断言，这是一种“保守策略”，可防止意外依赖类布局，但需要维护者为库中重要的类显式注册大小。要注意：如果类是聚合或标准布局类型而且想直接使用 `sizeof`，应使用 `compatible_strict_sizeof` 或通过宏注册。

- 目前 `detail::strict_sizeof_helper` 通过 `boost::is_class<T>::value` 判断 class 类型，C++20 之后可以考虑更准确的“不完整类型检测”或使用 `std::is_complete`（若可用）来改进策略，但在 C++11/C++03 中没有标准方法检测类型是否不完整。

## 测试建议

- 覆盖场景：
  - 原始内置类型（int/char/float/pointer）的 `strict_sizeof` 与 `compatible_strict_sizeof`。
  - 类类型：未注册时 `strict_sizeof` 引发静态断言；注册后返回指定值。
  - 对不完整类类型，验证 `compatible_strict_sizeof` 在退回到 `sizeof(T)` 时是否触发编译错误（以确保行为符合预期）。
  - `strict_sizeof_bit` 与 `compatible_strict_sizeof_bit` 的正确性（单位换算）。

- 推荐在测试中使用 `BOOST_STATIC_ASSERT` 或 `static_assert`（根据项目对 C++11 的支持），比如：

```cpp
BOOST_STATIC_ASSERT(( yggr::mplex::strict_sizeof<int>::value == sizeof(int) ));
```

- 添加一个单元测试文件 `test/strict_sizeof_test.cpp`，包含上面几类断言和注册示例。


## 结论

`strict_sizeof.hpp` 提供了一个保守的类型大小策略：内置与 POD 类型使用 `sizeof`，而 class 类型默认被视为未知并强制注册以避免误用。对于需要在编译期强保证类型大小（例如序列化、内存布局校验等场景），这是一个有价值的防护措施。若希望更宽松的行为，可以使用 `compatible_strict_sizeof` 或为相关类型使用 `YGGR_PP_REG_STRICT_SIZEOF` 显式注册。

---
