---
# yggr_config.h 文档

## 文件简介

yggr_config.h 是 Yggdrasil 工程的全局配置头文件，负责平台、编译器、架构等环境的自动检测与宏定义，并集中管理各类编译选项、兼容性设置和特性开关。该文件是整个工程的基础配置入口，需在包含前确保已包含 `<yggr/base/yggrdef.h>`。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`（必须先包含）
- `<boost/config.hpp>`
- `<yggr/base/version.hpp>`
- `<yggr/base/user_config.hpp>`
- `<yggr/base/yggr_cpp_ver_config.hpp>`
- `<yggr/base/boost_cpp_version_check.hpp>`
- `<yggr/base/script_lua_cfg.hpp>`
- `<yggr/base/script_python_cfg.hpp>`
- `<yggr/base/compiler_config.hpp>`
- `<yggr/base/container_cfg.hpp>`
- `<yggr/base/endian.hpp>`
- `<yggr/base/noexcept_cfg.hpp>`
- `<yggr/base/constexpr_cfg.hpp>`
- `<yggr/base/attribute_cfg.hpp>`
- `<yggr/base/if_constexpr_cfg.hpp>`
- `<yggr/base/cpp17_features_cfg.hpp>`
- `<yggr/base/cpp20_features_cfg.hpp>`

---

## 主要功能

### 1. 编译器与平台检测

自动检测并定义如下宏：

- 编译器相关：`YGGR_MSVC`, `YGGR_GCC`, `YGGR_CLANG`, `YGGR_INTEL`, `YGGR_BORLANDC`, `YGGR_CODEGEARC`, `YGGR_EMBTC`
- 架构相关：`YGGR_ARM`, `YGGR_ARM64`, `YGGR_RISCV`, `YGGR_X86`, `YGGR_X86_64`
- 平台相关：`YGGR_AT_WINDOWS`, `YGGR_AT_LINUX`, `YGGR_AT_DARWIN`, `YGGR_AT_IOS`, `YGGR_AT_ANDROID`, `YGGR_AT_MOBILE`
- 系统位数：`YGGR_SYSTEM_64`

### 2. MSVC 警告转错误

在 MSVC 下，将常见的编译警告提升为错误，保证代码质量（可通过 `YGGR_WARNING_NOT_TO_ERROR` 关闭）。

### 3. 宏定义说明

文件中详细注释了所有可用的编译宏及其作用，包括但不限于：

- 平台与架构相关宏
- 字符串与字符集相关宏
- 文件系统相关宏
- C++ 标准版本相关宏
- 容器与字符串实现选择
- 兼容性与优化开关
- 第三方库（如 OpenSSL、ICU、Lua）相关宏
- 其他工程特性开关

### 4. 平台兼容性处理

- 针对 Android 平台禁用 `std::atomic`，以兼容 Boost.Asio。
- 自动设置 Windows 版本宏 `_WIN32_WINNT`。

### 5. 其他配置

- 包含工程内各类特性、容器、编译器、C++标准、字节序等配置头文件。
- 提供调试辅助宏 `YGGR_DBG_VAR_ERR()`。

---

## 用法说明

- 本文件应在所有 Yggdrasil 工程源码的最前面包含（在 `<yggr/base/yggrdef.h>` 之后）。
- 通过定义或取消定义相关宏，可灵活控制工程的编译特性和兼容性。
- 详细的宏说明可参考文件内注释。

---

## 示例

````cpp
#include <yggr/base/yggrdef.h>
#include <yggr/base/yggr_config.h>

// 根据平台自动定义 YGGR_AT_WINDOWS/YGGR_AT_LINUX 等宏
#ifdef YGGR_AT_WINDOWS
    // Windows 平台相关代码
#endif
````

---

## 注意事项

- 必须先包含 `<yggr/base/yggrdef.h>`，否则会编译报错。
- 本文件为工程全局配置核心，建议不要随意修改，若需自定义配置请在 `user_config.hpp` 中进行。

---

 

