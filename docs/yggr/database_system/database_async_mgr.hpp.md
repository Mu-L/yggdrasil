---
`database_async_mgr.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::database_async_mgr` 模板类，是一个通用的异步数据库管理器，基于 `dbs_manager::async_dbs_mgr` 实现。它支持多种数据库连接类型、访问器、用户自定义数据和线程配置，适用于需要异步数据库操作的高性能场景。

---

## 命名空间

- `yggr::database_system`

---

## 主要类型

### 1. `basic_db_notify` / `db_notify`
- 说明：直接使用 `dbs_manager` 命名空间下的通知类型，便于数据库操作的事件通知和回调。

### 2. `database_async_mgr` 模板类

#### 模板参数
- `Key`：数据库连接的键类型（如标识符、名称等）。
- `Conn`：数据库连接类型。
- `Accesser`：数据库访问器类型，默认为 `database_accesser`。
- `InUserData`：输入用户数据类型，默认为 `yggr::any`。
- `OutUserData`：输出用户数据类型，默认为 `yggr::any`。
- `Thread_Config`：线程配置类型，默认为 `thread::boost_thread_config_type`。

#### 继承关系
- 继承自 `dbs_manager::async_dbs_mgr`，复用其异步管理能力。

#### 主要成员类型
- `key_type`：键类型。
- `conn_type`：连接类型。
- `accesser_type`：访问器类型。
- `in_user_data_type` / `out_user_data_type`：用户数据类型。
- `init_type`：初始化参数类型。

#### 构造与析构
- 支持 C++11 可变参数模板构造（或预处理器宏展开的多参数构造），可灵活传递初始化参数。
- 支持通过 `init_type` 直接初始化。
- 析构函数默认。

#### 主要接口（继承自基类）
- `async_execute`：异步执行数据库操作。
- `start`：启动异步管理器。
- `is_running`：判断管理器是否正在运行。
- `stop`：停止异步管理器。
- `join`：等待所有线程结束。
- `clear_notify`：清除所有通知。
- `clear`：清理所有资源。

---

## 技术要点

- **异步管理**：通过线程池或异步任务队列，实现数据库操作的异步化，提升并发性能。
- **高度可配置**：支持自定义连接类型、访问器、用户数据和线程模型，适应多种业务场景。
- **事件通知**：集成通知机制，便于任务完成、异常等事件的回调处理。
- **兼容 C++11 及更早标准**：通过宏和可变参数模板兼容不同编译环境。

---

## 适用场景

- 需要高并发、异步数据库访问的服务端或中间件系统。
- 需要统一管理多种数据库连接、支持多种数据类型和自定义访问逻辑的复杂系统。
- 需要事件驱动、任务队列等异步处理机制的数据库应用。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细接口用法或示例，请参考基类 `async_dbs_mgr` 及相关文档。

