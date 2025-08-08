---
# boost_cpp_version_check.hpp 文档

## 文件简介

boost_cpp_version_check.hpp 用于在编译期间检测 Boost 版本与 C++ 标准版本的兼容性，防止因 Boost 版本过低或 C++ 标准过高导致的编译或运行时问题。该文件会在不兼容时直接报错或给出编译警告。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<boost/config/pragma_message.hpp>`
- 必须先包含 `<yggr/base/yggrdef.h>`

---

## 主要功能

### 1. 头文件包含保护

- 若未先包含 `yggrdef.h`，则编译报错，确保类型和基础配置一致。

### 2. C++ 标准与 Boost 版本兼容性检查

- **C++17 检查**  
  - 如果当前 C++ 标准高于 C++14（即 C++17 及以上），且 Boost 版本低于 1.66.0，则编译报错：  
    “boost 1.53.0 - boost 1.65.1 not support cpp17 and later”

- **C++20 检查**  
  - 如果当前 C++ 标准高于 C++17（即 C++20 及以上），且 Boost 版本低于 1.82.0，则编译时给出警告：  
    “boost 1.66.0 - boost 1.81.0 not recommend using cpp20”

- **C++23 检查**  
  - 如果当前 C++ 标准高于 C++20（即 C++23 及以上），则直接编译报错：  
    “yggdrail has not been tested for cpp23 support”

---

## 用法说明

- 本文件会在工程编译初期自动检测 Boost 和 C++ 标准的兼容性，确保开发环境安全。
- 不建议在未通过检测的环境下继续开发或部署。

---

## 注意事项

- 必须先包含 `<yggr/base/yggrdef.h>`，否则会编译报错。
- 若需支持更高版本的 C++ 标准，请确保 Boost 版本满足要求，并根据提示升级 Boost。
- 若遇到编译警告或错误，请根据提示调整 Boost 版本或 C++ 标准。

---

 

