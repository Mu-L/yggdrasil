---
# utf8_char_reference_impl.hpp 文档

该头文件实现了 yggdrasil 框架中 UTF-8 字符串的**单字符引用类型**（`basic_utf8_char_reference` 和 `basic_utf8_char_const_reference`），为 UTF-8 字符串中的单字符提供高效、类型安全、泛型的引用与只读引用支持。它支持算术运算、比较、流操作、swap、哈希、与原始字符串的互转等丰富功能，是 UTF-8 字符串体系的核心组件之一。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类型**：
  - `basic_utf8_char_reference<Utf8String>`：可修改的 UTF-8 单字符引用
  - `basic_utf8_char_const_reference<Utf8String>`：只读的 UTF-8 单字符引用
- **辅助 traits/工具**：类型 traits、swap、hash、与字符串/视图/数值类型的互操作

---

## 主要功能

### 1. 单字符引用与只读引用

- **引用语义**：可直接引用 UTF-8 字符串中的单个字符（支持多字节 UTF-8 字符），无需拷贝。
- **只读引用**：`basic_utf8_char_const_reference` 提供只读访问，适合常量上下文。

### 2. 构造与赋值

- 支持从字符串、迭代器、位置、其他引用类型等多种方式构造。
- 支持从字符、C 字符串、标准字符串、utf8_char_impl、utf8_char_view、string_charset_helper 等多种类型赋值。

### 3. 算术与位运算

- 支持与数值类型、其他引用/只读引用/视图/utf8_char_impl 之间的 `+ - * / % << >> & | ^` 运算。
- 支持自增、自减、复合赋值（+=、-=、*=、/=、%=、<<=、>>=）。
- 运算结果为 utf8_char_impl 或数值类型，自动处理编码和溢出。

### 4. 比较操作

- 支持与字符、C 字符串、标准字符串、utf8_char_impl、utf8_char_view、string_charset_helper、其他引用类型等多种类型的 `== != < <= > >=` 比较。
- 比较时自动进行编码转换和内容比对。

### 5. 类型转换与数据访问

- 支持隐式/显式转换为底层字符串类型、utf8_char_impl、utf8_char_view、数值类型（to_number）。
- 支持获取底层数据指针、长度、索引、allocator。
- 支持 org_str() 获取原始字符串内容，str() 获取转换后的字符串。

### 6. swap 支持

- 支持与 utf8_char_impl、其他引用类型、字符串类型之间的高效 swap。
- 提供 swap_support 命名空间，兼容 std/boost/yggr 的 swap 调用。

### 7. 流输入输出

- 支持与任意字符类型的 `std::basic_ostream`/`std::basic_istream` 互操作，自动进行编码转换。

### 8. 哈希与 Boost.Range 支持

- 支持 `boost::hash`、`std::hash`（C++11 及以上）直接对引用类型进行哈希。
- 支持 Boost.Range 的 range_size。
- 支持字节长度计算（byte_size）。

### 9. 泛型与类型 traits

- `is_utf8_char_reference_t`、`is_utf8_char_const_reference_t`、`charset_name_t` 等 traits，便于泛型编程和类型安全分派。
- 支持 make_string_charset_helper 工厂函数，将引用与编码信息绑定。

---

## 设计说明

- **高效实现**：所有操作均为引用语义，避免不必要的数据拷贝。
- **类型安全**：大量使用 SFINAE、traits、静态断言，防止类型误用。
- **泛型友好**：支持任意 UTF-8 字符串类型、分配器、视图、数值类型等。
- **编码适配**：自动处理不同字符集编码的转换，保证内容正确。
- **与 yggdrasil 框架深度集成**：依赖于框架的字符串类型、traits、编码工具、容器特性等。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_char_reference_impl.hpp>
#include <yggr/charset/utf8_string_impl.hpp>

using namespace yggr::charset;

utf8_string_impl<> ustr = u8"你好世界";
basic_utf8_char_reference<utf8_string_impl<>> cref(ustr, 1); // 引用第2个字符

// 赋值
cref = 'A';

// 算术运算
auto c2 = cref + 1;

// 比较
if (cref == '你') { /* ... */ }

// swap
utf8_char_impl<> cimpl("世");
swap(cref, cimpl);

// 流输出
std::cout << cref << std::endl;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型、分配器或与其他字符串类型的互操作，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

