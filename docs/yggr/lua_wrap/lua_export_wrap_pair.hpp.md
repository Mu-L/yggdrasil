# yggr::lua_wrap::lua_export_wrap_pair.hpp 文档

## 文件简介

`lua_export_wrap_pair.hpp` 是 yggdrasil 项目中用于将自定义包装 pair 类型（wrap_pair）导出到 Lua 的头文件。通过 luabind 库，将包装 pair 的构造、赋值、比较、成员访问、交换、拷贝等方法暴露给 Lua，便于在 Lua 层进行二元组操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_wrap_pair_r_other_fs`

```cpp
// 支持以其他 first/second 类型构造和赋值
template<typename RF, typename RS, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_pair_r_other_fs(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持以其他类型 first/second 构造和 set_first/set_second。

### 2. `export_wrap_pair_r_other`

```cpp
// 支持以其他 pair 类型构造、比较、赋值
template<typename R, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_pair_r_other(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持以其他 pair 类型构造、比较（==、<、<=）、compare_eq、compare。

### 3. `export_wrap_pair`

```cpp
// 导出 wrap_pair 到 Lua
template<typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_pair(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持多种构造函数（默认、first/second、拷贝）。
- 支持 tostring、swap、copy、get/set_first/second、比较、compare_eq、compare。

## 依赖

- `<yggr/mplex/static_assert.hpp>`
- `<yggr/lua_wrap/wrap_base_t.hpp>`
- `<yggr/lua_wrap/lua_export_typeid.hpp>`
- `<yggr/lua_wrap/wrap_pair.hpp>`
- Boost Type Traits
- luabind 库

## 用法示例

在 C++ 侧注册 wrap_pair：

```cpp
luabind::module(L)[
    export_wrap_pair<MyWrapPair, ...>(luabind::class_<MyWrapPair, ...>(...)),
    export_wrap_pair_r_other<MyOtherPair, MyWrapPair, ...>(luabind::class_<MyWrapPair, ...>(...)),
    export_wrap_pair_r_other_fs<MyFirst, MySecond, MyWrapPair, ...>(luabind::class_<MyWrapPair, ...>(...))
];
```
Lua 脚本可直接构造、赋值、比较、访问、交换等。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或 pair 导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
