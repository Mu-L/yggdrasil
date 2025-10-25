# 文件：null_t.hpp 文档

路径：`yggr/mplex/null_t.hpp`

## 概要
`null_t.hpp` 定义了一个简单的占位类型 `null_t` 及其别名 `null_type`，在元编程中用作“无类型”或“未提供类型”的哨兵（sentinel）。这是一个轻量的标记类型，常在模板参数默认值、类型映射和 SFINAE 场景中作为占位使用。

该头非常小且无外部依赖（仅使用项目基础头），适合在库内部统一表示“空类型”概念。


## 内容与 API
文件仅包含：

```cpp
struct null_t { typedef null_t type; };

typedef null_t null_type;
```

- `null_t`：一个空的结构体，提供 `typedef null_t type;`，符合某些元编程习惯（例如方便在 MPL/traits 中引用 `::type`）。
- `null_type`：`null_t` 的类型别名，作为库中通用的“无类型”占位符。


## 命名空间
- 定义在 `yggr::mplex` 命名空间中，使用时请带上命名空间前缀或相应的 using 声明。


## 用途与示例
典型用法：
- 模板参数默认值：当模板参数未指定时使用 `null_type` 作为占位，表示“未提供类型”。
- 类型映射：配合 `null_t_to` 或类似工具，将 `null_type` 映射为具体类型（如 `void`、`default_t` 等）。
- SFINAE / traits：在需要表示“无类型”结果的 traits 中返回 `null_type`，而不是抛出编译错误。

示例：

```cpp
#include <yggr/mplex/null_t.hpp>
#include <yggr/mplex/null_t_to.hpp>

using yggr::mplex::null_type;

template<typename T = null_type>
struct wrapper { /* ... */ };

// 当 T == null_type 时，把它转换为 void 作为默认实际类型
using actual_t = typename yggr::mplex::null_t_to<T, void>::type;
```


## 设计意图与契约
- 目的：提供一个统一的、可识别的类型占位符，避免使用特殊值（如 `void`）直接作为占位导致语义模糊或不可用。
- 契约：`null_type` 表示“无类型/未提供”，应仅在编译期类型选择、traits 返回或作为模板占位场景中使用；不要在需要实际对象或完整类型语义的上下文中当作可实例化类型使用。


## 使用注意事项
- `null_type` 不是 `void`，在某些情况下二者不可互换；若需要 `void` 行为，请配合 `null_t_to` 或显式映射。
- 当把 `null_type` 传递给需要完整类型（例如定义成员、创建对象等）的模板时会触发编译错误；这是期望的保护行为，提示使用者要提供具体类型或使用映射工具。


## 测试建议
- 编写简单的静态断言或类型别名测试，确保 `null_type` 可以被 `std::is_same`/`boost::is_same` 识别，并能与 `null_t_to` 正确映射：

```cpp
static_assert(std::is_same<yggr::mplex::null_type, yggr::mplex::null_t::type>::value, "null_type alias ok");
using mapped = yggr::mplex::null_t_to<yggr::mplex::null_type, void>::type;
static_assert(std::is_same<mapped, void>::value, "null_type -> void mapping works");
```
