---
`database_accesser.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::database_accesser` 类，是对 `basic_database_accesser` 的进一步封装，提供了更友好的接口以支持多字符集（如 UTF-8）和多种字符串类型的数据库操作。该类通过静态模板方法，简化了数据库的增删改查、SQL 执行等常用操作，并自动处理字符串编码转换。

---

## 命名空间

- `yggr::database_system`

---

## 主要类

### 1. `database_accesser`
- 继承自 `basic_database_accesser`，对其接口进行扩展和适配。
- 主要功能：
  - 支持多种字符串类型（如 `std::string`、`yggr::charset::utf8_string` 等）作为表名、SQL 语句等参数。
  - 自动进行字符串编码转换，保证数据库操作的兼容性和安全性。
  - 保留了所有基础的数据库操作接口，并通过模板和 SFINAE 技术保证类型安全。

---

## 主要接口说明

### 连接管理
- `s_keep_connect`：确保数据库连接可用，自动重连。

### 查询操作
- `s_select_records_of_view`：从数据库视图中查询数据，支持自定义数据类型、容器和处理器，自动处理字符串编码。

### 插入操作
- `s_insert_records_of_table`：向数据库表插入数据，支持批量插入、自定义数据转换和事务控制。

### 更新操作
- `s_update_records_of_table`：更新数据库表中的数据，支持批量、自定义处理和事务控制。

### 删除操作
- `s_delete_records_of_table`：删除数据库表中的数据，支持批量、自定义处理和事务控制。

### SQL 执行
- `s_execute_sql`：执行 SQL 语句，支持多种字符串类型和事务控制。
- `s_execute_sql_non_conv`：直接执行原始字符串类型的 SQL 语句（不做编码转换）。

### 通用处理器调用
- `s_connection_using_handler`：以安全方式获取连接并执行自定义处理器，自动处理异常和连接归还。

---

## 技术要点

- **字符串兼容性**：通过 `charset::utf8_string_constructable`、`database_string_helper::s_conv` 等机制，自动将各种字符串类型转换为数据库可用的格式。
- **类型安全**：大量使用模板和 SFINAE（`boost::enable_if`、`boost::mpl::and_`）保证只有合适的类型才能调用相关接口。
- **异常安全**：所有操作均通过 `error_type` 返回详细错误信息，便于上层捕获和处理。
- **事务支持**：所有增删改操作均支持事务提交与回滚参数。

---

## 适用场景

- 需要对数据库进行统一、类型安全、字符集友好的访问封装时。
- 适用于多种数据库连接池、数据类型和容器的场景。
- 便于扩展和适配不同数据库实现，尤其适合多语言环境下的数据库操作。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细接口用法或示例，请参考具体函数模板定义及注释。

