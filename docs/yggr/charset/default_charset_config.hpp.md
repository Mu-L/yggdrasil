---
# default_charset_config.hpp 文档

该头文件为 yggdrasil 框架的字符集模块提供了**默认字符集名称配置**，用于在不同平台、不同字符类型下自动推导和获取字符串的默认编码名称。它为字符串编码转换、字符集适配等场景提供了统一的配置和类型工具。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心结构体**：`default_charset_config`
- **辅助类型**：`charset_name_t` 及其特化
- **宏定义**：一系列字符集名称获取和类型推导宏

---

## 主要功能

### 1. 默认字符集名称宏

- `TAG_YGGR_INNER_STRING_CHARSET_NAME()`  
  内部字符串默认编码（一般为 "utf-8"）。
- `YGGR_SYS_DEFAULT_STRING_CHARSET_NAME_CFG`  
  系统默认字符串编码（Linux/macOS 为 "utf-8"，Windows 为 "char"）。
- `YGGR_SYS_DEFAULT_WSTRING_CHARSET_NAME_CFG`  
  系统默认宽字符串编码（"wchar_t"）。
- `YGGR_SYS_DEFAULT_CHAR8_STRING_CHARSET_NAME_CFG`  
  char8_t 字符串默认编码（"utf-8"）。
- `YGGR_SYS_DEFAULT_CHAR16_STRING_CHARSET_NAME_CFG`  
  char16_t 字符串默认编码（根据字节序为 "utf-16le"、"utf-16be" 或 "utf-16"）。
- `YGGR_SYS_DEFAULT_CHAR32_STRING_CHARSET_NAME_CFG`  
  char32_t 字符串默认编码（根据字节序为 "utf-32le"、"utf-32be" 或 "utf-32"）。
- 还有对应的宏函数（如 `YGGR_SYS_DEFAULT_STRING_CHARSET_NAME()`）便于调用。

### 2. 默认字符集名称类型

- 通过 `defalut_charset_name_t<Char>` 模板，根据字符类型自动推导对应的默认字符集名称结构体，并提供静态方法 `s_charset_name()` 和 `s_str_charset_name()` 获取编码名称（`const char*` 和 `const string&`）。
- 针对不同字符类型（char、wchar_t、char8_t、char16_t、char32_t 及其数组、指针）和平台特性做了特化处理。

### 3. default_charset_config 工具结构体

- 提供静态方法获取各种字符类型的默认编码名称：
  - `get_default_string_charset_name<Char>()` 返回 `const char*`
  - `get_str_default_string_charset_name<Char>()` 返回 `const string&`
  - `get_inner_string_charset_name()` / `get_str_inner_string_charset_name()` 获取内部字符串编码
  - `get_utf8_string_charset_name()` / `get_str_utf8_string_charset_name()` 获取 UTF-8 编码名称

### 4. charset_name_t 泛型类型

- `charset_name_t<Char>` 可用于任意字符类型、字符串类型、字符串视图类型，自动推导并获取对应的默认字符集名称。
- 支持与 `const char*`、`const string&` 之间的隐式转换。
- 支持与字符串、C 字符串、其他 `charset_name_t` 实例之间的比较操作（==、!=）。

### 5. 宏工具

- `YGGR_STRING_DEFAULT_CHARSET_NAME(__char_t__)`  
  获取指定字符类型的默认编码名称（`const char*`）。
- `YGGR_STR_STRING_DEFAULT_CHARSET_NAME(__char_t__)`  
  获取指定字符类型的默认编码名称（`const string&`）。
- `YGGR_DEDUCED_DEFAULT_CHARSET_NAME(__char_t__)`  
  用于类型萃取场景下自动推导编码名称。
- `YGGR_CHARSET_MAKE_STRING(__basic_string__, __char__, __traits__, __alloc__)`  
  快速生成指定参数的字符串类型。

---

## 设计说明

- **平台兼容**：自动适配 Windows、Linux、macOS 等不同平台的默认编码。
- **类型泛化**：支持 char、wchar_t、char8_t、char16_t、char32_t 及其容器、视图类型。
- **静态推导**：所有编码名称均可在编译期通过类型推导获得，便于泛型编程。
- **安全高效**：所有类型均不可拷贝/移动，防止误用；编码名称为静态常量，避免重复构造。

---

## 用法示例

```cpp
#include <yggr/charset/default_charset_config.hpp>
#include <string>

const char* charset = YGGR_STRING_DEFAULT_CHARSET_NAME(char); // "utf-8" 或 "char"
const char* wcharset = YGGR_STRING_DEFAULT_CHARSET_NAME(wchar_t); // "wchar_t"、"utf-16le"等

// 泛型获取
std::string s;
const char* s_charset = yggr::charset::charset_name_t<std::string>();

// 比较
if (yggr::charset::charset_name_t<char>() == "utf-8") {
    // ...
}
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符类型或平台，请参考模板和宏定义实现方式。详细用法和扩展方式请查阅源码与注释。

