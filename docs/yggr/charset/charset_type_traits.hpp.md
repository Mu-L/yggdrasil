---
# charset_type_traits.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了丰富的类型萃取（Type Traits）工具，主要用于判断和区分各种字符串类型、字符串视图类型、UTF-8 相关类型、通用字符串容器类型及其迭代器类型。通过这些 traits，可以在模板编程中实现类型安全、自动分派和高效的泛型字符串处理。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心内容**：类型萃取模板结构体（Type Traits）

---

## 主要功能

### 1. 字符类型与字符串类型判断

- **is_utf8_char_t<T>**  
  判断类型 T 是否为 UTF-8 字符类型（默认 false，可特化）。
- **is_basic_string_t<T>**  
  判断类型 T 是否为 `std::basic_string` 或 `boost::container::basic_string`。
- **is_basic_string_view_t<T>**  
  判断类型 T 是否为 `std::basic_string_view`（C++17 及以上）。
- **is_utf8_string_t<T>**  
  判断类型 T 是否为 UTF-8 字符串类型（默认 false，可特化）。
- **is_string_t<T>**  
  判断类型 T 是否为标准字符串类型（basic_string 或 utf8_string）。
- **is_string_view_t<T>**  
  判断类型 T 是否为字符串视图类型（basic_string_view 或 utf8_string_view）。
- **is_generalized_string_t<T>**  
  判断类型 T 是否为广义字符串类型（包括字符串容器、指针等，元素为 integral 类型）。

### 2. 字符串视图类型判断

- **is_same_basic_string_view_tpl<T1, T2>**  
  判断 T1 和 T2 是否为相同模板的 basic_string_view。
- **is_difference_basic_string_view_tpl<T1, T2>**  
  判断 T1 和 T2 是否为不同模板的 basic_string_view。

### 3. 迭代器类型判断

- **is_utf8_string_iterator_t<T>**  
  判断 T 是否为 UTF-8 字符串的普通迭代器。
- **is_utf8_string_reverse_iterator_t<T>**  
  判断 T 是否为 UTF-8 字符串的反向迭代器。
- **is_utf8_string_const_iterator_t<T>**  
  判断 T 是否为 UTF-8 字符串的常量迭代器。
- **is_utf8_string_const_reverse_iterator_t<T>**  
  判断 T 是否为 UTF-8 字符串的常量反向迭代器。
- **is_utf8_string_modify_iterator_t<T>**  
  判断 T 是否为 UTF-8 字符串的可修改迭代器。
- **is_utf8_string_modify_reverse_iterator_t<T>**  
  判断 T 是否为 UTF-8 字符串的可修改反向迭代器。
- **is_any_utf8_string_iterator_t<T>**  
  判断 T 是否为任意 UTF-8 字符串相关迭代器（普通、反向、常量、可修改）。
- **is_any_utf8_string_reverse_iterator_t<T>**  
  判断 T 是否为任意 UTF-8 字符串相关反向迭代器。

### 4. 反向判断（not_xxx）

每个类型萃取都提供了对应的反向判断（如 `is_not_utf8_char_t<T>`），便于模板编程中的条件分支。

---

## 设计说明

- **高度泛型**：通过模板和 Boost MPL，支持任意自定义字符串类型和容器类型的扩展。
- **可特化**：默认实现均为 false_，实际项目中可针对自定义类型进行特化。
- **与 STL/Boost 深度集成**：自动识别 STL、Boost 字符串及视图类型。
- **支持 C++17 string_view**：自动适配 `std::basic_string_view`。
- **广义字符串支持**：不仅支持标准字符串，还支持元素为 integral 的容器和指针。

---

## 用法示例

```cpp
#include <yggr/charset/charset_type_traits.hpp>
#include <string>
#include <vector>

static_assert(yggr::charset::is_basic_string_t<std::string>::value, "std::string 应为 basic_string");
static_assert(yggr::charset::is_generalized_string_t<std::vector<char>>::value, "vector<char> 也被视为广义字符串");
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型，请特化对应的 traits 结构体。详细用法和扩展方式请查阅源码实现与注释。

