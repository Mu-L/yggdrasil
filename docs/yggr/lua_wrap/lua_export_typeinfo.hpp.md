# yggr::lua_wrap::lua_export_typeinfo.hpp 文档

## 文件简介

`lua_export_typeinfo.hpp` 是 yggdrasil 项目中用于将 C++ 的 `std::type_info` 类型信息导出到 Lua 的头文件。它通过 luabind 库，将类型信息的 `name()` 方法等接口暴露给 Lua，便于在 Lua 层获取和比较 C++ 类型信息。

## 命名空间结构

- `yggr`
  - `lua_wrap`
    - `detail`
    - `patch`（条件编译下）

## 主要内容

### 1. `operator<<` 重载

```cpp
// 支持 std::ostream << std::type_info
template<typename Char, typename Traits>
std::basic_ostream<Char, Traits>& operator<<(std::basic_ostream<Char, Traits>& os, const std::type_info& info);
```
- 允许直接将 `std::type_info` 输出到流，输出类型名。

### 2. `patch::type_info_dot_name`

```cpp
// 某些编译器/Boost 版本下的兼容性补丁
template<typename T> inline const char* type_info_dot_name(const T& info);
```
- 返回类型名字符串。
- 仅在特定条件下启用（如 MSVC 低版本或部分 Boost 版本）。

### 3. `export_type_info`

```cpp
// 导出 type_info 到 Lua
template<typename T, typename X1, typename X2, typename X3> inline
luabind::class_<T, X1, X2, X3>& export_type_info(luabind::class_<T, X1, X2, X3>& cobj);
```
- 为 luabind class 增加 `name` 方法（返回类型名）、`tostring`、`==` 运算符等。
- 兼容不同编译环境。

## 依赖

- C++ 标准库 `<typeinfo>`
- luabind 库
- 项目内头文件 `<yggr/base/yggrdef.h>`、`<yggr/ppex/cast_to_string.hpp>`

## 用法示例

在 C++ 侧注册 type_info：

```cpp
luabind::module(L)[
    export_type_info<type_info, ...>(luabind::class_<type_info, ...>(...))
];
```
Lua 脚本可通过 `obj:name()` 获取类型名，通过 `==` 比较类型。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或类型导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
