---
# utf8_char.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 UTF-8 单字符类型 `utf8_char` 的类型定义及相关泛型类型推导宏。它统一了 UTF-8 字符的类型接口，便于在泛型编程、模板推导、类型安全转换等场景下高效处理 UTF-8 单字符。

---

## 主要内容

- **命名空间**：`yggr::charset`、yggr
- **核心类型**：`utf8_char_impl<>` 的类型别名 `utf8_char`
- **类型推导工具**：`utf8_char_t_getter` 模板结构体
- **类型推导宏**：多组宏定义，便于自动推导 UTF-8 字符类型

---

## 主要功能

### 1. utf8_char 类型别名

```cpp
typedef utf8_char_impl<> utf8_char;
```
- **功能**：将默认模板参数的 `utf8_char_impl` 作为 UTF-8 单字符类型，便于直接使用。
- **适用场景**：需要高效、类型安全地处理 UTF-8 单字符的场合。

### 2. utf8_char_t_getter 泛型类型推导

```cpp
template<typename Char, typename Utf8_Char>
struct utf8_char_t_getter : public mplex::get_reference_if_same<Char, Utf8_Char> { ... };
```
- **功能**：根据输入类型 `Char` 和目标 UTF-8 字符类型 `Utf8_Char`，自动推导出合适的类型（引用或对象）。
- **特化**：对 `string_charset_helper` 类型做了专门适配，保证泛型场景下类型推导正确。
- **类型安全**：通过 `BOOST_MPL_ASSERT` 静态断言，保证 `Utf8_Char` 必须为 UTF-8 字符类型。

### 3. 类型推导宏

- **常用宏**：
  - `YGGR_TYPEDEF_UTF8_CHAR_TYPE(__char_t__, __utf8_char_t_name__)`
  - `YGGR_TYPEDEF_CONST_UTF8_CHAR_TYPE(__char_t__, __utf8_char_t_name__)`
  - `YGGR_TYPEDEF_UTF8_CHAR_TYPE_TPL(__char_t__, __utf8_char_t_name__)`
  - `YGGR_TYPEDEF_CONST_UTF8_CHAR_TYPE_TPL(__char_t__, __utf8_char_t_name__)`
- **自定义 UTF-8 字符类型宏**：
  - `YGGR_TYPEDEF_CUSTOM_UTF8_CHAR_TYPE(__char_t__, __cmp_utf8_char_t__, __utf8_char_t_name__)`
  - `YGGR_TYPEDEF_CUSTOM_CONST_UTF8_CHAR_TYPE(__char_t__, __cmp_utf8_char_t__, __utf8_char_t_name__)`
  - `YGGR_TYPEDEF_CUSTOM_UTF8_CHAR_TYPE_TPL(__char_t__, __cmp_utf8_char_t__, __utf8_char_t_name__)`
  - `YGGR_TYPEDEF_CUSTOM_CONST_UTF8_CHAR_TYPE_TPL(__char_t__, __cmp_utf8_char_t__, __utf8_char_t_name__)`
- **功能**：根据输入类型和目标 UTF-8 字符类型，自动生成合适的类型别名，支持模板和非模板场景，便于泛型代码中类型适配。

---

## 设计说明

- **类型安全**：通过静态断言和类型 traits，保证类型推导的正确性和安全性。
- **泛型友好**：支持任意字符类型、UTF-8 字符类型、string_charset_helper 等复杂类型的自动推导。
- **易用性**：通过类型别名和宏，极大简化了泛型模板代码中的类型声明和适配。
- **与 yggdrasil 框架深度集成**：依赖于框架的 UTF-8 字符串、字符类型、traits 等。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_char.hpp>

// 直接使用 utf8_char
yggr::charset::utf8_char c = '你';

// 泛型推导
YGGR_TYPEDEF_UTF8_CHAR_TYPE(char, my_utf8_char_t);
my_utf8_char_t c2 = '好';

// 自定义类型推导
YGGR_TYPEDEF_CUSTOM_UTF8_CHAR_TYPE(char, yggr::charset::utf8_char_impl<wchar_t>, my_custom_utf8_char_t);
my_custom_utf8_char_t c3 = L'世';
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义 UTF-8 字符类型，请使用相关宏或特化 `utf8_char_t_getter`。详细用法和扩展方式请查阅源码与注释。

