---
# utf8_string.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 UTF-8 字符串类型 `utf8_string` 的类型定义。它将泛型 UTF-8 字符串实现（`utf8_string_impl<>`）通过类型别名统一为 `utf8_string`，便于在项目中直接使用高效、类型安全的 UTF-8 字符串类型，适合多字符集、高性能字符串处理场景。

---

## 主要内容

- **命名空间**：`yggr::charset`、yggr
- **核心类型别名**：
  - `utf8_string`（等价于 `utf8_string_impl<>`）
- **依赖**：
  - `utf8_char.hpp`
  - `utf8_string_impl.hpp`
  - `utf8_string_view_impl.hpp`

---

## 主要功能

### 1. 类型别名声明

```cpp
typedef utf8_string_impl<> utf8_string;
```

- **功能**：将默认模板参数的 `utf8_string_impl` 作为 UTF-8 字符串类型，便于直接使用。
- **适用场景**：需要高效、类型安全地处理 UTF-8 字符串的场合。

### 2. 全局 using 导出

- 在 yggr 命名空间下导出 `utf8_string`，便于全局统一访问。

---

## 设计说明

- **类型安全**：通过泛型实现，保证与 UTF-8 字符类型、视图类型兼容。
- **高效实现**：底层实现支持高性能的 UTF-8 字符串操作。
- **易用性**：直接提供常用类型别名，简化泛型模板的使用。
- **与 yggdrasil 框架深度集成**：依赖于框架的 UTF-8 字符串、字符类型、traits 等。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_string.hpp>

yggr::charset::utf8_string s = u8"你好世界";
std::cout << s << std::endl;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义 UTF-8 字符串类型，请使用 `utf8_string_impl` 模板并指定对应的字符类型或 traits。详细用法和扩展方式请查阅源码与注释。