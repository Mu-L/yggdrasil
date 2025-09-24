---
recursive_handlers.hpp 文档

---

# 文件：recursive_handlers.hpp

## 简介
该头文件定义了递归文件操作（如递归复制、递归移动等）过程中的空通知处理器。通过结构体 `recursive_copy_empty_notifier` 及其类型别名，为递归操作提供默认的“无操作”通知实现，便于扩展和自定义递归操作的回调行为。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发

## 主要内容

- 头文件保护宏：`__YGGR_FILE_SYSTEM_RECURSIVE_HANDLERS_HPP__`
- 依赖头文件：
  - `<yggr/base/yggrdef.h>`
  - `<yggr/file_system/local_fsys_native_operators.hpp>`
  - `<sstream>`
- 命名空间：`yggr::file_system`
- 结构体定义：
  - `struct recursive_copy_empty_notifier`
    - 递归复制操作的空通知器，`operator()` 为无操作实现，参数包括源路径、目标路径、当前处理路径、结果、计数、错误码、是否可继续等。
  - 类型别名：
    - `typedef recursive_copy_empty_notifier recursive_move_empty_notifier;`
    - `typedef recursive_copy_empty_notifier recursive_remove_empty_notifier;`
    - 递归移动和递归删除操作同样采用空通知器。

## 适用场景
适用于需要递归文件操作但暂不需要通知回调，或作为自定义通知器的基类和默认实现，便于后续扩展递归操作的回调逻辑。

---



