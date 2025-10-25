# 文件：null_t_to.hpp 文档

路径：`yggr/mplex/null_t_to.hpp`

## 概要
`null_t_to.hpp` 定义了小型的元编程适配器 `null_t_to`（及一个便捷别名 `null_t_to_void`），用于在编译期将一个类型 `null_type` 替换为目标类型 `To`，否则保持原类型 `T` 不变。

这个工具在编写通用元编程组件（例如模板参数默认占位、类型选取、类型映射）时很有用：当某处使用 `null_type` 表示“没有类型”或“未提供类型”时，可以通过 `null_t_to<...>` 将其统一映射到实际需要的占位类型（例如 `void`、`default_t` 或特定类型）。


## 依赖
- `yggr/mplex/null_t.hpp`（定义 `null_type`）

该头文件本身不依赖 Boost 或其它库，只使用简单的模板特化技术实现功能。


## 命名空间
位于 `yggr::mplex` 命名空间。


## API 说明

模板：`null_t_to<T, To>`

- 定义：
  - 默认版本 `null_t_to<T, To>` 将 `typedef T type;`（保持原类型）。
  - 特化版本 `null_t_to<null_type, To>` 将 `typedef To type;`（当第一个参数为 `null_type` 时返回 `To`）。

- 语义：如果第一个模板参数是 `null_type`（表示“无类型”或占位），则 `type` 别名表示目标类型 `To`；否则 `type` 为原始类型 `T`。

别名模板：`null_t_to_void<T>`

- 定义：
  - `null_t_to_void<T>` 继承自 `null_t_to<T, void>`，也就是在 `T == null_type` 时返回 `void`，否则返回 `T`。

- 用途：方便把 `null_type` 映射为 `void` 的常见情形，便于在 SFINAE、返回类型选取、或占位符处理时使用。


## 使用示例

```cpp
#include <yggr/mplex/null_t_to.hpp>
#include <yggr/mplex/null_t.hpp>

using yggr::mplex::null_type;

// 情形 1: 普通类型不变
using A = yggr::mplex::null_t_to<int, double>::type; // A == int

// 情形 2: null_type 被替换为目标类型
using B = yggr::mplex::null_t_to<null_type, std::string>::type; // B == std::string

// 情形 3: 便捷别名，将 null_type -> void
using C = yggr::mplex::null_t_to_void<null_type>::type; // C == void
using D = yggr::mplex::null_t_to_void<float>::type;     // D == float
```

示例场景：模板的默认参数为 `null_type`，但在实际使用时希望将 `null_type` 映射为 `void` 或其它类型用于函数返回或类型别名。


## 设计意图与契约
- 输入：模板参数 `T`（任意类型）和目标类型 `To`。
- 输出：`null_t_to<T, To>::type`，当 `T == null_type` 时等于 `To`，否则等于 `T`。
- 错误/异常模型：本工具在编译期工作，不会引入运行时错误；若误用（例如将不可用类型作为 `To`），错误会在实例化时表现为编译错误。


## 边界情况与注意事项
- `null_type` 标识必须来自 `yggr/mplex/null_t.hpp`（同一命名空间），否则特化不会被匹配。
- `To` 可以是任何合法类型，包括 `void`、指针、模板实例等；确保在上下文中 `To` 可被接受（比如作为返回类型或成员类型）。
- `null_t_to_void` 是常用映射（`null_type` -> `void`），但在某些环境下 `void` 可能不适合作为类型别名（例如当期望完整类型时），请据具体场景选择合适的 `To`。


## 测试建议
- 添加编译期静态断言以确认映射行为：
  - `null_t_to<int, X>::type` 为 `int`。
  - `null_t_to<null_type, X>::type` 为 `X`（测试多种 `X`，例如 `void`, `std::nullptr_t`, 自定义类型）。
- 在更复杂的模板中使用 `null_t_to` 做默认类型映射，验证 SFINAE/重载选择行为是否与期望一致。

