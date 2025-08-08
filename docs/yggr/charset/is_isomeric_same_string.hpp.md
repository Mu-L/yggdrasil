---
# is_isomeric_same_string.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了**同构字符串类型判断**的类型萃取工具，主要用于判断两个字符串类型（如 `std::basic_string`、`boost::container::basic_string` 等）是否为“同构异参”类型，即模板参数（字符类型、traits、allocator）一致但类型本身不同。这对于泛型字符串处理、类型安全转换等场景非常有用。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心结构体**：
  - `is_isomeric_same_string`
  - `is_same_or_isomeric_same_string`

---

## 主要功能

### 1. is_isomeric_same_string

```cpp
template<typename StringL, typename StringR>
struct is_isomeric_same_string : public boost::mpl::bool_<...> {};
```

- **功能**：判断 StringL 和 StringR 是否为“同构异参字符串类型”。
- **判定标准**：
  - 两者为同一模板（如都是 `basic_string`，但可以是 std 或 boost）。
  - 模板参数数量为 3（通常为 Char、Traits、Allocator）。
  - 第三个模板参数（Allocator）类型不同（用于区分 std::allocator 与 boost::container::allocator）。
  - 字符类型（value_type）相同。
  - traits_type 相同。
  - allocator_type 相同。
- **典型用途**：判断 `std::basic_string<char, Traits, Alloc>` 与 `boost::container::basic_string<char, Traits, Alloc>` 是否为同构类型。

### 2. is_same_or_isomeric_same_string

```cpp
template<typename StringL, typename StringR>
struct is_same_or_isomeric_same_string : public boost::mpl::or_<...> {};
```

- **功能**：判断 StringL 和 StringR 是否为完全相同类型或同构异参字符串类型。
- **判定标准**：等价于 `boost::is_same<StringL, StringR>` 或 `is_isomeric_same_string<StringL, StringR>` 为 true。

---

## 设计说明

- **模板元编程**：通过模板特化、类型展开、traits 检查等方式实现复杂类型关系的编译期判断。
- **兼容性强**：适配 boost 1.70 及以上版本，解决 boost::container::basic_string 模板参数变化带来的兼容性问题。
- **类型安全**：便于在泛型代码中安全地进行字符串类型转换或重载分派。

---

## 用法示例

```cpp
#include <yggr/charset/is_isomeric_same_string.hpp>
#include <string>
#include <boost/container/string.hpp>

static_assert(
    yggr::charset::is_isomeric_same_string<
        std::basic_string<char, std::char_traits<char>, std::allocator<char>>,
        boost::container::basic_string<char, std::char_traits<char>, std::allocator<char>>
    >::value,
    "两者为同构异参字符串类型"
);

static_assert(
    yggr::charset::is_same_or_isomeric_same_string<
        std::string,
        std::string
    >::value,
    "完全相同类型"
);
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型，请确保其模板参数结构与上述标准一致。详细用法和扩展方式请查阅源码与注释。

