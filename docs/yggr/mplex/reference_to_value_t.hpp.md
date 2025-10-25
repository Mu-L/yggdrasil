# 文件：reference_to_value_t.hpp 文档

路径：`yggr/mplex/reference_to_value_t.hpp`

## 概要
`reference_to_value_t.hpp` 提供了元编程工具 `reference_to_value_t<T>`，用于在编译期把“引用类型或引用样包装”转换为其指向/封装的值类型，并去除 cv 修饰（`const`/`volatile` 被移除）。

这个工具常见于需要从引用或引用包装（例如 `T&`、`std::reference_wrapper<T>` 或自定义引用包装）提取基础类型以便进行类型推导、映射或进一步转换（例如映射为指针/引用/容器元素类型）的场景。


## 依赖
- `yggr/base/yggrdef.h`（项目基础类型/宏）
- `yggr/type_traits/reference_checker.hpp`（项目内用于引用包装处理/兼容性支持）
- Boost.TypeTraits：`boost::remove_reference`、`boost::remove_cv`、`boost::unwrap_reference` 等


## 命名空间
位于 `yggr::mplex` 命名空间；实现细节在 `yggr::mplex::detail`。


## API 说明

模板：

```cpp
template<typename T>
struct reference_to_value_t;
```

语义：
- 若 `T` 是引用类型（`U&` 或 `const U&` 等），则 `reference_to_value_t<T>::type` 为 `typename boost::remove_cv<typename boost::remove_reference<T>::type>::type`（即去除引用与 cv 后的 `U`）。
- 若 `T` 不是引用类型，但为引用样包装（如 `std::reference_wrapper<U>`），则使用 `boost::unwrap_reference<T>::type` 提取基础类型，再去除 cv，作为结果类型。
- 该模板通过 `detail::reference_to_value_t_imp<T, boost::is_reference<T>::value>` 两分支实现，用户直接使用 `reference_to_value_t<T>::type` 即可。


## 实现要点

- `detail::reference_to_value_t_imp<T, false>`：当 `T` 不是引用时，继承自 `boost::remove_cv<typename boost::unwrap_reference<T>::type>`。
- `detail::reference_to_value_t_imp<T, true>`：当 `T` 是引用时，继承自 `boost::remove_cv<typename boost::remove_reference<T>::type>`。
- 顶层 `reference_to_value_t<T>` 继承自对应的 `imp`，暴露最终 `::type`。

注意：`boost::unwrap_reference<T>` 在标准库中能处理 `std::reference_wrapper<T>`，若项目中有自定义引用包装，需在 `reference_checker.hpp` 或其它地方提供支持/特化以使其可解包。


## 示例

```cpp
#include <type_traits>
#include <yggr/mplex/reference_to_value_t.hpp>

// 引用
static_assert(std::is_same<yggr::mplex::reference_to_value_t<int&>::type, int>::value, "int& -> int");
static_assert(std::is_same<yggr::mplex::reference_to_value_t<const long&>::type, long>::value, "const long& -> long (cv removed)");

// 对 std::reference_wrapper（需 unwrap_reference 支持）
using wrapper_t = std::reference_wrapper<double>;
static_assert(std::is_same<yggr::mplex::reference_to_value_t<wrapper_t>::type, double>::value, "reference_wrapper<double> -> double");
```


## 注意事项与约束
- `remove_cv` 会移除 `const` 与 `volatile`，因此 `reference_to_value_t<const T&>::type` 为裸 `T`，若想保留 `const` 语义需在调用处另行处理。
- `unwrap_reference` 的行为决定了对引用样包装的支持范围；若项目使用自定义包装类型，请确保 `boost::unwrap_reference` 或项目中的等价实现被特化以支持这些类型。
- 该工具仅在编译期进行类型映射，不影响运行时行为；当结果类型被用作返回类型或成员类型时，务必在运行时保证相应对象的生命周期安全。


## 测试建议
- 为常见情形添加静态断言：裸引用、带 const 的引用、`std::reference_wrapper`。
- 对自定义包装类型添加 `unwrap_reference` 的特化并为其添加测试用例。
- 在使用 `reference_to_value_t` 的上层模板中，增加静态断言或 SFINAE 分支来处理 `unwrap_reference` 失败的情形（以便给出更明确的错误提示）。


## 改进建议
- 提供现代 C++ 的别名模板：

```cpp
template<typename T>
using reference_to_value_t_t = typename reference_to_value_t<T>::type;
```
