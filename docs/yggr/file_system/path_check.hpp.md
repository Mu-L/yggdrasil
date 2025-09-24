---
path_check.hpp 文档

---

# 文件：path_check.hpp

## 简介
该头文件为路径合法性检查、路径字符串处理等功能提供支持。集成了多种字符集、正则表达式、迭代器、容器等工具，便于对文件系统路径进行格式校验、编码转换和相关操作。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发

## 主要内容

- 头文件保护宏：`__YGGR_FILE_SYSTEM_FILE_CHECK_HPP__`
- 依赖头文件：
  - `<yggr/base/yggrdef.h>`
  - `<yggr/move/move.hpp>`
  - `<yggr/nonable/noncreateable.hpp>`
  - `<yggr/iterator_ex/is_reverse_iterator.hpp>`
  - `<yggr/iterator_ex/iterator.hpp>`
  - `<yggr/container_ex/allocator_t.hpp>`
  - `<yggr/container_ex/is_allocator.hpp>`
  - `<yggr/container/clear.hpp>`
  - `<yggr/container/reserve.hpp>`
  - `<yggr/tuple/tuple.hpp>`
  - `<yggr/charset/const_strings.hpp>`
  - `<yggr/charset/utf8_string.hpp>`
  - `<yggr/charset/utf8_string_view.hpp>`
  - `<yggr/regular_parse/regex_parse.hpp>`
  - `<yggr/regular_parse/u32regex_parse.hpp>`
  - `<boost/utility/enable_if.hpp>`
  - `<boost/range/functions.hpp>`
  - `<boost/type_traits/is_base_of.hpp>`
  - 以及标准库头文件 `<utility>`, `<algorithm>`, `<cassert>`
- 主要用于路径字符串的合法性校验、正则解析、字符集转换等操作，支持多种容器和迭代器类型。

## 适用场景
适用于需要对文件路径进行格式校验、字符集处理、正则解析等复杂操作的 C++ 项目，提升路径处理的健壮性和灵活性。

---

如需更详细的类与函数说明，请告知或指定需要详细说明的部分。

alucard-dracula: 详细说明下 该文件中的 class 和 struct

path_object_maker.hpp 文档

---

# 文件：path_object_maker.hpp

## 简介
该头文件定义了 `path_object_maker` 类，用于统一和简化路径对象的创建。该类继承自 `path_check`，集成了路径合法性校验、类型萃取、迭代器适配等功能，便于从多种输入类型（如字符串、迭代器区间等）高效构造本地文件系统路径对象。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发

## 主要内容

- 头文件保护宏：`__YGGR_FILE_SYSTEM_PATH_OBJECT_MAKER_HPP__`
- 依赖头文件：
  - `<yggr/base/yggrdef.h>`
  - `<yggr/type_traits/remove_cv_ref.hpp>`
  - `<yggr/iterator_ex/is_iterator.hpp>`
  - `<yggr/iterator_ex/is_reverse_iterator.hpp>`
  - `<yggr/iterator_ex/is_const_iterator.hpp>`
  - `<yggr/file_system/path_check.hpp>`
  - `<yggr/file_system/local_fsys_native_operators.hpp>`
- 命名空间：`yggr::file_system`
- 类定义：`class path_object_maker : public path_check`
  - 继承自 `path_check`，具备路径校验能力
  - 类型定义：
    - `path_type`：本地文件系统路径类型
    - `path_char_type`：路径字符类型
    - `path_string_type`：路径字符串类型
    - `error_code_type`、`exception_type`：错误码和异常类型
  - 主要用于多种输入类型到路径对象的安全、统一转换

## 适用场景
适用于需要从多种数据源（如字符串、迭代器、区间等）构造本地文件系统路径对象，并要求路径合法性校验和类型安全的 C++ 项目。

---



