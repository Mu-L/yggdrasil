# utf8_string_impl.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件实现了 Yggdrasil 框架下 UTF-8 字符串的核心类型 `utf8_string_impl`，支持多种字符类型、traits、分配器，兼容 STL/Boost 字符串接口，并扩展了丰富的 UTF-8 专用操作。支持与标准字符串、视图、字符类型、辅助类型的高效互操作，适合多语言、跨平台、高性能文本处理场景。

## 3. 主要类型与功能

### 3.1 utf8_string_impl
- **模板参数**：`Char` 字符类型，`Traits` 字符特性，`Alloc` 分配器。
- **主要成员**：
  - `_base`：底层存储，通常为 `std::string` 或兼容类型。
  - `_utf8_size`：逻辑 UTF-8 字符长度。
- **主要功能**：
  - 构造、赋值、拷贝、移动、swap。
  - 兼容 STL/Boost 字符串的接口（如 `data()`、`c_str()`、`get_allocator()`）。
  - 支持多种构造和赋值方式，包括从字符、字符串、视图、辅助类型等构造。
  - 支持 append、assign、insert、replace 等批量操作。
  - 支持 find、rfind、find_first_of、find_first_not_of、find_last_of、find_last_not_of 等查找操作，支持多种参数类型。
  - 支持 substr、compare、compare_eq、starts_with、ends_with、contains 等高级文本操作。
  - 支持 org_str、str 等底层数据访问与转换。
  - 支持 hash、affix_length、recount_length 等辅助功能。
  - 支持与标准字符串、视图、辅助类型的高效互操作和类型转换。

### 3.2 相关工具与特性
- **类型萃取与 traits**：支持 is_utf8_string_impl、is_utf8_string_t、is_basic_string_t、is_string_view_t 等类型判断。
- **swap 支持**：提供 swap 重载，支持与标准字符串、utf8_string_impl、辅助类型的高效交换，并导入 std/boost 命名空间。
- **流操作符**：重载 `<<`、`>>`，支持与标准流的输入输出。
- **getline 支持**：多重重载，支持多种分隔符和字符串类型的 getline 操作。
- **比较操作符**：重载 `==`、`!=`、`<`、`<=`、`>`、`>=`，支持与多种类型的比较。
- **加法操作符**：重载 `+`，支持与字符、字符串、视图、辅助类型的拼接。
- **字节数支持**：集成到 bytes 模块，支持 byte_size 计算。
- **适配器与辅助函数**：如 org_str、affix_length、recount_length、string_charset_helper_data 等。

### 3.3 构造与类型适配
- 支持从多种类型（如 char*、wchar_t*、std::string、string_view、utf8_char_impl、string_charset_helper 等）构造和赋值。
- 通过类型萃取和 SFINAE 技术自动适配参数类型，保证类型安全和高效。

### 3.4 兼容性与扩展性
- 兼容 C++98/03/11/17/20，支持右值引用、Boost.Move。
- 支持自定义 traits、分配器，适应不同平台和需求。
- 通过宏和模板元编程自动适配多种用法。

---

## 4. 典型用法

```cpp
#include <yggr/charset/utf8_string_impl.hpp>

yggr::charset::utf8_string_impl<char> s1("你好，世界");
yggr::charset::utf8_string_impl<char> s2 = s1.substr(0, 2);
bool found = s1.contains("世界");
s1.append("!");
std::cout << s1 << std::endl;

if (s1.starts_with("你")) { /* ... */ }
if (s1.ends_with("!")) { /* ... */ }
auto pos = s1.find("世界");
auto sub = s1.substr(pos, 2);
```

---

## 5. 设计要点

- **高性能**：底层直接操作字节数组，逻辑长度与字节长度分离，适合高效 UTF-8 处理。
- **类型安全**：通过 enable_if、类型萃取、断言等保证接口类型安全。
- **接口丰富**：兼容 STL/Boost 字符串接口，扩展 UTF-8 专用操作。
- **泛型友好**：支持多种类型参数，适合泛型编程和模板库集成。
- **跨平台**：兼容多种编译器和标准，适合多平台开发。

---

## 6. 注意事项

- `_utf8_size` 仅在部分操作后自动维护，直接操作底层数据后需手动调用 `recount_length()`。
- 字符串操作涉及编码转换时需确保 charset_name 参数正确。
- 复杂操作建议优先使用接口提供的安全方法，避免直接操作底层数据。

---

## 7. 总结

本文件为 Yggdrasil 框架提供了功能强大、类型安全、接口丰富的 UTF-8 字符串实现，适合多语言、跨平台、高性能文本处理场景。其设计兼顾性能、易用性和扩展性，是大型 C++ 项目中 UTF-8 字符串处理的理想选择。

---

