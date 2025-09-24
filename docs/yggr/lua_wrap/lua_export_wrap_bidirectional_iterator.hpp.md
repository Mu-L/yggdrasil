# yggr::lua_wrap::lua_export_wrap_bidirectional_iterator.hpp 文档

## 文件简介

`lua_export_wrap_bidirectional_iterator.hpp` 是 yggdrasil 项目中用于将自定义包装双向迭代器（wrap_bidirectional_iterator 及其 const 版本）导出到 Lua 的头文件。通过 luabind 库，将迭代器的构造、赋值、遍历、比较、取值等方法暴露给 Lua，便于在 Lua 层进行容器遍历和元素操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_wrap_bidirectional_iterator`

```cpp
// 导出双向迭代器到 Lua
template<typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_bidirectional_iterator(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持默认构造、拷贝构造、tostring、== 运算符。
- 支持 swap、set_iterator、copy、get_value、set_value、前后增减、比较、next/prev 等。

### 2. `export_wrap_bidirectional_iterator_r_const_iterator`

```cpp
// 支持与 const_iterator 的比较和接口
template<typename R, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_bidirectional_iterator_r_const_iterator(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持与 const_iterator 的 ==、compare_eq。

### 3. `export_wrap_bidirectional_const_iterator`

```cpp
// 导出双向 const 迭代器到 Lua
template<typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_bidirectional_const_iterator(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持默认构造、拷贝构造、tostring、== 运算符。
- 支持 swap、set_iterator、copy、get_value、前后增减、比较、next/prev 等。

### 4. `export_wrap_bidirectional_const_iterator_r_iterator`

```cpp
// 支持 const_iterator 与 iterator 的转换和比较
template<typename R, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_bidirectional_const_iterator_r_iterator(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持由 iterator 构造 const_iterator，set_iterator、==、compare_eq。

## 依赖

- `<yggr/mplex/static_assert.hpp>`
- `<yggr/lua_wrap/lua_export_typeid.hpp>`
- `<yggr/lua_wrap/wrap_base_t.hpp>`
- `<yggr/lua_wrap/wrap_bidirectional_iterator.hpp>`
- Boost Type Traits
- luabind 库

## 用法示例

在 C++ 侧注册双向迭代器：

```cpp
luabind::module(L)[
    export_wrap_bidirectional_iterator<MyIter, ...>(luabind::class_<MyIter, ...>(...)),
    export_wrap_bidirectional_const_iterator<MyConstIter, ...>(luabind::class_<MyConstIter, ...>(...)),
    export_wrap_bidirectional_iterator_r_const_iterator<MyConstIter, MyIter, ...>(luabind::class_<MyIter, ...>(...)),
    export_wrap_bidirectional_const_iterator_r_iterator<MyIter, MyConstIter, ...>(luabind::class_<MyConstIter, ...>(...))
];
```
Lua 脚本可直接遍历、比较、取值、赋值、前后移动等。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或迭代器导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
