---
file_system_c_str.hpp 文档

---

# 文件：file_system_c_str.hpp

## 简介
该头文件用于兼容不同版本 Boost.Filesystem 的 `c_str` 路径字符串获取方式。通过宏定义 `YGGR_FILESYSTEM_C_STR`，屏蔽了 Boost 版本差异，方便跨版本获取文件路径的 C 字符串表示。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发

## 主要内容

- 头文件保护宏：`__YGGR_FILE_SYSTEM_FILE_SYSTEM_C_STR_HPP__`
- 依赖头文件：
  - `<yggr/base/yggrdef.h>`
  - `<boost/version.hpp>`
  - `<boost/filesystem/fstream.hpp>`
- 宏定义：
  - `YGGR_FILESYSTEM_C_STR(__var_path__)`  
    根据 Boost 版本，自动选择合适的 `c_str` 获取方式：
    - Boost 1.77.0 之前：`__var_path__.BOOST_FILESYSTEM_C_STR`
    - Boost 1.77.0 及之后：`BOOST_FILESYSTEM_C_STR(__var_path__)`
- 命名空间：`yggr::file_system`（当前为空）

## 适用场景
适用于需要兼容不同 Boost.Filesystem 版本、统一获取路径 C 字符串的 C++ 项目，避免因 Boost 升级导致的接口不兼容问题。

---



