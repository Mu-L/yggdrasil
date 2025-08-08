---
# script_lua_cfg.hpp 文档

## 文件简介

script_lua_cfg.hpp 用于配置 Yggdrasil 工程中 Lua 脚本支持的兼容性宏，确保不同版本的 Lua（如 5.1、5.2、5.3、5.4）在工程中能统一使用特定特性。该文件通过定义一系列 Lua 兼容性宏，提升 Lua 脚本集成的灵活性和兼容性。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- 必须先包含 `<yggr/base/yggrdef.h>`，否则编译报错。

---

## 主要内容

### 1. Lua 64位整数支持

- `LUA_USELONGLONG`  
  启用 Lua 对 long long（64位整数）的支持，适用于 Lua 5.1.4 及以上版本。

### 2. Lua 兼容性宏

- `LUA_COMPAT_ALL`  
  启用所有 Lua 5.2 兼容特性，适用于 Lua 5.2.1 及以上版本。

- `LUA_COMPAT_5_2`  
  启用 Lua 5.2 兼容特性，适用于 Lua 5.3.4 及以上版本。

- `LUA_COMPAT_5_1`  
  启用 Lua 5.1 兼容特性，适用于 Lua 5.3.4 及以上版本。

### 3. 宏定义逻辑

- 若未定义上述宏，则自动进行定义，确保 Lua 集成时具备所需兼容性。

---

## 用法说明

- 只需在工程中包含本头文件，即可自动为 Lua 脚本集成配置好兼容性宏，无需手动干预。
- 推荐在所有 Lua 相关代码之前包含本文件，保证宏定义生效。

````cpp
#include <yggr/base/script_lua_cfg.hpp>
extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}
````

---

## 注意事项

- 必须先包含 `<yggr/base/yggrdef.h>`，否则会编译报错。
- 这些宏会影响 Lua 源码的编译和行为，确保在包含 Lua 头文件前定义。
- 若工程中有特殊 Lua 版本需求，可根据实际情况调整宏定义。

---

 

