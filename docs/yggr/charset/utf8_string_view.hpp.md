---
# utf8_string_view.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 UTF-8 字符串只读视图类型 `utf8_string_view` 的类型别名声明。它将泛型 UTF-8 字符串视图类型（`basic_utf8_string_view<char>`）与默认实现绑定，便于在项目中直接使用高效、类型安全的 UTF-8 字符串只读视图，适合高性能、多字符集环境下的字符串处理和算法。

---

## 主要内容

- **命名空间**：`yggr::charset`、yggr
- **核心类型别名**：
  - `utf8_string_view`（等价于 `basic_utf8_string_view<char>`）
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
typedef basic_utf8_string_view<char> utf8_string_view;
```

- **功能**：将泛型 UTF-8 字符串视图类型与默认 char 实现绑定，便于直接使用。
- **适用场景**：需要对 UTF-8 字符串进行高效只读视图、查找、比较、子串、迭代等操作。

### 2. 全局 using 导出

- 在 yggr 命名空间下导出 `utf8_string_view`，便于全局统一访问。

---

## 设计说明

- **类型安全**：通过泛型实现，保证与 UTF-8 字符串类型兼容。
- **高效实现**：只读视图，零拷贝，适合高性能字符串处理。
- **易用性**：直接提供常用类型别名，简化泛型模板的使用。
- **与 yggdrasil 框架深度集成**：依赖于框架的 UTF-8 字符串、字符类型、traits 等。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_string_view.hpp>
#include <string>

yggr::charset::utf8_string_view sv(u8"你好世界");
if (sv.starts_with(u8"你好")) {
    // ...
}

std::cout << sv << std::endl;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义 UTF-8 字符串类型，请使用 `basic_utf8_string_view` 模板并指定对应的字符类型。详细用法和扩展方式请查阅源码与注释。

