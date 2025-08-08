---
# generalized_string.hpp 文档

该头文件为 yggdrasil 框架的字符集模块提供了**广义字符串类型**的判空工具。它支持多种字符串类型（包括标准字符串、字符串视图、容器、C 风格指针等），通过统一接口判断“字符串”是否为空，极大方便了泛型编程和通用字符串处理。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心函数**：`generalized_string_empty`
- **内部实现**：`detail::is_generalized_string_t_empty_helper` 模板结构体

---

## 主要功能

### 1. generalized_string_empty

```cpp
template<typename String>
bool generalized_string_empty(const String& str);
```

- **功能**：判断任意广义字符串类型是否为空。
- **类型要求**：`String` 必须满足 `is_generalized_string_t<String>::value == true`（即被视为广义字符串类型）。
- **实现机制**：根据类型特性自动选择合适的判空方式。

### 2. 判空策略（内部实现）

- **字符串视图类型**（如 `std::string_view`、`yggr::utf8_string_view` 等）  
  直接调用 `str.empty()`。
- **容器类型**（如 `std::vector<char>`、`std::basic_string` 等）  
  调用 `yggr::container::empty(str)`，兼容 STL 和自定义容器。
- **指针类型**（如 `const char*`、`const wchar_t*`）  
  判定为 null 或首字符为 0 时为空。

---

## 设计说明

- **高度泛型**：支持字符串、字符串视图、容器、C 风格指针等多种类型。
- **类型安全**：通过 SFINAE 和 traits 保证只有广义字符串类型可用。
- **统一接口**：无论输入类型如何，均可用 `generalized_string_empty` 判断是否为空。
- **内部实现灵活**：通过模板特化自动分派到最优判空方式。

---

## 用法示例

```cpp
#include <yggr/charset/generalized_string.hpp>
#include <string>
#include <vector>

std::string s1 = "";
std::vector<char> s2;
const char* s3 = nullptr;
const char* s4 = "";

bool b1 = yggr::charset::generalized_string_empty(s1); // true
bool b2 = yggr::charset::generalized_string_empty(s2); // true
bool b3 = yggr::charset::generalized_string_empty(s3); // true
bool b4 = yggr::charset::generalized_string_empty(s4); // true
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型，请确保其满足 `is_generalized_string_t` 的特化条件。详细用法和扩展方式请查阅源码与注释。

