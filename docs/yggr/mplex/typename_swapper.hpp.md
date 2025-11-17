# `yggr::mplex::typename_swapper`（文件：`yggr/mplex/typename_swapper.hpp`）

## 概要
- **目的**：提供一个用于交换二元模板（pair-like）类型模板参数顺序并暴露结果 traits 的小型元编程工具。主要用于将 `Pair<L, R>` 变换为 `Pair<R, L>`（或其等效 traits 表示），以便在模板推导或类型变换中使用。
- **位置**：`yggr/mplex/typename_swapper.hpp`（与该文档同目录）
- **适用场景**：需要在类型层面翻转成对（pair-like）类型参数的顺序，或生成以翻转后类型为参数的 traits/type 定义。例如在泛型适配器或类型映射中对键/值类型做互换。

## 主要实现说明
- 命名空间：`yggr::mplex`（实现细节在 `detail` 命名空间）。

- `detail::tpl_swapper<T>`（默认）：
  - 默认模板对任意类型继承自 `null_type`，表示不可交换或不匹配的类型。
  - 定义：
    ```cpp
    template<typename T>
    struct tpl_swapper : public null_type { };
    ```

- `detail::tpl_swapper< Pair<L, R> >`（特化）：
  - 对于匹配模板模板 `Pair`（形式为 `template<typename _L, typename _R> class Pair`）的实例，特化继承自 `traits< Pair<R, L> >`。
  - 等价效果：将 `Pair<L, R>` 的参数顺序翻转得到 `Pair<R, L>`，然后通过 `traits<...>` 暴露该翻转后的类型信息（由 `yggr/type_traits/traits.hpp` 提供）。
  - 定义：
    ```cpp
    template<typename L, typename R, template<typename _L, typename _R> class Pair>
    struct tpl_swapper< Pair<L, R> > : public traits< Pair<R, L> > { };
    ```

- 对外接口：
  - `template<typename T> struct typename_swapper : public detail::tpl_swapper<T> { }` —— 直接继承 `tpl_swapper` 的行为，作为公共入口使用。

- 依赖项：
  - `yggr/type_traits/traits.hpp`：用于包装和暴露类型信息（`traits<...>`）。
  - `yggr/mplex/null_t.hpp`：定义 `null_type`，用于表示未匹配或无效情形。

## 使用示例
```cpp
#include <type_traits>
#include <yggr/mplex/typename_swapper.hpp>

// 假设有一个简单pair模板：
template<typename A, typename B>
struct my_pair {};

// traits 假设将类型作为成员 type 暴露：
// traits<T>::type == T

using original = my_pair<int, double>;
using swapped_traits = yggr::mplex::typename_swapper<original>;

// 若 traits 的语义为提供 member `type`, 则：
using swapped_type = swapped_traits::type; // 应为 my_pair<double, int>

static_assert(std::is_same<swapped_type, my_pair<double, int>>::value, "swapped");
```

说明：示例依赖于项目中 `traits<T>` 的具体实现细节（通常 `traits<T>::type` 等于 `T`，并可能含有其他用途）。请根据项目中 `traits` 的定义适配示例。

## 语义与注意事项
- 该工具仅对满足特化匹配形式 `Pair<L, R>` 的类型有效（即 `Pair` 必须是接受两个类型参数的类模板）。
- 若传入的 `T` 不匹配该形式，`typename_swapper<T>` 将继承自 `null_type`，表示不可交换/不可用；使用时应对 `null_type` 做检测或提供备用分支。
- `traits< Pair<R, L> >` 的具体成员（例如 `type`、`value_type` 等）由 `traits` 的实现定义；文档示例假设 `traits<T>::type` 直接暴露了原始类型。

