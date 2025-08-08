---
# string_view_impl.hpp 文档

该头文件实现了 yggdrasil 框架自定义的 `basic_string_view`，为任意字符类型和 traits 提供轻量级、零拷贝的字符串视图功能。它兼容 C++17 `std::string_view` 的大部分接口，并扩展了与 STL/Boost 字符串、字符串视图的比较、拼接、哈希等操作，适用于高性能、泛型的字符串处理场景。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类型**：`basic_string_view<CharT, Traits>`
- **辅助 traits/工具**：比较器、not_within traits、swap、hash、与 STL/Boost 字符串的互操作

---

## 主要功能

### 1. basic_string_view 类模板

- **模板参数**：
  - `CharT`：字符类型（如 char、wchar_t、char16_t、char32_t 等）
  - `Traits`：字符 traits，默认与 `basic_string<CharT>` 保持一致
- **成员类型**：包括指针、引用、迭代器、反向迭代器、size_type、difference_type 等
- **构造函数**：
  - 默认构造（空视图）
  - 由 C 字符串指针、指针+长度、迭代器区间、拷贝/移动构造
- **迭代器接口**：begin/end/rbegin/rend 及其 const 版本
- **元素访问**：operator[]、at、front、back、data
- **容量相关**：size、length、max_size、empty
- **修饰操作**：remove_prefix、remove_suffix
- **内容操作**：
  - copy：拷贝内容到外部缓冲区
  - substr：获取子视图
  - compare/compare_eq：多种重载，支持与视图、C 字符串比较
  - starts_with/ends_with/contains：前缀、后缀、包含判断
  - find/rfind/find_first_of/find_last_of/find_first_not_of/find_last_not_of：多种查找接口
- **哈希**：hash()，支持与 Boost/std::hash 集成

### 2. 非成员操作符重载

- **视图间比较**：==, !=, <, <=, >, >=，支持同模板和不同模板的 string_view
- **与 STL/Boost 字符串比较**：==, !=, <, <=, >, >=
- **与 C 字符串比较**：==, !=, <, <=, >, >=
- **拼接操作**：operator+ 支持 string + string_view、string_view + string
- **追加操作**：operator+= 支持 string += string_view

### 3. IO 支持

- **operator<<**：支持将 string_view 输出到 std::ostream，自动处理对齐和填充

### 4. swap 支持

- **swap**：全局 swap 支持，兼容 std/boost/yggr

### 5. 哈希支持

- **hash_value**：Boost 哈希支持
- **std::hash**：C++11 及以上支持 std::hash

### 6. traits 支持

- **is_basic_string_view_t**：类型 traits，标记为 string_view 类型
- **charset_name_t_string_view_impl**：自动推导 string_view 的默认字符集名称

---

## 设计说明

- **零拷贝**：所有视图操作均不拷贝底层数据，仅保存指针和长度
- **泛型友好**：支持任意字符类型、traits，兼容 STL/Boost 字符串
- **高性能**：接口设计与 STL 保持一致，底层直接操作指针
- **类型安全**：大量使用 SFINAE、traits 保证类型安全
- **兼容性强**：支持与 STL/Boost 字符串、C 字符串、不同模板 string_view 的互操作
- **扩展性好**：可作为自定义字符串库的基础组件

---

## 用法示例

```cpp
#include <yggr/charset/string_view_impl.hpp>
#include <string>

using yggr::charset::basic_string_view;

std::string s = "hello world";
basic_string_view<char> sv(s.data(), s.size());

if (sv.starts_with("hello")) {
    // ...
}

std::cout << sv << std::endl; // 支持流输出

std::string s2 = "world";
if (sv.find(s2) != basic_string_view<char>::npos) {
    // ...
}
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符类型、traits 或与其他字符串类型的互操作，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

