# yggr::lua_wrap::lua_export_wrap_foo_sort.hpp 文档

## 文件简介

`lua_export_wrap_foo_sort.hpp` 是 yggdrasil 项目中用于将通用排序算法（升序/降序）导出到 Lua 的头文件。通过 luabind 库，将 C++ 的 `wrap_foo_sort_aesc` 和 `wrap_foo_sort_desc` 排序算法以 `sort_aesc` 和 `sort_desc` 函数形式暴露给 Lua，便于在 Lua 层对容器或区间进行排序操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_foo_sort_aesc`

```cpp
// 导出升序排序算法到 Lua
template<typename RandomIt> inline
luabind::scope export_foo_sort_aesc(void);
```
- 通过 luabind，将 `wrap_foo_sort_aesc<RandomIt>` 以 `sort_aesc` 名称导出到 Lua。
- Lua 脚本可直接调用 `sort_aesc` 进行升序排序。

### 2. `export_foo_sort_desc`

```cpp
// 导出降序排序算法到 Lua
template<typename RandomIt> inline
luabind::scope export_foo_sort_desc(void);
```
- 通过 luabind，将 `wrap_foo_sort_desc<RandomIt>` 以 `sort_desc` 名称导出到 Lua。
- Lua 脚本可直接调用 `sort_desc` 进行降序排序。

## 依赖

- `<yggr/lua_wrap/wrap_foo_sort.hpp>`
- luabind 库

## 用法示例

在 C++ 侧注册排序算法：

```cpp
luabind::module(L)[
    export_foo_sort_aesc<MyRandomIter>(),
    export_foo_sort_desc<MyRandomIter>()
];
```
Lua 脚本可直接调用 `sort_aesc(iter_begin, iter_end)` 或 `sort_desc(iter_begin, iter_end)` 进行排序。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或算法导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
