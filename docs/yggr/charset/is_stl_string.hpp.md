---
# is_stl_string.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了类型萃取工具 `is_stl_string`，用于在模板编程中判断某类型是否为 STL 标准字符串类型（即 `std::basic_string` 及其特化，如 `std::string`、`std::wstring` 等）。这对于泛型字符串处理、类型分派等场景非常有用。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心结构体**：`is_stl_string`

---

## 主要功能

### 1. 类型萃取模板

```cpp
template<typename T>
struct is_stl_string : public boost::mpl::false_ {};
```
- 默认情况下，所有类型都被判定为 `false`。

### 2. std::basic_string 特化

```cpp
template<typename Char, typename Traits, typename Alloc>
struct is_stl_string< std::basic_string<Char, Traits, Alloc> > : public boost::mpl::true_ {};
```
- 只有 `std::basic_string` 及其特化类型会被判定为 `true`。

---

## 用法示例

```cpp
#include <yggr/charset/is_stl_string.hpp>
#include <string>
#include <vector>

static_assert(yggr::charset::is_stl_string<std::string>::value, "std::string 是 STL 字符串类型");
static_assert(!yggr::charset::is_stl_string<std::vector<char>>::value, "vector<char> 不是 STL 字符串类型");
```

---

## 设计说明

- **类型安全**：通过模板特化和继承 `boost::mpl::true_`/`false_`，实现编译期类型判断。
- **泛型友好**：便于在模板代码中对 STL 字符串类型进行特化处理或分支。

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型，请特化该结构体。详细用法和扩展方式请查阅源码与注释。

