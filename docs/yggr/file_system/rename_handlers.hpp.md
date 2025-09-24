---
rename_handlers.hpp 文档

---

# 文件：rename_handlers.hpp

## 简介
该头文件定义了多种文件重命名处理器，包括扩展名追加、计数递增、空操作等策略。通过结构体和模板，支持灵活定制文件重命名行为，便于在文件系统操作中实现自动备份、冲突规避等功能。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发

## 主要内容

- 头文件保护宏：`__YGGR_FILE_SYSTEM_RENAME_HANDLERS_HPP__`
- 依赖头文件：
  - `<yggr/base/yggrdef.h>`
  - `<yggr/charset/const_strings.hpp>`
  - `<yggr/container/reserve.hpp>`
  - `<yggr/file_system/path_check.hpp>`
  - `<yggr/file_system/detail/path_opt.hpp>`
  - `<yggr/file_system/local_fsys_native_operators.hpp>`
  - `<boost/ref.hpp>`
  - `<sstream>`
- 命名空间：`yggr::file_system`
- 主要结构体和功能：
  - `rename_ext_empty`：空扩展名处理器，不做任何扩展名追加。
  - `rename_ext_bak`：追加 ".bak" 扩展名的处理器。
  - `rename_of_count<ExtHandler>`：带计数的重命名处理器，支持在文件名后自动追加计数（如 file(1).bak）。
  - 其他可扩展的重命名策略。
- 这些处理器可作为模板参数，灵活应用于文件系统的重命名、备份、冲突处理等场景。

## 适用场景
适用于需要自定义文件重命名策略、自动备份、避免文件名冲突等需求的 C++ 项目，提升文件操作的安全性和灵活性。

---



