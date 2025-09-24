# yggr::lua_wrap::lua_export_wrap_iterator_l_wrap_base_t.hpp 文档

## 文件简介

`lua_export_wrap_iterator_l_wrap_base_t.hpp` 是 yggdrasil 项目中用于将包装类型与包装迭代器的混合运算导出到 Lua 的头文件。通过 luabind 库，将包装类型（如 wrap_base_t）与包装迭代器的加法运算符暴露给 Lua，便于在 Lua 层实现“类型 + 迭代器”操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_wrap_iterator_l_wrap_base_t`

```cpp
// 导出 wrap_base_t + wrap_iterator 运算到 Lua
template<typename R, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_iterator_l_wrap_base_t(luabind::class_<T, X1, X2, X3>& wrap_base_cobj);
```
- 支持包装类型 T 与包装迭代器 R 的加法运算（T + R）。
- 便于在 Lua 脚本中直接进行“类型 + 迭代器”操作。

## 依赖

- `<yggr/mplex/static_assert.hpp>`
- `<yggr/lua_wrap/wrap_base_t.hpp>`
- `<yggr/lua_wrap/wrap_random_access_iterator.hpp>`
- `<yggr/lua_wrap/lua_export_typeid.hpp>`
- Boost Type Traits
- luabind 库

## 用法示例

在 C++ 侧注册类型与迭代器混合运算：

```cpp
luabind::module(L)[
    export_wrap_iterator_l_wrap_base_t<MyIter, MyWrapBaseT, ...>(luabind::class_<MyWrapBaseT, ...>(...))
];
```
Lua 脚本可直接进行 `wrap_base + wrap_iter` 运算。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或混合运算导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
