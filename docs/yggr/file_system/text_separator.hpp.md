---
text_separator.hpp 文档

---

# 文件：text_separator.hpp

## 简介
该头文件定义了文本分隔器相关的工具和元类型，主要用于文本分割、分隔符处理等场景。通过结构体、模板元编程和类型萃取，支持灵活的分隔符定义和文本处理，便于在文件系统或文本处理模块中实现高效、类型安全的分割操作。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发

## 主要内容

- 头文件保护宏：`__YGGR_FILE_SYSTEM_TEXT_SEPARATOR_HPP__`
- 依赖头文件：
  - `<yggr/base/yggrdef.h>`
  - `<yggr/charset/const_strings.hpp>`
  - `<yggr/charset/string.hpp>`
  - `<yggr/ppex/symbols.hpp>`
  - `<yggr/container/clear.hpp>`
  - `<yggr/type_traits/native_t.hpp>`
  - Boost MPL、类型萃取相关头文件
  - `<iostream>`
- 命名空间：`yggr::file_system`
- 主要结构体和功能：
  - `tag_text_separator`：文本分隔器的元标签类型
  - `detail` 命名空间下包含具体实现细节
  - 支持多种分隔符、分割策略和类型萃取，便于扩展和自定义文本分割行为

## 适用场景
适用于需要自定义文本分隔符、进行高效文本分割和类型安全处理的 C++ 项目，常用于配置解析、日志处理、数据导入导出等场景。

---

