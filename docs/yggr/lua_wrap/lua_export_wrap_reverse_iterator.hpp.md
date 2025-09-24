# yggr::lua_wrap::lua_export_wrap_reverse_iterator.hpp 文档

## 文件简介

`lua_export_wrap_reverse_iterator.hpp` 是 yggdrasil 项目中用于将自定义包装反向迭代器（wrap_reverse_iterator 及其 const 版本）导出到 Lua 的头文件。通过 luabind 库，将反向迭代器的构造、赋值、算术、比较、取值、赋值、前后移动等方法暴露给 Lua，便于在 Lua 层进行容器反向遍历和元素操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_wrap_reverse_iterator`

```cpp
// 导出反向迭代器到 Lua
template<typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_reverse_iterator(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持默认构造、拷贝构造、tostring、算术/比较运算符、swap、set_iterator、copy、get/set_value、前后移动、plus/minus/compare/next/prev 等。
- 针对随机访问迭代器和非随机访问迭代器分别处理 set_value、算术等。

### 2. `export_wrap_reverse_iterator_construct_other_iterator`

```cpp
// 支持由正向迭代器构造反向迭代器
template<typename R, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_reverse_iterator_construct_other_iterator(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持由正向迭代器构造反向迭代器。

### 3. `export_wrap_reverse_iterator_r_other_reverse_iterator`

```cpp
// 支持与其他反向迭代器的比较、算术等
template<typename R, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_reverse_iterator_r_other_reverse_iterator(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持与其他反向迭代器的 <、<=、==、-、minus、wraped_minus、compare_eq、compare。
- 非随机访问迭代器仅支持 ==、compare_eq。

### 4. `export_wrap_reverse_iterator_r_wrap_base_t`

```cpp
// 支持与 wrap_base_t 的混合运算和接口
template<typename R, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_reverse_iterator_r_wrap_base_t(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持 +、-、get_value、plus/minus/plus_set/minus_set。
- 随机访问迭代器支持 set_value。

## 依赖

- `<yggr/mplex/static_assert.hpp>`
- `<yggr/iterator_ex/iterator_category_check.hpp>`
- `<yggr/iterator_ex/is_const_iterator.hpp>`
- `<yggr/lua_wrap/lua_export_typeid.hpp>`
- `<yggr/lua_wrap/wrap_base_t.hpp>`
- `<yggr/lua_wrap/wrap_reverse_iterator.hpp>`
- Boost Type Traits
- luabind 库

## 用法示例

在 C++ 侧注册反向迭代器：

```cpp
luabind::module(L)[
    export_wrap_reverse_iterator<MyRIter, ...>(luabind::class_<MyRIter, ...>(...)),
    export_wrap_reverse_iterator_construct_other_iterator<MyIter, MyRIter, ...>(luabind::class_<MyRIter, ...>(...)),
    export_wrap_reverse_iterator_r_other_reverse_iterator<MyOtherRIter, MyRIter, ...>(luabind::class_<MyRIter, ...>(...)),
    export_wrap_reverse_iterator_r_wrap_base_t<MyWrapBaseT, MyRIter, ...>(luabind::class_<MyRIter, ...>(...))
];
```
Lua 脚本可直接反向遍历、比较、取值、赋值、前后移动等。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或迭代器导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
