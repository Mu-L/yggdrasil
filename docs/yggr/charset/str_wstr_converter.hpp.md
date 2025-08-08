---
# str_wstr_converter.hpp 文档

该头文件定义了 yggdrasil 框架字符集模块中的 `str_wstr_converter` 工具类，专用于**字符串与宽字符串（char/wchar_t）之间的编码转换**。它支持多种字符串类型和字符类型，自动适配编码名称，便于在多字符集环境下进行高效、安全的字符串互转。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`str_wstr_converter`（不可实例化，仅提供静态方法）

---

## 主要功能

### 1. 字符串与宽字符串互转

#### 1.1 C 风格字符串转换

```cpp
template<typename Char>
static basic_string<typename other_char_chr_wchr<Char>::type>
s_conv(const Char* src,
       const string& src_charset_name = charset_name_t<Char>(),
       const string& dst_charset_name = charset_name_t<typename other_char_chr_wchr<Char>::type>());
```
- **功能**：将 C 风格字符串 `src` 从 `src_charset_name` 编码转换为另一种字符类型（如 char <-> wchar_t）的字符串，目标编码为 `dst_charset_name`。
- **适用类型**：char、wchar_t、char8_t、char16_t、char32_t 等。

#### 1.2 C 风格字符串（带长度）转换

```cpp
template<typename Char>
static basic_string<typename other_char_chr_wchr<Char>::type>
s_conv(const Char* src, size_type n,
       const string& src_charset_name = charset_name_t<Char>(),
       const string& dst_charset_name = charset_name_t<typename other_char_chr_wchr<Char>::type>());
```
- **功能**：同上，但支持指定长度 n，适合非 0 结尾字符串。

#### 1.3 标准字符串类型转换

```cpp
template<typename Char, typename Traits, typename Alloc,
         template< typename _Char, typename _Traits, typename _Alloc > class Basic_String>
static typename other_string_str_wstr< Basic_String<Char, Traits, Alloc> >::type
s_conv(const Basic_String<Char, Traits, Alloc>& src,
       const string& src_charset_name = charset_name_t<Char>(),
       const string& dst_charset_name = charset_name_t<typename other_char_chr_wchr<Char>::type>());
```
- **功能**：将任意标准字符串类型（如 `std::basic_string`、`boost::container::basic_string`）从一种字符类型转换为另一种（如 char <-> wchar_t），并自动适配编码名称。

---

## 设计说明

- **类型安全**：通过 SFINAE 和 traits 保证只对原生字符类型和标准字符串类型开放接口。
- **自动编码适配**：默认自动推导源/目标编码名称，支持自定义编码。
- **高效实现**：底层调用 `charset_foo::s_xchg`，自动选择最优转换路径。
- **不可实例化**：继承自 `nonable::noncreateable`，仅能静态调用。

---

## 用法示例

```cpp
#include <yggr/charset/str_wstr_converter.hpp>
#include <string>

std::string s = "你好";
std::wstring ws = yggr::charset::str_wstr_converter::s_conv(s); // UTF-8 -> UTF-16/32

const wchar_t* wsrc = L"世界";
std::string s2 = yggr::charset::str_wstr_converter::s_conv(wsrc); // UTF-16/32 -> UTF-8
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型或编码，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

