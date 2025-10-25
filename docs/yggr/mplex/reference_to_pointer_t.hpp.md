# 文件：reference_to_pointer_t.hpp 文档

路径：`yggr/mplex/reference_to_pointer_t.hpp`

## 概要
`reference_to_pointer_t.hpp` 提供了编译期类型变换工具 `reference_to_pointer_t<T>`，用于把“引用类型或可解包引用样类型”映射到对应的指针类型（例如 `U&` -> `U*`，或对 `std::reference_wrapper<U>` / 自定义包装解包后再加指针）。

该工具区分原始本机引用与其它包装引用（或不可直接解包的类型），并利用 `boost::add_pointer`、`boost::remove_reference` / `boost::unwrap_reference` 等 type trait 实现泛化处理。

主要用途：在泛型代码或元编程中需要把某个引用类型转换为可传递/可存储的指针类型时使用，例如生成回调、存储引用目标地址或统一接口时。


## 依赖
- `yggr/base/yggrdef.h`（项目基础类型/宏）
- `yggr/type_traits/reference_checker.hpp`（项目内用于判断/处理引用的工具，确保 `boost::unwrap_reference` 可用或项目自定义的引用 wrapper 行为）
- Boost.TypeTraits：`boost::add_pointer`、`boost::remove_reference`、`boost::remove_cv`（间接通过 unwrap/traits 使用）


## 命名空间
位于 `yggr::mplex` 命名空间；实现细节位于 `yggr::mplex::detail`。


## 模板原型与行为

模板：

```cpp
template<typename T>
struct reference_to_pointer_t;
```

语义：
- 如果 `T` 是引用类型（例如 `U&` / `const U&`），则 `reference_to_pointer_t<T>::type` 为 `U*`（即 `remove_reference<T>::type *`，`const` 修饰保留在指向类型上：`const U&` -> `const U*`）。
- 如果 `T` 不是本机引用，而是引用样包装（例如 `std::reference_wrapper<U>`），则使用 `boost::unwrap_reference<T>::type` 提取基础类型，再对其 `add_pointer`。
- 由 `detail::reference_to_pointer_t_imp<T, boost::is_reference<T>::value>` 根据 `is_reference` 分支选择实现。

实现细节（两个分支）：
- `reference_to_pointer_t_imp<T, true>` （当 `T` 是引用类型）
  - 继承自 `boost::add_pointer< typename boost::remove_reference<T>::type >`。

- `reference_to_pointer_t_imp<T, false>` （当 `T` 不是引用类型）
  - 继承自 `boost::add_pointer< typename boost::unwrap_reference<T>::type >`。

最后 `reference_to_pointer_t<T>` 继承自对应的 `imp` 实现，从而暴露 `::type`。


## 使用示例

```cpp
#include <yggr/mplex/reference_to_pointer_t.hpp>

// 常见情形
using p1 = yggr::mplex::reference_to_pointer_t<int&>::type;       // int*
using p2 = yggr::mplex::reference_to_pointer_t<const long&>::type; // const long*

// 对于 std::reference_wrapper（前提：boost::unwrap_reference 支持或项目提供兼容）
using wrapper_t = std::reference_wrapper<double>;
using p3 = yggr::mplex::reference_to_pointer_t<wrapper_t>::type;  // double*

// 注意：返回的是指针类型的别名，实际运行时使用时需要确保指针所指对象有效
```


## 语义细节与约束
- `const` 保留：实现对 `const` 的保留由 `remove_reference` 与 `add_pointer` 的组合自然产生，例如 `const T&` -> `const T*`。
- `volatile`：文件没有显式去除 `volatile`，因此 `volatile` 会随 `remove_reference` 保留在目标指针指向类型（可按需在外层再移除）。
- 对于非引用且不支持 `unwrap_reference<T>` 的类型，`boost::unwrap_reference<T>::type` 的行为决定是否能成功得到 `::type`；若 `unwrap_reference` 未定义或不适用，结果可能在实例化时导致编译错误。


## 注意事项与陷阱
- 生命周期安全：`reference_to_pointer_t` 只是类型变换；在运行时代码中从引用得到指针时需要保证引用所指对象在指针使用期间仍然有效，避免悬挂指针。
- 对 `T` 为非引用且 `unwrap_reference` 未提供特化的情形，编译会失败或产生不可用的 `::type`，使用前请确认 `T` 的种类或提供相应的 `unwrap_reference` 特化。
- `boost::unwrap_reference` 需要对应于项目对引用包装器的支持（例如 `std::reference_wrapper`）；若项目自定义了引用包装器，请在 `reference_checker.hpp` 或其他地方确保 `unwrap_reference` 被支持。


## 测试建议
- 编写静态断言覆盖常见情形：`int&`、`const T&`、`std::reference_wrapper<T>` 等。
- 在运行时代码中把引用地址取出并转换为 `reference_to_pointer_t<T>::type` 的指针，确保实际指向对象在使用期内仍然有效。
- 对不支持的包装/自定义类型测试清晰的编译期错误并在需要时为其添加 `unwrap_reference` 支持或文档说明。
