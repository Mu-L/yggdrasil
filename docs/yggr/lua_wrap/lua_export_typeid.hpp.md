# yggr::lua_wrap::lua_export_typeid.hpp 文档

## 文件简介

`lua_export_typeid.hpp` 是 yggdrasil 项目中用于将 C++ 类型信息导出到 Lua 的头文件。它通过 luabind 库，将 C++ 的 `typeid` 功能以函数形式导出，便于在 Lua 层获取 C++ 对象的类型信息。

## 命名空间结构

- `yggr`
  - `lua_wrap`
    - `detail`

## 主要内容

### 1. `detail::typeid_`

```cpp
// 获取对象的 C++ 类型信息
template<typename T> inline
const std::type_info& typeid_(const T& obj);
```
- 返回传入对象的 `std::type_info`。
- 用于后续导出到 Lua。

### 2. `export_typeid`

```cpp
// 导出 typeid 到 Lua
template<typename T> inline
luabind::scope export_typeid(void);
```
- 通过 luabind，将 `typeid` 函数导出到 Lua。
- 返回 luabind 的 scope，可用于模块注册。
- Lua 脚本可通过此接口获取 C++ 对象的类型信息。

## 依赖

- C++ 标准库 `<typeinfo>`
- luabind 库
- 项目内头文件 `<yggr/base/yggrdef.h>`、`<yggr/ppex/cast_to_string.hpp>`

## 用法示例

在 C++ 侧注册：
```cpp
luabind::module(L)
[
    export_typeid<MyClass>()
];
```
Lua 脚本可通过 `typeid(obj)` 获取 `obj` 的类型信息。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或类型导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
