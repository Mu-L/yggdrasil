---
`database_string_helper.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::database_string_helper` 工具类，主要用于数据库相关字符串的字符集转换。该类为数据库操作中各种字符串类型（如C风格字符串、标准字符串、utf8_string等）与数据库内部字符串类型之间的转换提供统一接口，保证字符集兼容性和类型安全。

---

## 命名空间

- `yggr::database_system`

---

## 主要类

### `database_string_helper`

#### 主要类型定义
- `org_string_type`：数据库内部字符串类型（如 `dtl::tstring`）。
- `inner_string_type`：内部utf8字符串类型。

#### 主要静态方法

- `s_conv(const Char* str, const string& charset_name)`
  - 将C风格字符串按指定字符集转换为数据库内部字符串类型。
  - 默认字符集由类型自动推导。

- `s_conv(const Basic_String<Char, Traits, Alloc>& str, const string& charset_name)`
  - 将标准字符串（如 `std::string`、`std::wstring`）按指定字符集转换为数据库内部字符串类型。
  - 支持自定义分配器和traits。

- `s_conv(const charset::utf8_string_impl<Char, Traits, Alloc>& str, const string& charset_name)`
  - 将 `utf8_string` 类型转换为数据库内部字符串类型。
  - 断言字符集为utf8。

- `s_conv(const charset::string_charset_helper<T1, T2>& src)`
  - 通过 `string_charset_helper` 辅助类型进行转换，适配多种字符串源。

---

## 技术要点

- **字符集兼容**：自动处理不同字符集之间的转换，保证数据库操作的兼容性和正确性。
- **类型安全**：通过SFINAE和类型萃取，确保只有合适的类型才能调用相关接口。
- **多样性支持**：支持C风格字符串、标准字符串、utf8_string等多种常见字符串类型。

---

## 适用场景

- 需要在数据库操作中统一处理多种字符串类型和字符集的项目。
- 需要保证数据库操作字符集兼容性和类型安全的中间件、ORM等系统。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法，请参考各静态方法定义及相关类型说明。

