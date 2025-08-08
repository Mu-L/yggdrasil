---
# string.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了**字符串类型适配、工具函数与特性扩展**，统一支持 STL 字符串和 Boost.Container 字符串，并为泛型编程、类型安全、跨编码/跨容器字符串操作提供了丰富的辅助接口。它是 yggdrasil 字符串体系的核心适配层，适用于多字符集、多容器环境下的高性能字符串处理。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **适配类型**：`std::basic_string`、`boost::container::basic_string`
- **主要功能**：
  - 流操作符适配（输入/输出）
  - 同构字符串类型间的比较与交换
  - getline 适配与实现
  - shrink_to_fit 适配
  - 字符串类型 traits 与泛型工具
  - 字符串有效性检查
  - 字符串类型自动推导与 traits
  - 字符串原始数据与长度适配

---

## 主要功能详解

### 1. 流操作符适配

- **输出流重载**  
  支持 `boost::container::basic_string` 与任意字符类型输出流的互操作，自动进行字符集转换。
- **输入流重载**  
  支持 `boost::container::basic_string` 从任意字符类型输入流读取内容，并自动进行字符集转换。

### 2. 同构字符串类型间的比较与交换（Boost 1.70+）

- 支持不同 allocator 的 `boost::container::basic_string` 之间的 `==`, `!=`, `<`, `<=`, `>`, `>=` 比较，底层通过 reinterpret_cast 实现零拷贝比较。
- 支持同构字符串类型间的 swap，自动适配 allocator。

### 3. getline 适配与实现

- 提供 `yggr::charset::getline` 重载，支持 `boost::container::basic_string` 与标准流的互操作，兼容 STL getline 行为。

### 4. shrink_to_fit 适配

- 对 STL/Boost 字符串类型，自动适配 shrink_to_fit（若无 shrink_to_fit，则通过 swap 实现容量收缩）。

### 5. 字符串类型 traits 与泛型工具

- `string_t_getter`：根据当前字符串类型和目标类型，自动推导返回类型（引用或新对象）。
- `basic_string_getter`：统一获取 STL/Boost 字符串的引用。
- `string_traits`：自动萃取字符串类型的 char_type、traits_type、allocator_type、迭代器等信息。

### 6. 字符串有效性检查

- `is_validate_char`：判断字符类型是否合法。
- `is_validate_string`：判断字符串内容与长度是否一致，防止非法字符串。

### 7. 字符串原始数据与长度适配

- `org_str`：获取原始字符串指针或引用，适配 C 风格字符串、数组、标准字符串等。
- `recount_length`：重新计算字符串长度，适配多种类型。
- `affix_length`：断言长度与内容一致，保证数据安全。

---

## 设计说明

- **类型兼容**：统一适配 STL/Boost 字符串类型，便于跨容器、跨编码开发。
- **泛型友好**：大量使用模板、SFINAE、traits，支持任意字符串类型和字符类型的泛型编程。
- **高效实现**：同构类型零拷贝，自动分派最优实现路径。
- **类型安全**：静态断言、traits 检查，防止类型误用。
- **与 yggdrasil 框架深度集成**：依赖于框架的类型 traits、编码工具、容器特性等。

---

## 用法示例

```cpp
#include <yggr/charset/string.hpp>
#include <boost/container/string.hpp>
#include <string>

// 流输出
boost::container::string bs = "hello";
std::cout << bs << std::endl;

// getline 适配
boost::container::string bs2;
std::getline(std::cin, bs2);

// shrink_to_fit
std::string s = "abc";
yggr::charset::shrink_to_fit(s);

// 字符串类型 traits
typedef yggr::charset::string_traits<std::string>::char_type my_char_t;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型、traits 或流适配，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

