# yggr::lua_wrap::lua_export_wrap_list.hpp 文档

## 文件简介

`lua_export_wrap_list.hpp` 是 yggdrasil 项目中用于将自定义包装链表（wrap_list）导出到 Lua 的头文件。通过 luabind 库，将包装链表的构造、赋值、插入、删除、遍历、容量、元素访问、合并、去重、排序等方法暴露给 Lua，便于在 Lua 层进行容器操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_wrap_list_r_wrap_base_t`

```cpp
// 支持以 wrap_base_t 为索引的构造、赋值、插入、resize 等
template<typename R, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_list_r_wrap_base_t(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持以 wrap_base_t 为索引的构造、赋值、插入、resize 等。

### 2. `export_wrap_list_r_other_iterator`

```cpp
// 支持以其他迭代器区间为参数的构造、赋值、插入
template<typename R, typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_list_r_other_iterator(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持以其他迭代器区间为参数的构造、赋值、插入。

### 3. `export_wrap_list`

```cpp
// 导出 wrap_list 到 Lua
template<typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_list(luabind::class_<T, X1, X2, X3>& cobj);
```
- 支持多种构造函数（默认、分配器、区间、拷贝等）。
- 支持 swap、copy、assign、get/set_allocator、get/set/front/back、begin/end/rbegin/rend、empty/size/max_size、clear、insert/erase/push/pop/resize、merge/splice/remove/reverse/unique/sort 等。
- 支持与多种迭代器、索引类型的组合操作。

## 依赖

- `<yggr/mplex/static_assert.hpp>`
- `<yggr/lua_wrap/wrap_base_t.hpp>`
- `<yggr/lua_wrap/lua_export_typeid.hpp>`
- `<yggr/lua_wrap/wrap_list.hpp>`
- Boost Type Traits
- luabind 库

## 用法示例

在 C++ 侧注册 wrap_list：

```cpp
luabind::module(L)[
    export_wrap_list<MyWrapList, ...>(luabind::class_<MyWrapList, ...>(...)),
    export_wrap_list_r_wrap_base_t<MyWrapBaseT, MyWrapList, ...>(luabind::class_<MyWrapList, ...>(...)),
    export_wrap_list_r_other_iterator<MyOtherIter, MyWrapList, ...>(luabind::class_<MyWrapList, ...>(...))
];
```
Lua 脚本可直接构造、赋值、插入、删除、遍历、访问、合并、去重、排序等。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或容器导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
