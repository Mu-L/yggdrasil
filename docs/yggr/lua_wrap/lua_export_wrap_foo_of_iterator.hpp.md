# yggr::lua_wrap::lua_export_wrap_foo_of_iterator.hpp 文档

## 文件简介

`lua_export_wrap_foo_of_iterator.hpp` 是 yggdrasil 项目中用于将常用迭代器操作（如 advance、distance、next、prev 等）以函数形式导出到 Lua 的头文件。通过 luabind 库，将 C++ 迭代器相关算法以全局函数方式暴露给 Lua，便于在 Lua 层对迭代器进行操作和遍历。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 迭代器操作导出函数

- `export_foo_advance`：导出 advance（原地推进迭代器）
- `export_foo_advance_copy`：导出 advance_copy（推进副本）
- `export_foo_distance` / `export_foo_wraped_distance`：导出 distance、wraped_distance（计算距离）
- `export_foo_next` / `export_foo_next_n`：导出 next（下一个/推进 n 步）
- `export_foo_prev` / `export_foo_prev_n`：导出 prev（上一个/回退 n 步）

所有函数均以 luabind::scope 形式返回，可直接用于模块注册。

## 依赖

- `<yggr/lua_wrap/wrap_foo_of_iterator.hpp>`
- luabind 库

## 用法示例

在 C++ 侧注册迭代器操作：

```cpp
luabind::module(L)[
    export_foo_advance<MyIter, int>(),
    export_foo_distance<MyIter, MyIter>(),
    export_foo_next<MyIter>(),
    export_foo_prev<MyIter>(),
    // ... 其他接口
];
```
Lua 脚本可直接调用 `advance(iter, n)`、`distance(iter1, iter2)`、`next(iter)`、`prev(iter)` 等。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或迭代器操作导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
