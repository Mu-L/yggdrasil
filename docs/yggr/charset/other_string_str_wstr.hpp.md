---
# other_string_str_wstr.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 `other_string_str_wstr` 类型工具，用于在模板编程中根据主字符串类型自动推导“辅助字符串类型”。它适用于 char/wchar_t 或 char/char 等多字符集环境下的字符串类型适配，便于泛型字符串处理和类型安全转换。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心模板**：`other_string_str_wstr`

---

## 主要功能

### 1. other_string_str_wstr 模板结构体

```cpp
template<typename String>
struct other_string_str_wstr : public other_string<String, char, wchar_t> {};
```
- 若未定义 `YGGR_NO_CWCHAR`，则 `other_string_str_wstr` 继承自 `other_string<String, char, wchar_t>`，即主类型为 `char` 字符串，辅助类型为 `wchar_t` 字符串。

```cpp
template<typename String>
struct other_string_str_wstr : public other_string<String, char, char> {};
```
- 若定义了 `YGGR_NO_CWCHAR`，则辅助类型退化为 `char` 字符串，即 `other_string<String, char, char>`。

### 2. 适用场景

- 用于模板代码中需要根据平台是否支持 `wchar_t` 自动适配辅助字符串类型的场景。
- 便于统一处理 char/wchar_t 字符串转换、编码适配等问题。

---

## 设计说明

- **平台兼容**：通过宏 `YGGR_NO_CWCHAR` 控制是否启用 `wchar_t`，适配不同平台和编译环境。
- **泛型友好**：继承自 `other_string`，可统一访问主类型和辅助类型，便于泛型编程。
- **类型安全**：所有类型均通过模板参数静态确定，避免运行时类型错误。

---

## 用法示例

```cpp
#include <yggr/charset/other_string_str_wstr.hpp>
#include <string>

// 获取主类型和辅助类型
typedef yggr::charset::other_string_str_wstr<std::string>::main_type main_t;
typedef yggr::charset::other_string_str_wstr<std::string>::other_type other_t;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型，请特化 `other_string` 或调整宏定义。详细用法和扩展方式请查阅源码与注释。

