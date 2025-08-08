---
# string_converter.hpp 文档

该头文件定义了 yggdrasil 框架字符集模块中的 `string_converter` 工具类，为**不同字符串类型之间的高效转换**提供了统一泛型接口。支持标准字符串、boost 字符串、utf8_string 及其同构类型之间的零拷贝、编码转换、分配器适配等多种场景，适合多字符集、多容器环境下的高性能字符串处理。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`string_converter`（仅静态方法）
- **内部实现**：`detail::conv_helper` 模板结构体，针对不同类型组合特化

---

## 主要功能

### 1. 字符串类型泛型转换

- 支持任意字符串类型（如 `std::basic_string`、`boost::container::basic_string`、`utf8_string_impl` 等）之间的转换。
- 支持同类型字符串的零拷贝（直接返回引用）。
- 支持不同类型字符串的内容拷贝或编码转换。
- 支持分配器自定义，适合自定义内存管理场景。

### 2. 字符集编码转换

- 支持指定源字符串和目标字符串的字符集编码（如 UTF-8、GBK、UTF-16 等）。
- 若源编码与目标编码一致，则直接拷贝或零拷贝；否则自动进行编码转换。
- 内部调用 `charset_foo::s_xchg` 实现底层转换。

### 3. utf8_string 与其他类型互转

- 针对 `utf8_string_impl` 与其他字符串类型的互转做了专门特化，保证编码正确和高效。
- 支持 utf8_string 的构造、赋值、分配器适配等。

### 4. 支持多种调用方式

- 支持返回新字符串对象（值语义）。
- 支持原地赋值（引用语义）。
- 支持移动语义（BOOST_RV_REF）。
- 支持带分配器的构造和赋值。

### 5. SFINAE 与类型安全

- 大量使用 Boost.TypeTraits、Boost.MPL、enable_if/disable_if，保证类型安全和最优分派。
- 针对同类型、不同类型、utf8_string 相关类型等多种组合做了静态分派。

---

## 设计说明

- **高效实现**：同类型零拷贝，不同类型自动选择最优拷贝或编码转换路径。
- **类型安全**：通过 SFINAE、traits、静态断言，防止类型误用。
- **泛型友好**：支持任意字符串类型、分配器、编码组合，适合模板编程和大规模工程。
- **与 yggdrasil 框架深度集成**：依赖于框架的字符串类型、traits、分配器、编码配置等。

---

## 用法示例

```cpp
#include <yggr/charset/string_converter.hpp>
#include <string>
#include <boost/container/string.hpp>
#include <yggr/charset/utf8_string.hpp>

// std::string 转 boost::container::string
std::string s = "hello";
boost::container::string bs = yggr::charset::string_converter::s_conv<boost::container::string>(s);

// boost::container::string 转 utf8_string
yggr::charset::utf8_string us = yggr::charset::string_converter::s_conv<yggr::charset::utf8_string>(bs);

// 指定编码转换
std::string gbk_str = yggr::charset::string_converter::s_conv<std::string>(us, "utf-8", "gbk");
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型、分配器或编码，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

