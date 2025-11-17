# `yggr::mplex::typename_caster`（文件：`yggr/mplex/typename_caster.hpp`）

## 概要
- **目的**：把一个模板实例的模板参数列表“搬移”到另一个模板上。即将 `Src<Args...>` 的参数 `Args...` 提取出来并应用到另一个模板 `Dst`，得到 `Dst<Args...>`。
- **位置**：`yggr/mplex/typename_caster.hpp`（与该文档同目录）
- **适用场景**：在模板元编程中需要把类型容器（或任意模板实例）的参数传递/转换给另一个模板。例如将 `std::vector<int,Alloc>` 的参数传给 `std::list`、或在模板算法中统一应用参数到不同模板。

## 主要实现与说明
- 主要模板：
  - `template<typename T> struct typename_caster;` —— 总体框架。

- C++11 变参模板实现（优先使用）：
  - 模板匹配形式：
    ```cpp
    template<template<typename ..._Args> class Src, typename ...Args>
    struct typename_caster< Src<Args...> >
    {
        template<template<typename ..._Args> class Dst>
        struct apply { typedef Dst<Args...> type; };
    };
    ```
  - 作用：当 `T` 是某个模板实例 `Src<Args...>` 时，`typename_caster<T>::apply<Dst>::type` 即为 `Dst<Args...>`。

- C++03 回退（没有 variadic templates）：
  - 使用预处理器循环（`BOOST_PP_LOCAL_ITERATE()` 与 `YGGR_PP_TEMPLATE_PARAMS_LEN()`）生成多重特化，适配不同的模板参数个数上限。
  - 该实现依赖项目内的 `YGGR_PP_*` 一系列宏（见 `yggr/ppex/typedef.hpp` 与预处理宏配置），以及 Boost.Preprocessor 的本地迭代机制。

- 暴露方式：
  - `using detail::typename_caster;` —— 将 `detail` 命名空间中的 `typename_caster` 导出到 `yggr::mplex`，便于直接使用。

## 使用示例
```cpp
#include <list>
#include <vector>
#include <type_traits>
#include <yggr/mplex/typename_caster.hpp>

// 假设 T 为 std::vector<int>
using T = std::vector<int>;

// 将 vector<int> 中的参数应用到 std::list，得到 std::list<int>
using caster = yggr::mplex::typename_caster<T>::apply<std::list>;
static_assert(std::is_same<caster::type, std::list<int>>::value, "converted to list<int>");

// 更通俗的别名用法（C++11 起）
// using list_from_vector = yggr::mplex::typename_caster<T>::apply<std::list>::type;
```

说明：对于带有多个模板参数（例如 `std::vector<T, Alloc>`），`Args...` 会包含全部参数，`Dst` 也必须接受相同数量和形式的模板参数。

## 注意事项与兼容性
- 在 C++11 及以上，变参模板实现更简洁且不依赖预处理循环。项目通过宏 `YGGR_NO_CXX11_VARIADIC_TEMPLATES` 控制是否启用回退实现。
- 回退实现依赖预处理宏与 Boost.Preprocessor，且通常只能生成到某个最大参数数（由 `YGGR_PP_TEMPLATE_PARAMS_LEN()` 控制）。当需要支持比该上限更多的模板参数时，必须调整该宏及相关预处理配置。
- `Src` 与 `Dst` 必须都是模板模板参数，且 `Dst` 必须接受与 `Src` 相同数量与形式的参数（例如 `typename/typename`）；对非类型参数或更复杂模板参数（如模板模板参数嵌套）可能不适用或需扩展。
