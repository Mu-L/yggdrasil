---
`database_charset_config.hpp` 文档

# 文件概述

该头文件定义了数据库系统的字符集配置工具类 `yggr::database_system::database_charset_config`，用于统一管理和获取数据库默认字符集名称。通过宏和静态方法，支持灵活切换和获取当前数据库字符集，便于多字符集环境下的数据库开发。

---

## 命名空间

- `yggr::database_system`

---

## 主要内容

### 1. 宏定义

- `TAG_YGGR_DATABASE_CHARSET_NAME`  
  若未定义，则默认使用 `TAG_YGGR_UTF8_STRING_CHARSET_NAME`，即 UTF-8 字符集。

- `YGGR_DATABASE_CHARSET_NAME()`  
  获取当前数据库字符集名称的 C 字符串指针。

- `YGGR_STR_DATABASE_CHARSET_NAME()`  
  获取当前数据库字符集名称的 `string` 类型引用。

---

### 2. 类 `database_charset_config`

- **静态方法**
  - `get_default_database_charset_name()`  
    返回当前数据库默认字符集名称（`const char*`）。若与 UTF-8 相同，则返回内部默认字符集，否则返回宏定义的字符集名。

  - `get_str_default_database_charset_name()`  
    返回当前数据库默认字符集名称（`const string&`）。同样根据宏定义和 UTF-8 判断返回。

---

## 技术要点

- **灵活性**：通过宏和静态方法，支持在编译期或运行期灵活切换数据库字符集。
- **兼容性**：默认支持 UTF-8，也可通过宏自定义其他字符集，适应不同数据库和国际化需求。
- **统一入口**：所有字符集相关操作均通过该类和宏进行，便于维护和扩展。

---

## 适用场景

- 需要支持多字符集或国际化的数据库应用。
- 需要统一管理和切换数据库字符集配置的项目。
- 需要与 yggr 框架其他字符集相关模块协同工作的场景。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法，请参考具体宏和静态方法定义。

