---
# user_config.hpp 文档

## 文件简介

user_config.hpp 是 Yggdrasil 工程的用户自定义配置头文件。该文件用于集中管理和覆盖工程默认配置，允许开发者根据实际需求自定义类型支持、特性开关、第三方库适配等。所有用户级别的宏定义和兼容性调整建议在此文件中进行，便于后续升级和维护。

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

### 1. 宽字符与宽字符串支持

- 若定义了 `YGGR_NO_CWCHAR`，则自动定义 `YGGR_NO_WSTRING`，禁用宽字符串支持。

### 2. MinGW 下字符类型支持（注释示例）

- 针对 MinGW 平台，建议禁用 `char8_t`、`char16_t`、`char32_t` 支持（已注释，按需启用）。

### 3. ICU 支持（注释示例）

- 可选启用 `BOOST_HAS_ICU`，用于 Boost 的 ICU 支持（已注释，按需启用）。

### 4. Boost 兼容性修正

- 定义 `YGGR_FIX_BOOST_UNORDERED_TRY_EMPLACE_HINT_NOT_MOVE_KEY`，修复 Boost `unordered_map` 的 `try_emplace` 在带 hint 时 key 未移动的问题。

### 5. 用户自定义配置区（建议在此添加自定义宏）

- 推荐将所有自定义特性开关、默认行为等宏定义放在此处，便于集中管理。
- 示例（已注释）：
  - `YGGR_USE_UTF8_EX_MODE`：启用 UTF8 扩展模式
  - `YGGR_HEX_CONV_DEFAULT_MODE`：设置十六进制转换默认模式
  - `YGGR_LUA_THREAD_SAFE`：启用 Lua 线程安全

---

## 用法说明

- 在需要自定义工程行为、兼容性或特性时，直接在本文件中添加或取消注释相关宏定义。
- 推荐不要直接修改工程其他配置头文件，所有用户级别的配置建议集中在本文件。

````cpp
// 启用 UTF8 扩展模式
#ifndef YGGR_USE_UTF8_EX_MODE
#   define YGGR_USE_UTF8_EX_MODE
#endif
````

---

## 注意事项

- 必须在包含本文件前先包含 `<yggr/base/yggrdef.h>`。
- 修改本文件后建议重新编译整个工程，确保配置生效。
- 注释部分为常用配置示例，按需取消注释即可生效。

---

 

