---
# utf8_string_iterator_decl.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 UTF-8 字符串迭代器相关类型的**前置声明**。它声明了 UTF-8 字符串的通用迭代器、可修改迭代器和常量迭代器模板，为后续 UTF-8 字符串的遍历、修改等功能提供类型基础，便于在头文件依赖较多或需要提前声明类型的场景下使用。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心模板**：
  - `utf8_string_iterator<Char, Basic_Iterator>`
  - `utf8_string_modify_iterator<Char, Basic_Iterator>`
  - `utf8_string_const_iterator<Char, Basic_Iterator>`

---

## 主要功能

### 1. 前置声明

```cpp
template<typename Char, typename Basic_Iterator>
class utf8_string_iterator;

template<typename Char, typename Basic_Iterator>
class utf8_string_modify_iterator;

template<typename Char, typename Basic_Iterator>
class utf8_string_const_iterator;
```

- **功能**：声明了三种 UTF-8 字符串迭代器类型，分别用于普通遍历、可修改遍历和只读遍历。
- **模板参数**：
  - `Char`：底层字符类型（如 `char`）
  - `Basic_Iterator`：底层基础迭代器类型（如 `std::string::iterator`）

### 2. 适用场景

- 用于需要提前声明 UTF-8 字符串迭代器类型的头文件，避免头文件循环依赖或减少编译依赖。
- 便于在泛型编程、字符串遍历、容器操作等场景下统一接口。

---

## 设计说明

- **类型兼容**：与 UTF-8 字符串类型保持一致，便于与字符串、字符视图等类型协作。
- **泛型友好**：支持任意字符类型和基础迭代器类型，适合多字符集、多编码环境。
- **轻量声明**：仅做类型声明，无需包含完整实现，减少编译依赖。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_string_iterator_decl.hpp>

yggr::charset::utf8_string_iterator<char, std::string::iterator> it;
yggr::charset::utf8_string_const_iterator<char, std::string::const_iterator> cit;
yggr::charset::utf8_string_modify_iterator<char, std::string::iterator> mit;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需完整功能和实现，请包含对应的实现头文件。详细用法和扩展方式请查阅源码与注释。

