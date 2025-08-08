---
# other_char.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 `other_char` 类型工具，用于在模板编程中根据主字符类型和两个候选类型，自动推导“辅助字符类型”。这对于泛型字符串处理、字符类型适配等场景非常有用，尤其适合在 char/wchar_t、char/char16_t 等多字符集环境下自动选择另一种字符类型。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心模板**：`other_char`

---

## 主要功能

### 1. other_char 模板结构体

```cpp
template<typename C, typename C1, typename C2>
struct other_char
{
    typedef C type;
};
```
- 默认情况下，`type` 为第一个模板参数 `C`。

#### 特化1

```cpp
template<typename C, typename C2>
struct other_char<C, C, C2>
{
    typedef C2 type;
};
```
- 若第一个和第二个模板参数类型相同，则 `type` 为第三个参数 `C2`。

#### 特化2

```cpp
template<typename C, typename C1>
struct other_char<C, C1, C>
{
    typedef C1 type;
};
```
- 若第一个和第三个模板参数类型相同，则 `type` 为第二个参数 `C1`。

### 2. 类型断言

- 使用 `YGGR_ASSERT_CHAR_TYPE` 宏断言模板参数必须为字符类型，保证类型安全。

---

## 设计说明

- **类型推导**：根据主类型和两个候选类型，自动推导“另一种”字符类型，便于泛型代码中自动适配。
- **泛型友好**：适用于 char/wchar_t、char/char16_t、char/char32_t 等多字符集场景。
- **类型安全**：通过静态断言宏，防止非字符类型误用。

---

## 用法示例

```cpp
#include <yggr/charset/other_char.hpp>

// 主类型为 char，候选为 char 和 wchar_t，结果为 char
typedef yggr::charset::other_char<char, char, wchar_t>::type t1; // t1 == char

// 主类型为 wchar_t，候选为 char 和 wchar_t，结果为 char
typedef yggr::charset::other_char<wchar_t, char, wchar_t>::type t2; // t2 == char

// 主类型为 char，候选为 wchar_t 和 char，结果为 wchar_t
typedef yggr::charset::other_char<char, wchar_t, char>::type t3; // t3 == wchar_t
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符类型，请确保其满足 `YGGR_ASSERT_CHAR_TYPE` 的要求。详细用法和扩展方式请查阅源码与注释。

