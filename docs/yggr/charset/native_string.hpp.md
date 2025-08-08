---
# native_string.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 `native_string` 泛型工具函数，支持多种字符串类型、字符数组、指针、UTF-8 字符串等在不同类型间的**零拷贝转换**或高效转换。其核心目标是：在类型安全的前提下，将各种字符串/字符类型以“本地”方式（即无需实际数据拷贝）转换为目标类型，极大提升泛型字符串处理的灵活性和效率。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心函数**：`native_string`（多重模板重载）

---

## 主要功能

### 1. 原生字符数组与指针的类型转换

- 支持不同字符类型的数组间 reinterpret_cast 转换（如 `wchar_t[4]` 转 `char[8]`）。
- 支持同类型数组/指针的直接返回。
- 支持 `const` 和非 `const` 情况。
- 支持不同字符类型指针间 reinterpret_cast 转换（如 `const wchar_t*` 转 `const char*`）。

### 2. 标准字符串（basic_string）类型转换

- 支持 `std::basic_string`、`boost::container::basic_string` 及其同构类型间的零拷贝转换（通过 reinterpret_cast）。
- 支持同类型字符串的直接返回。
- 支持不同 allocator 的字符串类型转换。
- 若目标类型与源类型完全不同，则通过字节拷贝构造新字符串对象。

### 3. UTF-8 字符串与视图类型转换

- 支持 `utf8_char_impl`、`utf8_string_impl`、`basic_utf8_char_view`、`basic_utf8_char_reference`、`basic_utf8_char_const_reference` 等 UTF-8 类型与其底层字符串类型的高效转换。
- 支持同构类型间的 reinterpret_cast。
- 支持 allocator 传递，便于自定义内存管理。

### 4. 泛型与类型安全

- 通过 Boost.TypeTraits、SFINAE、is_convertible_char、is_basic_string_t、is_isomeric_same_string 等 traits 保证类型安全。
- 针对不同类型自动选择最优实现路径，避免不必要的数据拷贝。

---

## 设计说明

- **零拷贝优先**：只要类型兼容，优先使用 reinterpret_cast 实现零拷贝转换，极大提升效率。
- **类型安全**：大量使用 SFINAE、traits、enable_if/disable_if，防止类型误用。
- **泛型友好**：支持任意字符类型、字符串类型、allocator、UTF-8 类型等。
- **灵活性高**：支持 allocator 传递，适配自定义内存管理需求。
- **与 yggdrasil 框架深度集成**：依赖于框架的字符串类型、traits、UTF-8 类型等。

---

## 用法示例

```cpp
#include <yggr/charset/native_string.hpp>
#include <string>
#include <boost/container/string.hpp>

wchar_t ws[4] = L"Hi";
auto cs = yggr::charset::native_string<char>(ws); // reinterpret_cast 为 char[8]

std::string s = "hello";
auto& s_ref = yggr::charset::native_string(s); // 返回 std::string&

boost::container::string bs = "world";
auto& std_str = yggr::charset::native_string<std::string>(bs); // reinterpret_cast 为 std::string&

const char* cstr = "abc";
auto p = yggr::charset::native_string<const wchar_t>(cstr); // reinterpret_cast 为 const wchar_t*
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型，请确保其满足相关 traits 的特化条件。详细用法和扩展方式请查阅源码与注释。

