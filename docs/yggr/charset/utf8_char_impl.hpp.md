---
# utf8_char_impl.hpp 文档

该头文件实现了 yggdrasil 框架中 UTF-8 单字符类型 `utf8_char_impl`，为 UTF-8 字符的存储、编码转换、算术运算、比较、流操作、哈希等提供了高度泛型和类型安全的支持。它是 UTF-8 字符串体系的基础组件，适用于多字符集、多容器环境下的高性能 UTF-8 字符处理。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类型**：`utf8_char_impl<TChar, TTraits, TAlloc>`
- **相关类型**：`utf8_string_impl`、`basic_utf8_char_view`、`basic_utf8_char_reference`、`string_charset_helper`
- **特性支持**：算术运算、比较、流输入输出、swap、哈希、类型 traits

---

## 主要功能

### 1. UTF-8 单字符泛型类型

- **模板参数**：
  - `TChar`：底层字符类型（通常为 `char`，仅支持 char）
  - `TTraits`：traits 类型（如 `std::char_traits<char>`）
  - `TAlloc`：分配器类型
- **本质**：内部以 `basic_string<TChar, TTraits, TAlloc>` 存储 UTF-8 字符的字节序列，始终保证只存储一个有效 UTF-8 字符。

### 2. 构造与赋值

- 支持从任意可转换为字符的类型、C 字符串、标准字符串、字符串视图、迭代器区间、initializer_list、其他 utf8_char_impl、utf8_string_impl、utf8_char_view/reference/const_reference、string_charset_helper 等多种类型构造和赋值。
- 支持指定源字符集编码，自动进行编码转换。
- 支持分配器自定义。

### 3. 算术与位运算

- 支持与数值类型、其他 utf8_char_impl、utf8_char_view/reference/const_reference 之间的 `+ - * / % << >>` 运算，结果为 utf8_char_impl 或数值类型。
- 支持自增、自减、复合赋值（+=、-=、*=、/=、%=、<<=、>>=）。
- 支持与数值类型的位运算（& | ^），结果为数值类型或 s32。

### 4. 比较操作

- 支持与字符、C 字符串、标准字符串、字符串视图、utf8_char_impl、utf8_char_view/reference/const_reference、string_charset_helper 等多种类型的 `== != < <= > >=` 比较。
- 比较时自动进行编码转换和内容比对。

### 5. 类型转换

- 支持隐式转换为底层字符串类型、utf8_string_impl、utf8_char_view/reference/const_reference、数值类型（to_number）。
- 支持显式转换为目标字符串类型（如 std::string、std::wstring）。

### 6. 其他成员函数

- `data()` / `c_str()`：获取底层数据指针
- `size()` / `length()`：获取字节长度/字符长度（始终为 1）
- `empty()`：判断是否为空（始终为 false）
- `is_validate()`：判断内容是否合法 UTF-8 字符
- `shrink_to_fit()`：收缩底层存储
- `org_str()` / `str()`：获取底层字符串或转换为目标字符串类型
- `view()`：获取字符串视图
- `hash()`：获取哈希值

### 7. swap 支持

- 支持与同构/异构 allocator 的 utf8_char_impl、底层字符串、utf8_char_reference 之间的高效 swap。

### 8. 流输入输出

- 支持与任意字符类型的 `std::basic_ostream`/`std::basic_istream` 互操作，自动进行编码转换。

### 9. 哈希与 Boost.Range 支持

- 支持 `boost::hash`、`std::hash`（C++11 及以上）直接对 utf8_char_impl 进行哈希。
- 支持 Boost.Range 的 range_size。

### 10. 类型 traits 与泛型支持

- `is_utf8_char_t`、`charset_name_t_string_impl`、`other_char`、`utf8_char_constructable`、`utf8_char_loadable` 等 traits，便于泛型编程和类型安全分派。

---

## 设计说明

- **类型安全**：大量使用 SFINAE、traits、静态断言，防止类型误用。
- **泛型友好**：支持任意字符串类型、字符类型、分配器、字符串视图等。
- **高效实现**：同构类型零拷贝，自动分派最优实现路径。
- **编码适配**：自动处理不同字符集编码的转换，保证内容正确。
- **与 yggdrasil 框架深度集成**：依赖于框架的字符串类型、traits、编码工具、容器特性等。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_char_impl.hpp>
#include <string>

using yggr::charset::utf8_char_impl;

// 构造
utf8_char_impl<char> c1('你');
utf8_char_impl<char> c2("好");
utf8_char_impl<char> c3(std::string("世"));

// 算术运算
auto c4 = c1 + 1;
auto c5 = c2 * 2;

// 比较
bool eq = (c1 == '你');
bool lt = (c1 < c2);

// 转换
std::string s = c1.str<std::string>();

// 流输出
std::cout << c1 << std::endl;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符类型、分配器或与其他字符串类型的互操作，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

