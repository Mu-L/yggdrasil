---
# string_byte_size.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了**字符串字节长度计算工具**，支持多种字符串类型（包括 C 风格字符串、标准字符串、字符串视图、boost 字符串等）和多种字符类型（char、wchar_t、char8_t、char16_t、char32_t）。它可用于高效、类型安全地计算字符串实际占用的字节数，适合序列化、内存分配、网络传输等场景。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心函数**：
  - `string_byte_size`：计算字符串内容的字节数（不含结尾 0）
  - `char_buffer_byte_size`：计算字符串缓冲区所需字节数（含结尾 0）
- **内部实现**：通过 detail 命名空间下的辅助模板结构体实现类型分派

---

## 主要功能

### 1. string_byte_size

- **功能**：计算字符串内容的实际字节数（不包含结尾 0）。
- **支持类型**：
  - C 风格字符串指针（如 `const char*`、`const wchar_t*` 等）
  - 字符数组（如 `char[N]`、`wchar_t[N]` 等）
  - 标准字符串类型（如 `std::basic_string`、`boost::container::basic_string` 等）
  - 字符串视图类型（如 `std::basic_string_view` 等）
- **实现机制**：根据类型自动选择合适的长度计算方式，并乘以字符类型的字节数。

#### 示例

```cpp
std::string s = "abc";
size_t n = yggr::charset::string_byte_size(s); // n == 3

const wchar_t* ws = L"你好";
size_t wn = yggr::charset::string_byte_size(ws); // wn == 2 * sizeof(wchar_t)
```

### 2. char_buffer_byte_size

- **功能**：计算字符串缓冲区所需的总字节数（包含结尾 0）。
- **支持类型**：同上。
- **实现机制**：在内容字节数基础上加上一个字符类型的字节数。

#### 示例

```cpp
std::string s = "abc";
size_t n = yggr::charset::char_buffer_byte_size(s); // n == 4

const wchar_t* ws = L"你好";
size_t wn = yggr::charset::char_buffer_byte_size(ws); // wn == (2 + 1) * sizeof(wchar_t)
```

---

## 设计说明

- **类型泛化**：通过模板和 SFINAE，支持多种字符串/字符类型，自动分派到最优实现。
- **类型安全**：所有类型均通过 `YGGR_ASSERT_CHAR_TYPE` 静态断言，防止非字符类型误用。
- **高效实现**：底层直接调用 `std::strlen`、`std::wcslen`、`std::char_traits::length` 等，无额外开销。
- **可扩展性**：便于扩展支持自定义字符串类型和字符类型。

---

## 用法示例

```cpp
#include <yggr/charset/string_byte_size.hpp>
#include <string>
#include <vector>

std::string s = "hello";
size_t bytes = yggr::charset::string_byte_size(s); // 5

wchar_t ws[] = L"世界";
size_t wbytes = yggr::charset::char_buffer_byte_size(ws); // (2+1)*sizeof(wchar_t)
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型，请确保其满足相关 traits 的特化条件。详细用法和扩展方式请查阅源码与注释。

