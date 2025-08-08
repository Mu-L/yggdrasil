---
# utf8_string_view_impl.hpp 文档

该头文件实现了 yggdrasil 框架中 UTF-8 字符串只读视图类型 `basic_utf8_string_view`，为 UTF-8 字符串提供高性能、零拷贝、类型安全的只读访问、查找、比较、子串、迭代等功能。它兼容 STL/Boost 字符串、字符串视图、UTF-8 字符类型，适用于多字符集、多容器环境下的泛型字符串处理和高效算法。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类型**：`basic_utf8_string_view<CharT, TraitsT>`
- **相关类型**：UTF-8 字符类型、迭代器、视图、引用、string_charset_helper
- **特性支持**：查找、比较、子串、starts_with/ends_with/contains、迭代、hash、swap、流输出、Boost.Range

---

## 主要功能

### 1. 只读 UTF-8 字符串视图

- **本质**：以指针和长度保存 UTF-8 字符串的只读视图，不拥有底层数据，零拷贝。
- **泛型支持**：支持任意 1 字节字符类型和 traits，兼容 STL/Boost 字符串及自定义类型。

### 2. 构造与赋值

- 支持从 C 字符串、指针+长度、任意迭代器区间、utf8_string_impl、其他 string_view、utf8_string_iterator、string_charset_helper 等多种类型构造。
- 支持拷贝、移动、赋值等操作。

### 3. 迭代器与元素访问

- 提供 begin/end/cbegin/cend/rbegin/rend 等迭代器，支持正向/反向遍历。
- 支持下标访问、at、front、back、data。
- 迭代器为 UTF-8 字符级别，保证字符边界安全。

### 4. 容量与属性

- size()：字节长度
- length()：UTF-8 字符数
- empty()：是否为空
- is_validate()：是否为合法 UTF-8 字符串

### 5. 子串与拷贝

- substr()：获取子视图，支持多种目标类型和分配器
- copy()：拷贝内容到外部缓冲区，支持编码转换

### 6. 查找与比较

- compare/compare_eq：支持与各种字符串类型、视图、C 字符串、UTF-8 字符类型的比较，支持子串比较和编码转换
- starts_with/ends_with/contains：前缀、后缀、包含判断，支持多种类型和编码
- find/rfind/find_first_of/find_last_of/find_first_not_of/find_last_not_of：多种查找接口，支持多类型和编码

### 7. 类型转换与原始访问

- str()/org_str()/org_view()：获取原始视图或转换为目标字符串类型，支持编码转换
- affix_length/recount_length：手动设置或重新计算 UTF-8 长度

### 8. 非成员操作符重载

- 支持与 string_charset_helper、C 字符串、STL/Boost 字符串、string_view、其他 utf8_string_view 的 == != < <= > >= 比较
- 支持流输出（operator<<），自动编码转换

### 9. swap、hash、Boost.Range

- swap：高效交换两个视图
- hash/hash_value/std::hash：支持哈希容器
- Boost.Range：支持 range_size

### 10. 泛型 traits 与辅助

- is_utf8_string_view_t、utf8_string_view_loadable、is_validate_string 等 traits，便于泛型算法分派
- string_charset_helper_data：与 string_charset_helper 协作

---

## 设计说明

- **零拷贝**：所有视图操作均不拷贝底层数据，效率极高
- **类型安全**：大量使用 SFINAE、traits、静态断言，防止类型误用
- **泛型友好**：支持任意字符串类型、字符类型、视图、引用、string_charset_helper
- **编码适配**：自动处理不同字符集编码的转换，保证内容正确
- **与 yggdrasil 框架深度集成**：依赖于框架的字符串类型、traits、编码工具、容器特性等

---

## 用法示例

```cpp
#include <yggr/charset/utf8_string_view_impl.hpp>
#include <string>

using yggr::charset::basic_utf8_string_view;

std::string s = u8"你好世界";
basic_utf8_string_view<char> sv(s.data(), s.size());

if (sv.starts_with(u8"你好")) {
    // ...
}

auto sub = sv.substr(2, 2); // 获取子串视图

std::cout << sv << std::endl; // 支持流输出

if (sv.find(u8"世") != basic_utf8_string_view<char>::npos) {
    // ...
}
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型、分配器或与其他字符串类型的互操作，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

