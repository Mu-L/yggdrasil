# `yggr::mplex::tag_sfinae`（文件：`yggr/mplex/tag_sfinae.hpp`）

## 概要
- **目的**：提供一个用于 SFINAE（Substitution Failure Is Not An Error）模式的占位类型别名，方便在模板元编程和重载选择中使用。该文件仅定义简单别名，不包含复杂实现。
- **位置**：`yggr/mplex/tag_sfinae.hpp`（与该文档同目录）
- **包含依赖**：`yggr/mplex/null_t.hpp`（定义 `null_type`）

## 主要定义
- `typedef null_type tag_sfinae_type;`
  - 将项目中定义的 `null_type` 用于命名 `tag_sfinae_type`，作为 SFINAE 相关占位符。
- `typedef tag_sfinae_type* sfinae_type;`
  - 定义指向 `tag_sfinae_type` 的指针类型 `sfinae_type`。在 SFINAE 场景中经常使用指针或引用类型来实现可选模板参数或启用/禁用函数模板重载。

## 语义与用途说明
- `null_type`（定义在 `null_t.hpp` 中）通常表示一个空占位类型，用于模板元编程中占位或作为默认类型参数。
- 将 `tag_sfinae_type` 定义为 `null_type`，并进一步提供 `sfinae_type` 指针别名，是一种常见技巧：在模板参数列表中使用 `sfinae_type = 0`（或类似形式）可以触发 SFINAE 判断，从而在函数模板重载或特化时有条件地启用/禁用函数。

## 使用示例
```cpp
#include <type_traits>
#include <yggr/mplex/tag_sfinae.hpp>

// 示例：使用 sfinae_type 确认参数合法性

template<typename T> 
class A
{
  template<typename OT>
  A(typename boost::mpl::if_<boost::is_same<OT, char>, OT, sfinae_type>::type val = 0)
  {
    ...
  }
}



## 注意事项
- 该文件非常轻量，仅做类型别名封装；理解 `null_type` 的定义对于正确使用该别名很重要。
- `sfinae_type` 是 `tag_sfinae_type*`，因此在某些上下文中可能需要注意 `nullptr`/`0` 的兼容性（尤其在老编译器或 C++03 风格代码中）。
