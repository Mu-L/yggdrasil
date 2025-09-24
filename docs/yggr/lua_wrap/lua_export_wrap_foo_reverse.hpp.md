# yggr::lua_wrap::lua_export_wrap_foo_reverse.hpp 文档

## 文件简介

`lua_export_wrap_foo_reverse.hpp` 是 yggdrasil 项目中用于将通用反转算法（reverse）导出到 Lua 的头文件。通过 luabind 库，将 C++ 的 `wrap_foo_reverse` 反转算法以 `reverse` 函数形式暴露给 Lua，便于在 Lua 层对容器或区间进行元素反转操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_foo_reverse`

```cpp
// 导出 reverse 算法到 Lua
template<typename BidirIt> inline
luabind::scope export_foo_reverse(void);
```
- 通过 luabind，将 `wrap_foo_reverse<BidirIt>` 以 `reverse` 名称导出到 Lua。
- Lua 脚本可直接调用 `reverse` 进行区间反转。

## 依赖

- `<yggr/lua_wrap/wrap_foo_reverse.hpp>`
- luabind 库

## 用法示例

在 C++ 侧注册 reverse 算法：

```cpp
luabind::module(L)[
    export_foo_reverse<MyBidirIter>()
];
```
Lua 脚本可直接调用 `reverse(iter_begin, iter_end)` 进行反转。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或算法导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
