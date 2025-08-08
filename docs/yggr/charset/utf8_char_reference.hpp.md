---
# utf8_char_reference.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 UTF-8 字符串的**单字符引用类型**（utf8_char_reference 和 utf8_char_const_reference）的类型别名声明。它将泛型 UTF-8 字符引用类型（`basic_utf8_char_reference` 和 `basic_utf8_char_const_reference`）与默认 UTF-8 字符串实现（`utf8_string_impl<>`）结合，便于在项目中直接使用高效、类型安全的 UTF-8 单字符引用。

---

## 主要内容

- **命名空间**：`yggr::charset`、yggr
- **核心类型别名**：
  - `utf8_char_reference`
  - `utf8_char_const_reference`
- **依赖**：
  - `utf8_string_impl.hpp`
  - `utf8_string_view_impl.hpp`
  - `utf8_string_iterator.hpp`
  - `utf8_char_impl.hpp`
  - `utf8_char_view_impl.hpp`
  - `utf8_char_reference_impl.hpp`

---

## 主要功能

### 1. 类型别名声明

```cpp
typedef basic_utf8_char_reference< utf8_string_impl<> > utf8_char_reference;
typedef basic_utf8_char_const_reference< utf8_string_impl<> > utf8_char_const_reference;
```

- **功能**：将泛型 UTF-8 字符引用类型与默认 UTF-8 字符串实现绑定，便于直接使用。
- **适用场景**：需要对 UTF-8 字符串中的单个字符进行高效引用、只读引用、操作、比较、流输出等。

### 2. 全局 using 导出

- 在 yggr 命名空间下导出 `utf8_char_reference` 和 `utf8_char_const_reference`，便于全局统一访问。

---

## 设计说明

- **类型安全**：通过泛型实现，保证与 UTF-8 字符串类型兼容。
- **高效实现**：引用语义，避免不必要的数据拷贝，适合高性能字符串处理。
- **易用性**：直接提供常用类型别名，简化泛型模板的使用。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_char_reference.hpp>
#include <yggr/charset/utf8_string_impl.hpp>

yggr::charset::utf8_string_impl<> ustr = u8"你好世界";
yggr::utf8_char_reference cref(ustr, 1); // 引用第2个字符
yggr::utf8_char_const_reference ccref(ustr, 0); // 只读引用第1个字符

std::cout << cref << std::endl;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义 UTF-8 字符串类型，请使用 `basic_utf8_char_reference` 模板并指定对应的字符串类型。详细用法和扩展方式请查阅源码与注释。

