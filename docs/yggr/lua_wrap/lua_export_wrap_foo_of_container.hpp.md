# yggr::lua_wrap::lua_export_wrap_foo_of_container.hpp 文档

## 文件简介

`lua_export_wrap_foo_of_container.hpp` 是 yggdrasil 项目中用于将常用容器操作（如 size、resize、empty、clear、迭代器等）以函数形式导出到 Lua 的头文件。通过 luabind 库，将 C++ 容器的常用成员函数以全局函数方式暴露给 Lua，便于在 Lua 层对容器进行操作和遍历。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 容器属性与操作导出函数

- `export_foo_size` / `export_foo_wraped_size` / `export_foo_ssize` / `export_foo_wraped_ssize`：导出 size、wraped_size、ssize、wraped_ssize
- `export_foo_resize`：导出 resize（支持不同参数）
- `export_foo_empty`：导出 empty
- `export_foo_clear`：导出 clear

### 2. 迭代器相关导出函数

- `export_foo_ref_begin` / `export_foo_cref_begin` / `export_foo_cbegin`：导出 begin/const begin
- `export_foo_ref_end` / `export_foo_cref_end` / `export_foo_cend`：导出 end/const end
- `export_foo_ref_rbegin` / `export_foo_cref_rbegin` / `export_foo_crbegin`：导出 rbegin/const rbegin
- `export_foo_ref_rend` / `export_foo_cref_rend` / `export_foo_crend`：导出 rend/const rend

所有函数均以 luabind::scope 形式返回，可直接用于模块注册。

## 依赖

- `<yggr/lua_wrap/wrap_foo_of_container.hpp>`
- luabind 库

## 用法示例

在 C++ 侧注册容器操作：

```cpp
luabind::module(L)[
    export_foo_size<MyContainer>(),
    export_foo_resize<MyContainer, int>(),
    export_foo_empty<MyContainer>(),
    export_foo_clear<MyContainer>(),
    export_foo_ref_begin<MyContainer>(),
    export_foo_ref_end<MyContainer>(),
    // ... 其他接口
];
```
Lua 脚本可直接调用 `size(cont)`、`resize(cont, n)`、`empty(cont)`、`begin_(cont)` 等。

## 版权声明

本文件遵循 MIT 协议。

---

如需进一步了解 luabind 的用法或容器操作导出机制，请参考 luabind 官方文档或 yggdrasil 项目文档。
