# 文件：pointer_to_reference_t.hpp 文档

路径：`yggr/mplex/pointer_to_reference_t.hpp`

## 概要
`pointer_to_reference_t.hpp` 提供了把“指针/指针样类型”在类型层面转换为对应引用类型的元编程工具 `pointer_to_reference_t<T>`。该工具用于将指针或指针样包装类型映射为其所指向对象的引用类型（例如 `U*` -> `U&`，`smart_ptr<U>` -> `U&`）。

实现分为两条分支：
- 对本机指针类型（`T` 满足 `boost::is_pointer<T>::value`）使用 `boost::remove_pointer<T>::type` 提取基础类型再加引用；
- 对“非本机指针”的指针样类型（例如智能指针或自定义包装）使用 `unwrap_pointer<T>::type`（来自 `pointer_to_value_t.hpp`）提取其指向类型再加引用。

最终通过 `boost::add_reference`（`T&`）生成引用


## 依赖
- `yggr/mplex/pointer_to_value_t.hpp`（定义 `unwrap_pointer<T>`，用于从指针样类型中提取值类型）
- Boost.TypeTraits：`boost::add_reference`、`boost::remove_volatile`、`boost::is_pointer`


## 命名空间
位于 `yggr::mplex` 命名空间；实现细节在 `yggr::mplex::detail` 内。


## API & 类型说明

模板：

- `template<typename T> struct pointer_to_reference_t`
  - 该模板继承自 `detail::pointer_to_reference_t_imp<T, boost::is_pointer<T>::value>`。
  - 实际结果类型可通过 `pointer_to_reference_t<T>::type` 或直接继承的 MPL/类型包装访问（通常为 `T&` 形式）。

内部实现（关键特化）：

- `pointer_to_reference_t_imp<T, true>`（当 `T` 为本机指针时）
  - 继承自 `boost::add_reference< typename boost::remove_volatile< typename boost::remove_pointer<T>::type >::type >`。
  - 语义：先 `remove_pointer` 得到 `U`，再 `remove_volatile`，最后 `add_reference` 得到 `U&` 或 `const U&`（若 `U` 带 `const`）。

- `pointer_to_reference_t_imp<T, false>`（当 `T` 不是本机指针时）
  - 继承自 `boost::add_reference< typename boost::remove_volatile< typename unwrap_pointer<T>::type >::type >`。
  - 语义：对智能指针或用户自定义包装，使用 `unwrap_pointer<T>::type` 提取内部值类型，然后同样去 `volatile` 并加引用。


## 语义细节与约束
- `unwrap_pointer<T>`：该工具来自 `pointer_to_value_t.hpp`，其行为决定了对智能指针/容器等的解包策略。若 `unwrap_pointer<T>` 未能为某类型提供 `::type`，则 `pointer_to_reference_t` 的实例化会失败。
- 引用生命周期：`pointer_to_reference_t<T>::type` 只是类型级别的引用（如 `U&`），实际使用时必须确保所返回引用所指对象在运行时具有足够生命周期，避免悬挂引用。


## 使用示例

```cpp
#include <yggr/mplex/pointer_to_reference_t.hpp>

// 假设 T = int*
using ref1 = yggr::mplex::pointer_to_reference_t<int*>::type; // int&

// 假设 T = const long*
using ref2 = yggr::mplex::pointer_to_reference_t<const long*>::type; // const long&

// 假设 T = std::shared_ptr<MyType>（前提：unwrap_pointer<std::shared_ptr<MyType>>::type == MyType）
using ref3 = yggr::mplex::pointer_to_reference_t<std::shared_ptr<MyType>>::type; // MyType&
```

示例说明：`pointer_to_reference_t` 更侧重于“类型级别的映射”；在实际函数或接口中，只有保证传入的对象确实存在且生命周期足够时，才可返回或保存由该工具推导的引用类型。


## 测试建议
- 对本机指针：对 `T = U*`、`T = const U*`、`T = U* volatile` 等情况写静态断言，验证 `pointer_to_reference_t<T>::type` 与预期一致。
- 对智能指针/包装类型：打开并检查 `pointer_to_value_t.hpp` 中 `unwrap_pointer` 的实现，编写针对 `std::unique_ptr`、`std::shared_ptr`、自定义包装指针的静态断言（前提项目已为这些类型提供 `unwrap_pointer` 特化）。
- 错误分支：测试当 `unwrap_pointer<T>` 不存在或未定义 `::type` 时的编译错误信息，确保能给出可理解的错误提示（如必要，可在 `unwrap_pointer` 添加更友好的 static_assert）。

