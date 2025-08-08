---
# other_string.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了**字符串类型自动推导工具**，用于在模板编程中根据主字符串类型和两个候选字符类型，自动推导“辅助字符串类型”。它支持标准字符串、traits、allocator 及相关对象的泛型适配，适用于 char/wchar_t、char/char16_t 等多字符集环境下的字符串类型自动切换。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心模板**：
  - `other_char_traits`
  - `other_char_allocator`
  - `other_char_tpl_arg_allocator`
  - `other_char_object`
  - `other_string`

---

## 主要功能

### 1. other_char_traits

- **功能**：根据主 traits 类型和两个候选字符类型，自动推导“辅助字符类型”的 traits。
- **用法**：
  ```cpp
  typedef other_char_traits<std::char_traits<char>, char, wchar_t>::type wtraits_t; // std::char_traits<wchar_t>
  ```

### 2. other_char_allocator

- **功能**：根据主 allocator 类型和两个候选字符类型，自动推导“辅助字符类型”的 allocator。
- **用法**：
  ```cpp
  typedef other_char_allocator<std::allocator<char>, char, wchar_t>::type walloc_t; // std::allocator<wchar_t>
  ```

### 3. other_char_tpl_arg_allocator

- **功能**：根据模板参数 allocator 类型和两个候选字符类型，自动推导“辅助字符类型”的 allocator，支持 void 特化。
- **用法**：
  ```cpp
  typedef other_char_tpl_arg_allocator<void, char, wchar_t>::type void_t; // void
  ```

### 4. other_char_object

- **功能**：根据主对象类型（如 traits、allocator、其他模板对象）和两个候选字符类型，自动推导“辅助字符类型”的对象类型。
- **用法**：
  ```cpp
  typedef other_char_object<MyObject<char>, char, wchar_t>::type MyObject<wchar_t>;
  ```

### 5. other_string

- **功能**：根据主字符串类型（如 `std::basic_string<char, Traits, Alloc>`）和两个候选字符类型，自动推导“辅助字符类型”的字符串类型（如 `std::basic_string<wchar_t, Traits, Alloc>`）。
- **用法**：
  ```cpp
  typedef other_string<std::basic_string<char>, char, wchar_t>::type wstring_t; // std::basic_string<wchar_t>
  ```

---

## 设计说明

- **类型自动推导**：通过模板参数和类型 traits，自动推导与主类型“同构”的辅助类型，适合泛型字符串处理和多字符集适配。
- **类型安全**：所有模板参数均通过 `YGGR_ASSERT_CHAR_TYPE` 静态断言，防止非字符类型误用。
- **灵活扩展**：支持 traits、allocator、对象、字符串等多种类型的自动推导，便于扩展和自定义。

---

## 用法示例

```cpp
#include <yggr/charset/other_string.hpp>
#include <string>

// 推导 wchar_t 版本的 string
typedef yggr::charset::other_string<std::string, char, wchar_t>::type wstring_t; // std::wstring

// 推导 char 版本的 wstring
typedef yggr::charset::other_string<std::wstring, char, wchar_t>::type string_t; // std::string

// 推导辅助 allocator
typedef yggr::charset::other_char_allocator<std::allocator<char>, char, wchar_t>::type walloc_t; // std::allocator<wchar_t>
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型、traits 或 allocator，请确保其模板参数结构与上述标准一致。详细用法和扩展方式请查阅源码与注释。

