---
# utf8_string_iterator.hpp 文档

该头文件为 yggdrasil 框架字符集模块实现了 UTF-8 字符串的三种高性能迭代器：普通迭代器（utf8_string_iterator）、可修改迭代器（utf8_string_modify_iterator）、常量迭代器（utf8_string_const_iterator）。这些迭代器支持以字符为单位（而非字节）安全遍历、定位、比较和操作 UTF-8 字符串，适用于多字节字符集环境下的泛型字符串处理。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类型**：
  - `utf8_string_iterator<Char, Basic_Iterator>`
  - `utf8_string_modify_iterator<Char, Basic_Iterator>`
  - `utf8_string_const_iterator<Char, Basic_Iterator>`
- **辅助工具**：
  - 字节长度支持（byte_size）
  - 迭代器类型 traits
  - swap 支持
  - 比较操作符重载

---

## 主要功能

### 1. UTF-8 字符串迭代器

#### 1.1 utf8_string_iterator

- 继承自底层基础迭代器，支持随机访问。
- 以 UTF-8 字符为单位遍历字符串，自动跳过多字节字符的中间字节。
- 支持 `*`、`[]`、`+`、`-`、`++`、`--`、`+=`、`-=` 等操作，保证字符边界安全。
- 支持与其他迭代器的比较和距离计算。
- 支持 swap。

#### 1.2 utf8_string_modify_iterator

- 以字符索引定位 UTF-8 字符串，适合修改操作。
- 支持通过字符串和字符位置构造，或通过底层迭代器定位。
- 支持 `*`、`[]`、`+`、`-`、`++`、`--`、`+=`、`-=` 等操作。
- 支持与其他迭代器的比较和距离计算。
- 支持 swap 和 set 操作。

#### 1.3 utf8_string_const_iterator

- 只读 UTF-8 字符串迭代器，支持常量上下文。
- 支持与普通迭代器、可修改迭代器的互转和比较。
- 支持所有常用迭代器操作和 swap。

### 2. 字节长度支持

- 提供 `byte_size_iterator_helper`，可计算任意 UTF-8 迭代器区间的字节长度，兼容正向和反向迭代器。

### 3. 比较操作符重载

- 支持不同类型 UTF-8 迭代器之间的 `== != < <= > >=` 比较，保证泛型算法兼容性。

### 4. swap 支持

- 提供 `swap_support` 命名空间下的 swap 重载，兼容 std/boost/yggr 的 swap 调用。

### 5. 类型 traits

- 提供 `is_utf8_string_iterator_t`、`is_utf8_string_modify_iterator_t`、`is_utf8_string_const_iterator_t`，便于泛型编程时类型分派。

---

## 设计说明

- **字符级安全**：所有操作均以 UTF-8 字符为单位，避免破坏多字节字符边界。
- **泛型友好**：支持任意底层迭代器和字符类型，适合模板编程和多容器环境。
- **高效实现**：底层直接操作指针或迭代器，零拷贝，效率高。
- **类型安全**：大量使用 SFINAE、traits、静态断言，防止类型误用。
- **与 yggdrasil 框架深度集成**：依赖于框架的字符串类型、traits、编码工具、容器特性等。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_string_impl.hpp>
#include <yggr/charset/utf8_string_iterator.hpp>

using namespace yggr::charset;

utf8_string_impl<> ustr = u8"你好世界";
auto begin = utf8_string_iterator<utf8_char, std::string::iterator>(ustr.org_str().begin());
auto end = utf8_string_iterator<utf8_char, std::string::iterator>(ustr.org_str().end());

for (auto it = begin; it != end; ++it) {
    auto ch_view = *it; // 得到 basic_utf8_char_view
    // ...处理每个字符
}

// 可修改迭代器
utf8_string_modify_iterator<utf8_char, std::string::iterator> mit(ustr, 1);
*mit = 'A'; // 修改第2个字符
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型、分配器或与其他字符串类型的互操作，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

