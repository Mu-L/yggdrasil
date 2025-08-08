---
# utf8_string_view_decl.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 UTF-8 字符串视图类型 `basic_utf8_string_view` 的**前置声明**。它用于在头文件依赖较多或需要提前声明类型的场景下，避免循环依赖和减少编译开销，为后续 UTF-8 字符串视图相关功能（如只读视图、零拷贝子串等）提供类型基础。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心模板**：`basic_utf8_string_view<CharT, Traits>`

---

## 主要功能

### 1. 前置声明

```cpp
template<typename CharT, typename Traits = typename basic_string<CharT>::traits_type>
class basic_utf8_string_view;
```

- **功能**：声明了一个泛型 UTF-8 字符串视图类型，支持自定义字符类型和 traits。
- **默认参数**：
  - `CharT`：字符类型（如 `char`、`wchar_t` 等）
  - `Traits`：traits 类型，默认为 `basic_string<CharT>::traits_type`
- **适用场景**：用于需要提前声明 UTF-8 字符串视图类型的头文件，避免头文件循环依赖或减少编译依赖。

---

## 设计说明

- **类型兼容**：与 `yggr::charset::basic_string` 保持 traits 一致，便于与字符串类型协作。
- **泛型友好**：支持任意字符类型和 traits，适合多字符集、多编码环境。
- **轻量声明**：仅做类型声明，无需包含完整实现，减少编译依赖。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_string_view_decl.hpp>

yggr::charset::basic_utf8_string_view<char> sv;
yggr::charset::basic_utf8_string_view<wchar_t> wsv;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需完整功能和实现，请包含对应的实现头文件。详细用法和扩展方式请查阅源码与注释。

