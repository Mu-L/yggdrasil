# yggr::lua_wrap::lua_export_wrap_foo_find.hpp 文档

## 文件简介

`lua_export_wrap_foo_find.hpp` 是 yggdrasil 项目中用于将通用查找算法（find）导出到 Lua 的头文件。通过 luabind 库，将 C++ 的 `wrap_foo_find` 查找算法以 `find` 函数形式暴露给 Lua，便于在 Lua 层对容器或区间进行查找操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_foo_find`

```cpp
// 导出 find 算法到 Lua
template<typename InputIt, typename T> inline
luabind::scope export_foo_find(void);
```
- 通过 luabind，将 `wrap_foo_find<InputIt, T>` 以 `find` 名称导出到 Lua。
- Lua 脚本可直接调用 `find` 进行查找。

## 依赖

- `<yggr/lua_wrap/wrap_foo_find.hpp>`
- luabind 库

## 用法示例

在 C++ 侧注册 find 算法：

```cpp
luabind::module(L)[
    export_foo_find<MyIter, MyValueType>()
];
```
Lua 脚本可直接调用 `find(iter_begin, iter_end, value)` 进行查找。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或算法导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
