# yggr::lua_wrap::lua_export_wrap_foo_shuffle.hpp 文档

## 文件简介

`lua_export_wrap_foo_shuffle.hpp` 是 yggdrasil 项目中用于将通用洗牌算法（shuffle）导出到 Lua 的头文件。通过 luabind 库，将 C++ 的 `wrap_foo_shuffle` 洗牌算法以 `shuffle` 函数形式暴露给 Lua，便于在 Lua 层对容器或区间进行元素随机重排操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_foo_shuffle`

```cpp
// 导出 shuffle 算法到 Lua
template<typename RandomIt> inline
luabind::scope export_foo_shuffle(void);
```
- 通过 luabind，将 `wrap_foo_shuffle<RandomIt>` 以 `shuffle` 名称导出到 Lua。
- Lua 脚本可直接调用 `shuffle` 进行区间洗牌。

## 依赖

- `<yggr/lua_wrap/wrap_foo_shuffle.hpp>`
- luabind 库

## 用法示例

在 C++ 侧注册 shuffle 算法：

```cpp
luabind::module(L)[
    export_foo_shuffle<MyRandomIter>()
];
```
Lua 脚本可直接调用 `shuffle(iter_begin, iter_end)` 进行洗牌。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或算法导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
