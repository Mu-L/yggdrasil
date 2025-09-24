---
`database_check_operator.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::database_check_operator` 工具类，主要用于生成数据库操作相关的命令ID和表名字符串。该类为数据库命令分发、日志、调试等场景提供了统一的字符串生成工具。

---

## 命名空间

- `yggr::database_system`

---

## 主要类

### `database_check_operator`

#### 主要静态方法

- `make_database_command_id(const std::string& op_str)`  
  模板方法，根据操作字符串和视图结构类型生成唯一的数据库命令ID。  
  - `View_Struct`：视图结构体类型。
  - `op_str`：操作字符串（如"select"、"insert"等）。
  - 返回值：格式为 `"op_str, typeid(View_Struct).name()"` 的字符串。

- `make_database_command_id(const std::string& op_str, const std::string& type_str)`  
  根据操作字符串和类型字符串生成数据库命令ID。  
  - `op_str`：操作字符串。
  - `type_str`：类型字符串。
  - 返回值：格式为 `"op_str, type_str"` 的字符串。

- `make_table_names(const std::vector<std::string>& tb_names)`  
  将表名数组拼接为逗号分隔的字符串。  
  - `tb_names`：表名字符串数组。
  - 返回值：如 `"table1, table2, table3"` 的字符串。

---

## 技术要点

- **命令唯一性**：通过类型信息和操作名组合，确保数据库命令ID唯一，便于调度和日志追踪。
- **字符串拼接**：高效生成多表操作的表名字符串，适合SQL语句拼接和日志输出。
- **模板与重载**：支持类型安全的命令ID生成，也支持自定义类型字符串。

---

## 适用场景

- 数据库命令分发、调度、日志记录、调试等需要唯一标识和描述数据库操作的场景。
- 多表操作、动态SQL生成等需要表名字符串拼接的场景。

---

## 版权声明

```
Copyright (c) 2010-2022 yggdrasil
MIT License
```

---

如需详细用法，请参考各静态方法定义。

