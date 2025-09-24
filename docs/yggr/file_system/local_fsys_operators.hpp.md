---
local_fsys_operators.hpp 文档

---

# 文件：local_fsys_operators.hpp

## 简介
该头文件为本地文件系统操作提供统一的操作类型定义。通过类型别名 `local_fsys_operators`，将底层的 Boost 文件流配置与本地文件系统基础操作器结合，便于在项目中直接使用高层次的本地文件系统操作接口。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发

## 主要内容

- 头文件保护宏：`__YGGR_FILE_SYSTEM_LOCAL_FSYS_OPERATORS_HPP__`
- 依赖头文件：
  - `<yggr/base/yggrdef.h>`
  - `<yggr/file_system/boost_fstream_config.hpp>`
  - `<yggr/file_system/stl_fstream_config.hpp>`
  - `<yggr/file_system/local_fsys_basic_operators.hpp>`
- 命名空间：`yggr::file_system`
- 类型别名：
  ```cpp
  typedef local_fsys_basic_operators<boost_fstream_config_type> local_fsys_operators;
  ```
  该类型将 Boost 文件流配置作为模板参数，生成本地文件系统操作器，便于直接调用本地文件系统相关操作。

## 适用场景
适用于需要统一、便捷地进行本地文件系统操作的 C++ 项目，屏蔽底层实现细节，提升开发效率。

---



