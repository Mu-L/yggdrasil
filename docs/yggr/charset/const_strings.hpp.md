---
# const_strings.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了跨多字符类型（char、wchar_t、char8_t、char16_t、char32_t）定义和获取常量字符串与字符的宏工具。通过这些宏，可以方便地为不同字符类型声明和访问同名常量，极大简化多字符集代码的编写和维护。

---

## 主要内容

- **命名空间**：`yggr::charset::const_strings` 及 `yggr::charset::const_chars`
- **核心功能**：常量字符串/字符的多字符类型声明与获取宏

---

## 主要功能

### 1. 常量字符/字符串的本地声明

- `YGGR_PP_CONST_CHAR_LOCAL_DEF(__name__, __char_val__)`  
  定义一个结构体 `__name__`，为多种字符类型（char、wchar_t、char8_t、char16_t、char32_t）分别提供静态 `value` 方法，返回对应类型的常量字符。
- `YGGR_PP_CONST_STRING_LOCAL_DEF(__name__, __string__)`  
  定义一个结构体 `__name__`，为多种字符类型分别提供静态 `value` 方法，返回对应类型的常量字符串指针。

### 2. 常量字符/字符串的本地获取

- `YGGR_PP_CONST_CHAR_LOCAL_GET(__name__, __char__)`  
  获取本地结构体 `__name__` 中指定字符类型的常量字符。
- `YGGR_PP_CONST_STRING_LOCAL_GET(__name__, __char__)`  
  获取本地结构体 `__name__` 中指定字符类型的常量字符串。

### 3. 常量字符/字符串的全局声明

- `YGGR_PP_CONST_CHAR_GLOBAL_DEF(__name__, __char_val__)`  
  在 `yggr::charset::const_chars` 命名空间下全局声明常量字符结构体。
- `YGGR_PP_CONST_STRING_GLOBAL_DEF(__name__, __string__)`  
  在 `yggr::charset::const_strings` 命名空间下全局声明常量字符串结构体。

### 4. 常量字符/字符串的全局获取

- `YGGR_PP_CONST_CHAR_GLOBAL_GET(__name__, __char__)`  
  全局获取指定命名空间下结构体的常量字符。
- `YGGR_PP_CONST_STRING_GLOBAL_GET(__name__, __char__)`  
  全局获取指定命名空间下结构体的常量字符串。

---

## 设计说明

- **多字符集兼容**：自动适配 char、wchar_t、char8_t、char16_t、char32_t，便于跨平台和多编码开发。
- **宏自动生成**：通过宏展开，避免重复手写多种类型的常量定义。
- **类型安全**：通过静态类型转换，保证获取的常量类型正确。
- **灵活性高**：支持本地和全局两种声明方式，适合不同作用域需求。

---

## 用法示例

```cpp
// 定义全局常量字符串
YGGR_PP_CONST_STRING_GLOBAL_DEF(hello_str, "hello");

// 获取不同字符类型的常量字符串
const char* cstr = YGGR_PP_CONST_STRING_GLOBAL_GET(hello_str, char);
#ifndef YGGR_NO_CWCHAR
const wchar_t* wstr = YGGR_PP_CONST_STRING_GLOBAL_GET(hello_str, wchar_t);
#endif
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符类型，请参考宏定义实现方式。详细用法和扩展方式请查阅源码与注释。

