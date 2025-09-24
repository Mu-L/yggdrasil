---
`database_connection_init.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::database_connection_init` 类，用于封装数据库连接初始化参数（如DSN、提示、自动提交等），并提供多种字符集和分配器兼容的访问与转换接口。该类便于在多字符集、多平台环境下安全、灵活地管理数据库连接配置。

---

## 命名空间

- `yggr::database_system`
- `yggr::database_system::swap_support`

---

## 主要类

### `database_connection_init`

#### 主要成员变量
- `_dsn`：数据库连接字符串（支持多字符集）。
- `_bprompt`：是否弹出提示（如登录对话框）。
- `_bauto_commit`：是否自动提交事务。

#### 主要接口

- **构造与赋值**
  - 支持默认、拷贝、移动构造与赋值，兼容C++11及更早标准。
  - 支持通过任意可构造为utf8_string的字符串类型初始化DSN。

- **DSN访问与转换**
  - `dsn_string()`：获取/设置原始DSN字符串。
  - `dsn_string(const Alloc&)`：使用指定分配器获取DSN字符串。
  - `dsn_string(const string& charset_name)`：转换为指定字符集的字符串。
  - `dsn_string(const Alloc&, const string& charset_name)`：分配器+字符集双重自定义。

- **参数访问**
  - `prompt()`：获取/设置是否弹出提示。
  - `auto_commit()`：获取/设置是否自动提交。

- **swap支持**
  - 提供高效的swap实现，便于容器操作和性能优化。

---

## 技术要点

- **字符集兼容**：支持多字符集DSN输入与输出，适应国际化和多数据库环境。
- **分配器兼容**：支持自定义分配器，便于与STL容器集成。
- **高效拷贝/移动**：支持现代C++的拷贝、移动语义。
- **swap友好**：提供标准和boost命名空间下的swap重载。

---

## 适用场景

- 需要灵活配置和管理数据库连接参数的中间件、ORM、数据库驱动等。
- 需要支持多字符集、跨平台、分布式数据库环境的项目。
- 需要高效容器操作和内存管理的数据库连接池等场景。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法，请参考构造函数、成员函数及swap相关实现。

