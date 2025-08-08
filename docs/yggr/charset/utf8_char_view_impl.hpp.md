---
# utf8_char_view_impl.hpp 文档

该头文件实现了 yggdrasil 框架中 UTF-8 单字符视图类型 `basic_utf8_char_view`，为 UTF-8 字符串中的单字符提供零拷贝、类型安全、泛型的只读视图。它支持与多种字符串类型、UTF-8 字符类型、数值类型的高效互操作，适用于高性能 UTF-8 字符串处理、泛型算法、容器操作等场景。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类型**：`basic_utf8_char_view<TChar, TTraits>`
- **特性支持**：算术运算、比较、流操作、hash、与原始字符串/utf8_char_impl/utf8_char_reference的互操作、Boost.Range/字节长度支持

---

## 主要功能

### 1. UTF-8 单字符视图类型

- **模板参数**：
  - `TChar`：底层字符类型（通常为 `char`）
  - `TTraits`：traits 类型（如 `std::char_traits<char>`）
- **本质**：内部仅保存一个指向 UTF-8 字符起始位置的指针（不拥有数据），所有操作均为只读视图。

### 2. 构造与赋值

- 支持从原始指针、迭代器、utf8_char_impl、utf8_string_impl、utf8_char_reference、utf8_char_const_reference、其他 utf8_char_view 等多种类型构造。
- 支持拷贝、移动、赋值等操作。

### 3. 类型转换

- 支持隐式/显式转换为底层字符串类型、utf8_char_impl、其他 utf8_char_view、数值类型（to_number）。
- 支持转换为任意字符串类型（如 std::string、std::wstring、boost::container::string 等），自动进行编码转换。

### 4. 数据访问与属性

- `data()`/`operator&`：获取底层数据指针
- `size()`/`length()`：获取字节长度/字符长度（始终为 1）
- `begin()`/`end()`：获取只读迭代器
- `is_validate()`：判断是否为有效 UTF-8 字符
- `is_same_address()`：判断与其他视图/引用/字符类型是否指向同一地址

### 5. 算术与位运算

- 支持与数值类型、其他 utf8_char_view/utf8_char_impl/utf8_char_reference 之间的 `+ - * / % << >> & | ^` 运算。
- 运算结果为 utf8_char_impl 或数值类型，自动处理编码和溢出。

### 6. 比较操作

- 支持与字符、C 字符串、标准字符串、utf8_char_impl、utf8_char_reference、string_charset_helper 等多种类型的 `== != < <= > >=` 比较。
- 比较时自动进行编码转换和内容比对。

### 7. 字符串转换

- `org_str()`：获取原始字符串内容
- `str()`：获取 UTF-8 字符串或转换为目标字符串类型
- `view()`：获取自身或转换为其他视图类型

### 8. hash 支持

- `hash()`：获取哈希值
- 支持 `boost::hash`、`std::hash`（C++11 及以上）直接对 utf8_char_view 进行哈希

### 9. Boost.Range 与字节长度支持

- 支持 Boost.Range 的 range_size
- 支持字节长度计算（byte_size）

### 10. 流输出

- 支持与任意字符类型的 `std::basic_ostream` 互操作，自动进行编码转换

### 11. 泛型与类型 traits

- `is_utf8_char_view_t`、`charset_name_t_string_view_impl` 等 traits，便于泛型编程和类型安全分派
- 支持 make_string_charset_helper 工厂函数，将视图与编码信息绑定

---

## 设计说明

- **零拷贝**：所有操作均为只读视图，不拷贝底层数据，效率极高
- **类型安全**：大量使用 SFINAE、traits、静态断言，防止类型误用
- **泛型友好**：支持任意字符串类型、字符类型、视图、数值类型等
- **编码适配**：自动处理不同字符集编码的转换，保证内容正确
- **与 yggdrasil 框架深度集成**：依赖于框架的字符串类型、traits、编码工具、容器特性等

---

## 用法示例

```cpp
#include <yggr/charset/utf8_char_view_impl.hpp>
#include <yggr/charset/utf8_string_impl.hpp>

using namespace yggr::charset;

utf8_string_impl<> ustr = u8"你好世界";
basic_utf8_char_view<char> v1(ustr, 1); // 视图第2个字符

// 转换为 std::string
std::string s = v1;

// 算术运算
auto c2 = v1 + 1;

// 比较
if (v1 == "好") { /* ... */ }

// 流输出
std::cout << v1 << std::endl;

// 获取原始数据
auto raw = v1.org_str();
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型、分配器或与其他字符串类型的互操作，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

