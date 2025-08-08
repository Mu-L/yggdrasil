---
# string_decl.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了**字符串类型声明与适配**，统一了标准字符串（STL）与 Boost.Container 字符串的类型定义。通过宏控制，可灵活切换使用 STL 或 Boost 字符串类型，并为多字符类型（char、wchar_t、char8_t、char16_t、char32_t）提供统一的字符串类型别名，便于跨平台、多编码环境下的泛型编程。

---

## 主要内容

- **命名空间**：`yggr::charset`、yggr
- **核心类型**：
  - `basic_string`
  - `string`
  - `wstring`
  - `u8string`
  - `u16string`
  - `u32string`
- **宏控制**：
  - `YGGR_USE_BOOST_STRING`：优先使用 Boost.Container 字符串
  - `YGGR_USE_STL_STRING`：优先使用 STL 字符串
  - `YGGR_NO_CWCHAR`、`YGGR_NO_CHAR8_T`、`YGGR_NO_CHAR16_T`、`YGGR_NO_CHAR32_T`：控制是否启用对应字符类型

---

## 主要功能

### 1. 字符串类型适配

- **Boost.Container 字符串**  
  若未定义 `YGGR_USE_STL_STRING`，则默认使用 Boost.Container 的 `basic_string`、`string`、`wstring`、`u8string`、`u16string`、`u32string`。
- **STL 字符串**  
  若定义了 `YGGR_USE_STL_STRING`，则使用标准库的 `std::basic_string`、`std::string`、`std::wstring`、`std::u8string`、`std::u16string`、`std::u32string`。
- **类型别名**  
  在 `yggr::charset` 命名空间下定义统一的字符串类型别名，并在 yggr 命名空间下导出，便于全局使用。

### 2. 多字符类型支持

- 通过条件编译，自动适配是否支持 `wchar_t`、`char8_t`、`char16_t`、`char32_t`，并为每种类型提供对应的字符串类型别名。

### 3. 兼容性与扩展性

- 支持 Boost 及 STL 字符串类型的无缝切换，便于根据项目需求灵活选择。
- 通过宏控制，适配不同平台和编译器对字符类型的支持。

---

## 用法示例

```cpp
#include <yggr/charset/string_decl.hpp>

yggr::string s = "hello";
yggr::charset::wstring ws = L"世界";
yggr::u16string u16s = u"你好";
```

---

## 设计说明

- **统一接口**：无论底层使用 STL 还是 Boost，外部代码均可通过 `yggr::string`、`yggr::charset::string` 等统一类型名访问字符串类型。
- **类型安全**：通过条件编译和类型别名，保证类型一致性和安全性。
- **跨平台支持**：自动适配不同平台和编译器对多字符类型的支持。

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型或字符类型，请调整宏定义或类型别名。详细用法和扩展方式请查阅源码与注释。

