# 文件：pointer_to_value_t.hpp 文档

路径：`yggr/mplex/pointer_to_value_t.hpp`

## 概要
`pointer_to_value_t.hpp` 提供了元编程工具 `pointer_to_value_t<T>` 与配套机制，用于在编译期“解包”指针或指针样类型，得到其所指向或包装的值类型（去除 cv 修饰）。

主要用途：在模板元编程和泛型代码中，统一提取原始指针（`U*`）或智能指针/自定义包装（如 `shared_ptr<U>`）的 `U` 类型，以便在类型选择、引用映射或其他编译期计算中使用。


## 依赖
- `yggr/mplex/null_t.hpp`（定义 `null_type`，作为默认不可解包的占位）
- `yggr/ppex/symbols.hpp`（预处理器符号宏，供宏辅助展开使用）
- Boost.TypeTraits：`boost::remove_pointer`、`boost::remove_cv`、`boost::is_pointer`
- Boost.MPL：`boost::mpl::if_`（用于分支选择）
- 额外：文件末尾包含了 `yggr/mplex/detail/pointer_to_value_t_of_wrapper.hpp`，用于扩展或为各种包装类型提供 `unwrap_pointer` 的特化。


## 命名空间
位于 `yggr::mplex`，实现细节在 `yggr::mplex::detail`。


## API 与宏

- 模板：`template<typename T> struct pointer_to_value_t`
  - 语义：如果 `T` 是本机指针类型（`U*`），则 `pointer_to_value_t<T>::type` 为 `remove_cv<U>::type`；
    否则尝试使用 `detail::unwrap_pointer<T>::type`，并对其 `remove_cv`。
  - 若既不是本机指针，且 `unwrap_pointer<T>` 未被特化，则 `unwrap_pointer<T>` 的默认定义继承自 `null_type`，此时 `pointer_to_value_t<T>` 也会退化为 `null_type`（具体表现取决于 `pointer_to_value_t_imp` 的实现/继承）。

- 宏：
  - `YGGR_PP_POINTER_UNWRAP_DEF(__pointer_type__, __value_type__)`
    - 为 `detail::unwrap_pointer<__pointer_type__>` 提供显式特化，定义其 `typedef __value_type__ type;`。
    - 用于为外部或自定义指针类型注册如何解包获得值类型。

  - `YGGR_PP_POINTER_UNWRAP_SMART_POINTER_DEF(__template__, __suffix__)`
    - 为模板形式的智能指针（如 `template<typename T> class Ptr;`）生成解包特化，匹配 `__template__<T> __suffix__` 形式的声明。
    - 当宏变体没有后缀时可使用 `YGGR_PP_POINTER_UNWRAP_SMART_POINTER_DEF_NON_SUFFIX(__template__)`。

这些宏便利地把常见智能指针（例如 `shared_ptr<T>`、`unique_ptr<T>` 或库内包装）映射到其内部值类型。


## 实现细节

核心实现位于 `detail`：

- `detail::unwrap_pointer<T>` 默认继承自 `null_type`，表示未定义的解包。

- `detail::pointer_to_value_t_imp<T, is_native_ptr>`：
  - 当 `is_native_ptr == true`（`boost::is_pointer<T>::value`）时，特化使用 `boost::remove_pointer<T>::type` 提取指向类型，并 `boost::remove_cv` 去除 cv 修饰。
  - 当 `is_native_ptr == false` 时，使用 `unwrap_pointer<T>::type`（由宏或其它特化提供）并去除 cv。

- 顶层 `pointer_to_value_t<T>` 继承自 `detail::pointer_to_value_t_imp<T, boost::is_pointer<T>::value>`，因此对用户透明地暴露 `::type`。

- 最后包含的 `detail/pointer_to_value_t_of_wrapper.hpp` 很可能提供对常见包装类型（如 `std::unique_ptr`, `std::shared_ptr`, `boost::optional` 或项目自定义 Wrapper）的一组 `unwrap_pointer` 特化与辅助宏。


## 返回值语义
- 当成功解包（本机指针或已注册的包装类型）时，`pointer_to_value_t<T>::type` 为目标值类型且被 `remove_cv`（去除 const/volatile）。
- 当无法解包（既非本机指针，且未为该类型提供 `unwrap_pointer` 特化）时，`pointer_to_value_t<T>::type` 继承自 `null_type`（或具体实现可能导致编译失败），这样上层可以通过类型检测或 SFINAE 做出分支。


## 使用示例

```cpp
#include <yggr/mplex/pointer_to_value_t.hpp>
#include <yggr/mplex/null_t.hpp>

using namespace yggr::mplex;

// 本机指针
static_assert(std::is_same<pointer_to_value_t<int*>::type, int>::value, "int* -> int");
static_assert(std::is_same<pointer_to_value_t<const long*>::type, long>::value, "const long* -> long (cv removed)");

// 对于智能指针，需要在某处注册解包规则，例如（伪宏使用）：
// YGGR_PP_POINTER_UNWRAP_SMART_POINTER_DEF(std::shared_ptr, )
// 然后：
// static_assert(std::is_same<pointer_to_value_t<std::shared_ptr<MyType>>::type, MyType>::value);

// 未注册类型退化为 null_type
static_assert(std::is_same<pointer_to_value_t<int>::type, yggr::mplex::null_type>::value, "int is not a pointer -> null_type by default");
```

注意：上例 `pointer_to_value_t<int>::type` 为 `null_type` 仅在 `unwrap_pointer<int>` 的默认实现（继承自 `null_type`）保持不变时成立；有些编译器/配置下直接使用 `pointer_to_value_t<int>::type` 可能导致编译错误。推荐在模板中通过 `std::is_same<..., null_type>` 或类似方式显式检测是否解包成功。


## 注意事项与陷阱
- 包装类型支持依赖于 `unwrap_pointer` 的特化；若项目中未为常见智能指针或自定义包装提供 `unwrap_pointer`，请使用 `YGGR_PP_POINTER_UNWRAP_*` 宏或手动特化来注册。
- `remove_cv` 会去除 `const`/`volatile`，若需要保留 `const` 语义（例如 `const U*` -> `const U`），请在使用方自行处理或修改该 trait。
- 默认 `unwrap_pointer` 返回 `null_type`，若用户直接把未解包类型当作返回类型使用，可能产生不明确的编译错误；建议在模板中使用静态断言或 SFINAE 分支以给出清晰的诊断。


## 测试建议
- 为常见本机指针情形编写静态断言（`T*`, `const T*`）验证去 cv 后的类型。
- 检查并写测试为 `std::unique_ptr` / `std::shared_ptr` 等注册 `unwrap_pointer`（查看项目里的 `detail/pointer_to_value_t_of_wrapper.hpp`，它可能已为这些类型提供实现）。
- 验证未注册类型会返回 `null_type` 或导致合理的编译期错误，并在上层代码中以可检测方式处理该情形。

