# yggr/lua_wrap/wrap_base_t_maker.hpp 文档

## 文件概述

`wrap_base_t_maker.hpp` 提供了一个类型萃取工具 `wrap_base_t_maker`，用于根据类型自动选择是否需要包装为 `wrap_base_t`。该机制主要用于 Lua/C++ 交互时，对特定类型（如 u64、s64）进行特殊包装，保证类型在 Lua 环境下的正确性和兼容性。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 前置声明
- `template<typename Val> class wrap_base_t;`
  - 用于后续类型特化。

### 2. 模板结构体 `wrap_base_t_maker<T>`
- **主模板**：
  - `typedef T type;`  // 默认不做包装，直接返回原类型
- **特化模板**：
  - `wrap_base_t_maker<u64>`：type 为 `wrap_base_t<u64>`
  - `wrap_base_t_maker<s64>`：type 为 `wrap_base_t<s64>`
- **用途**：
  - 在泛型代码中自动为 u64、s64 类型选择包装类型，其它类型保持原样。

## 依赖关系
- `yggr/base/yggrdef.h`
- 依赖 `wrap_base_t` 的定义（通常在 `wrap_base_t.hpp` 中实现）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_base_t_maker.hpp>

// 泛型代码中：
typedef yggr::lua_wrap::wrap_base_t_maker<u64>::type U64WrapType; // 得到 wrap_base_t<u64>
typedef yggr::lua_wrap::wrap_base_t_maker<int>::type IntWrapType; // 仍为 int
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
