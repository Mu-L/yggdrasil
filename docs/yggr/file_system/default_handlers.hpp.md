---
default_handlers.hpp 文档

---

# 文件：default_handlers.hpp

## 简介
该头文件定义了文件系统操作的默认处理器类型，包括重命名、递归复制、递归移动和递归删除等操作的处理器。通过模板和类型别名，便于在文件系统相关功能中统一和扩展各种操作的处理逻辑。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发

## 主要内容

- 头文件保护宏：`__YGGR_FILE_SYSTEM_DEFAULT_HANDLERS_HPP__`
- 依赖头文件：
  - `<yggr/base/yggrdef.h>`
  - `<yggr/file_system/rename_handlers.hpp>`
  - `<yggr/file_system/recursive_handlers.hpp>`
- 命名空间：`yggr::file_system`
- 模板结构体：
  ```cpp
  template<
      typename HRename, 
      typename HRecursive_Copy_Notify = recursive_copy_empty_notifier,
      typename HRecursive_Move_Notify = recursive_move_empty_notifier,
      typename HRecursive_Remove_Notify = recursive_remove_empty_notifier
  >
  struct basic_default_handlers
  {
      typedef native::path path_type;
      typedef HRename rename_handler_type;
      typedef HRecursive_Copy_Notify recursive_copy_notify_handler_type;
      typedef HRecursive_Move_Notify recursive_move_notify_handler_type;
      typedef HRecursive_Remove_Notify recursive_remove_notify_handler_type;
  };
  ```
  该结构体通过模板参数允许自定义各类文件操作的处理器类型，默认使用空通知处理器。

- 类型别名：
  ```cpp
  typedef basic_default_handlers< rename_of_count<rename_ext_bak> > default_handlers;
  ```
  该类型为项目提供了默认的文件操作处理器集合。

## 适用场景
适用于需要自定义或统一管理文件系统操作处理器的 C++ 项目，便于扩展和维护文件操作相关逻辑。

---



