---
`basic_database_accesser.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::basic_database_accesser` 类及其相关辅助结构，主要用于对数据库的基本访问操作（如增删改查、SQL执行等）进行统一封装和异常处理。该类为数据库访问提供了模板化的静态方法，支持多种容器和自定义处理器，便于扩展和适配不同数据库实现。

---

## 命名空间

- `yggr::database_system`
- `yggr::database_system::detail`

---

## 主要结构与类

### 1. `keep_connect_helper`
- 作用：确保数据库连接处于连接状态，若未连接则尝试重连，并处理异常。
- 用法：作为连接操作的前置检查。

### 2. `connection_using_handler_helper<Ret>`
- 作用：模板结构体，封装了“安全地获取连接、执行处理器、异常处理、归还连接”的完整流程。
- 特化版本支持 `void` 返回类型。

### 3. `basic_database_accesser`
- 主要功能：提供一组静态模板方法，支持数据库的 select、insert、update、delete、execute_sql 等操作。
- 设计特点：
  - 所有操作均通过模板参数适配不同的连接类型、数据容器和数据类型。
  - 支持自定义数据处理器（如 handler_val_maker）以适配复杂的数据转换需求。
  - 内部统一处理连接的获取、异常捕获、连接归还、事务提交/回滚等细节，简化上层调用。
  - 提供了事务相关的私有辅助方法（commit/rollback）。

---

## 主要接口说明

### 连接管理
- `s_org_keep_connect`：确保连接可用，必要时自动重连。

### 查询操作
- `s_org_select_records_of_view`：从数据库视图中查询数据，支持自定义数据类型和处理器。

### 插入操作
- `s_org_insert_records_of_table`：向数据库表插入数据，支持批量插入和自定义数据转换。

### 更新操作
- `s_org_update_records_of_table`：更新数据库表中的数据，支持批量和自定义处理。

### 删除操作
- `s_org_delete_records_of_table`：删除数据库表中的数据，支持批量和自定义处理。

### SQL 执行
- `s_org_execute_sql`：直接执行 SQL 语句，支持事务控制。

### 通用处理器调用
- `s_org_connection_using_handler`：以安全方式获取连接并执行自定义处理器，自动处理异常和连接归还。

---

## 错误处理

- 所有操作均通过 `dtl_error` 类型返回详细错误信息，便于上层捕获和处理。
- 支持自动回滚和提交事务，保证数据一致性。

---

## 适用场景

- 需要对数据库进行统一、类型安全、异常安全的访问封装时。
- 适用于多种数据库连接池、数据类型和容器的场景。
- 便于扩展和适配不同数据库实现。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细接口用法或示例，请参考具体函数模板定义及注释。

