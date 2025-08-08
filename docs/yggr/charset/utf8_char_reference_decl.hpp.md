---
# utf8_char_reference_decl.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 UTF-8 字符引用类型的**前置声明**，即 `basic_utf8_char_reference` 和 `basic_utf8_char_const_reference`。它用于在头文件依赖较多或需要提前声明类型的场景下，避免循环依赖和减少编译开销，为后续 UTF-8 字符串和字符操作提供类型基础。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心模板**：
  - `basic_utf8_char_reference<Utf8String>`
  - `basic_utf8_char_const_reference<Utf8String>`

---

## 主要功能

### 1. 前置声明

```cpp
template<typename Utf8String>
class basic_utf8_char_reference;

template<typename Utf8String>
class basic_utf8_char_const_reference;
```

- **功能**：声明了两个泛型 UTF-8 字符引用类型，分别用于可修改和只读场景。
- **模板参数**：
  - `Utf8String`：底层 UTF-8 字符串类型（如 `utf8_string_impl` 等）。

### 2. 适用场景

- 用于需要提前声明 UTF-8 字符引用类型的头文件，避免头文件循环依赖或减少编译依赖。
- 便于在泛型编程、字符串视图、字符操作等场景下统一接口。

---

## 设计说明

- **类型兼容**：与 UTF-8 字符串类型保持一致，便于与字符串、字符视图等类型协作。
- **泛型友好**：支持任意 UTF-8 字符串类型，适合多字符集、多编码环境。
- **轻量声明**：仅做类型声明，无需包含完整实现，减少编译依赖。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_char_reference_decl.hpp>

yggr::charset::basic_utf8_char_reference<yggr::charset::utf8_string_impl<>> ref;
yggr::charset::basic_utf8_char_const_reference<yggr::charset::utf8_string_impl<>> cref;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需完整功能和实现，请包含对应的实现头文件。详细用法和扩展方式请查阅源码与注释。

