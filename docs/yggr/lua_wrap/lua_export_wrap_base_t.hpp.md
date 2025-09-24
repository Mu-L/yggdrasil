# yggr::lua_wrap::lua_export_wrap_base_t.hpp 文档

## 文件简介

`lua_export_wrap_base_t.hpp` 是 yggdrasil 项目中将lua中不支持的基础类型（比如u64）以wrap_base_t的方式导出到 Lua 的头文件。通过 luabind 库，将包装类型的构造、算术/逻辑/位运算、赋值、比较等方法和运算符暴露给 Lua，便于在 Lua 层进行丰富的数值和逻辑操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_wrap_base_t`

```cpp
// 导出 wrap_base_t 到 Lua
template<typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_base_t(luabind::class_<T, X1, X2, X3>& cobj);
```
- 静态断言类型 T 必须为 wrap_base_t。
- 支持多种构造函数（默认、值、字符串、半类型、拷贝）。
- 支持 tostring、算术运算符（+、-、*、/）、比较运算符（==、<、<=）、逻辑运算符、位运算符等。
- 支持 set_value、get_value、swap、copy、plus/minus/multiplies/divides/modulus 及其 set 版本、逻辑与或非、比较、位移、位与或异或等丰富接口。

### 2. `export_wrap_base_t_other`

```cpp
// 支持不同类型 wrap_base_t 之间的运算和赋值
template<typename OT, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_base_t_other(luabind::class_<T, X1, X2, X3>& cobj);
```
- 静态断言 OT、T 均为 wrap_base_t。
- 支持与其他类型的 wrap_base_t 进行构造、算术、赋值、比较、逻辑、位运算等。

## 依赖

- `<yggr/mplex/static_assert.hpp>`
- `<yggr/lua_wrap/wrap_base_t.hpp>`
- `<yggr/lua_wrap/lua_export_typeid.hpp>`
- `<yggr/lua_wrap/wrap_random_access_iterator.hpp>`
- Boost Type Traits
- luabind 库

## 用法示例

在 C++ 侧注册 wrap_base_t：

```cpp
luabind::module(L)[
    export_wrap_base_t<MyWrapBaseT, ...>(luabind::class_<MyWrapBaseT, ...>(...)),
    export_wrap_base_t_other<OtherWrapBaseT, MyWrapBaseT, ...>(luabind::class_<MyWrapBaseT, ...>(...))
];
```
Lua 脚本可直接构造、赋值、算术、逻辑、位运算、比较等。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或包装类型导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
