# yggr::lua_wrap::lua_export_wrap_allocator.hpp 文档

## 文件简介

`lua_export_wrap_allocator.hpp` 是 yggdrasil 项目中用于将自定义包装分配器（wrap_allocator）导出到 Lua 的头文件。通过 luabind 库，将包装分配器的构造、方法和运算符暴露给 Lua，便于在 Lua 层进行内存分配相关操作和对象管理。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. `export_wrap_allocator`

```cpp
// 导出 wrap_allocator 到 Lua
template<typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_wrap_allocator(luabind::class_<T, X1, X2, X3>& cobj);
```
- 静态断言类型 T 必须为 wrap_allocator。
- 导出构造函数、拷贝构造、tostring、== 运算符。
- 导出成员方法：
  - `get_allocator`：获取底层分配器
  - `copy`：拷贝分配器
  - `max_size`：分配器最大容量
  - `wraped_max_size`：包装后最大容量
  - `compare_eq`：分配器相等性比较

## 依赖

- `<yggr/mplex/static_assert.hpp>`
- `<yggr/lua_wrap/wrap_allocator.hpp>`
- `<yggr/lua_wrap/lua_export_typeid.hpp>`
- Boost Type Traits
- luabind 库

## 用法示例

在 C++ 侧注册 wrap_allocator：

```cpp
luabind::module(L)[
    export_wrap_allocator<MyWrapAllocator, ...>(luabind::class_<MyWrapAllocator, ...>(...))
];
```
Lua 脚本可直接构造、拷贝、比较、调用分配器相关方法。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或分配器导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
