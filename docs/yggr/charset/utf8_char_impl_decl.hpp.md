---
# utf8_char_impl_decl.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 UTF-8 字符实现类 `utf8_char_impl` 的**前置声明**。它定义了一个高度泛型的 UTF-8 字符类型模板，为后续 UTF-8 字符相关功能（如 utf8 字符串、字符处理等）提供类型基础，便于在头文件依赖较多或需要提前声明类型的场景下使用。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心模板**：`utf8_char_impl<TChar, TTraits, TAlloc>`

---

## 主要功能

### 1. utf8_char_impl 前置声明

```cpp
template<
    typename TChar = char,
    typename TTraits = typename basic_string<TChar>::traits_type,
    typename TAlloc = typename mplex::typename_expand_get<basic_string<TChar>, 2>::type
>
class utf8_char_impl;
```

- **功能**：声明了一个泛型 UTF-8 字符类型，支持自定义字符类型、traits 和分配器。
- **默认参数**：
  - `TChar`：字符类型，默认为 `char`
  - `TTraits`：traits 类型，默认为 `basic_string<TChar>::traits_type`
  - `TAlloc`：分配器类型，默认为 `basic_string<TChar>` 的第三个模板参数（通常为 allocator）
- **适用场景**：用于需要提前声明 UTF-8 字符类型的头文件，避免头文件循环依赖或减少编译开销。

---

## 设计说明

- **类型兼容**：与 `yggr::charset::basic_string` 保持 traits 和 allocator 一致，便于与字符串类型协作。
- **泛型友好**：支持任意字符类型、traits 和分配器，适合多字符集、多编码环境。
- **轻量声明**：仅做类型声明，无需包含完整实现，减少编译依赖。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_char_impl_decl.hpp>

yggr::charset::utf8_char_impl<> c; // 默认 char 版本
yggr::charset::utf8_char_impl<wchar_t> wc; // wchar_t 版本
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需完整功能和实现，请包含对应的实现头文件。详细用法和扩展方式请查阅源码与注释。

