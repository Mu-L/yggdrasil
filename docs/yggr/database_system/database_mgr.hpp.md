---
`database_mgr.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::database_mgr` 模板类，是一个通用的数据库管理器，基于 `dbs_manager::dbs_mgr` 实现。它支持多种数据库连接类型、访问器、用户自定义数据，适用于需要统一管理数据库连接、命令注册与调度的高性能场景。

---

## 命名空间

- `yggr::database_system`

---

## 主要模板类

### `database_mgr`

#### 模板参数
- `Key`：数据库连接的键类型（如标识符、名称等）。
- `Conn`：数据库连接类型。
- `Accesser`：数据库访问器类型，默认为 `database_accesser`。
- `InUserData`：输入用户数据类型，默认为 `yggr::any`。
- `OutUserData`：输出用户数据类型，默认为 `yggr::any`。

#### 继承关系
- 继承自 `dbs_manager::dbs_mgr`，复用其数据库管理能力。

#### 主要成员类型
- `key_type`、`conn_type`、`init_type`、`accesser_type`、`in_user_data_type`、`out_user_data_type`：类型适配。

#### 构造与析构
- 支持 C++11 可变参数模板构造（或预处理器宏展开的多参数构造），可灵活传递初始化参数。
- 支持通过 `init_type` 直接初始化。
- 析构函数默认。

#### 主要接口（继承自基类）
- `register_command`：注册数据库命令。
- `unregister_command`：注销数据库命令。
- `execute`：执行数据库操作。
- `reconnect`：重连数据库。
- `clear`：清理所有资源。

---

## 技术要点

- **统一管理**：支持多种数据库连接、访问器和用户数据类型，便于统一管理和扩展。
- **命令注册与调度**：支持数据库命令的注册、注销和调度，适合复杂业务逻辑。
- **高兼容性**：通过模板和可变参数，适应不同数据库和业务场景。
- **与上层集成**：可作为数据库访问、调度、异步管理等上层组件的基础。

---

## 适用场景

- 需要统一管理多种数据库连接、支持多种数据类型和自定义访问逻辑的复杂系统。
- 需要事件驱动、命令注册与调度的数据库应用。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细接口用法或示例，请参考基类 `dbs_mgr` 及相关文档。

