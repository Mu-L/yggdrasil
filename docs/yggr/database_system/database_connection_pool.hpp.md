---
`database_connection_pool.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::database_connection_pool` 类，实现了数据库连接池的基本功能。该类负责统一管理数据库连接对象的创建、复用、回收与线程安全访问，支持多字符集和分配器，适用于高并发、跨平台的数据库应用场景。

---

## 命名空间

- `yggr::database_system`

---

## 主要类

### `database_connection_pool`

#### 主要成员类型
- `conn_type`：底层数据库连接类型（如 `dtl::DBConnection`）。
- `org_conn_ptr_type`：连接对象的智能指针类型。
- `connection_type`：封装的数据库连接类型。
- `init_type`：连接初始化参数类型（`database_connection_init`）。
- `init_wrap_type`：线程安全的连接初始化参数包装。
- `conn_queue_type`：线程安全的连接队列。

#### 主要成员变量
- `_init_wrap`：线程安全的连接初始化参数。
- `_conn_queue`：线程安全的连接对象队列。

#### 主要接口

- **构造与析构**
  - 支持多字符集DSN、提示、自动提交等参数初始化。
  - 禁止拷贝和移动。

- **连接池操作**
  - `push(const org_conn_ptr_type&)`：回收连接对象到池中（校验DSN和自动提交参数）。
  - `pop()`：从池中获取一个连接对象。
  - `clear()`：清空连接池。
  - `empty()`：判断连接池是否为空。
  - `operator bool()`：判断连接池是否有效。

- **连接信息访问**
  - `gen_connection(connection_type&)`：生成新的连接对象。
  - `dns_string()`/`dns_string(const Alloc&)`/`dns_string(const string&)`：获取DSN字符串，支持多字符集和分配器。
  - `connect_info()`：获取当前连接初始化参数。

---

## 技术要点

- **线程安全**：通过 `safe_wrap` 和 `safe_queue` 实现多线程安全的参数和连接管理。
- **连接复用**：通过队列实现连接对象的复用，减少频繁创建销毁的开销。
- **参数校验**：回收连接时校验DSN和自动提交参数，保证连接池一致性。
- **多字符集支持**：DSN字符串支持多字符集转换，适应国际化需求。
- **分配器兼容**：支持自定义分配器，便于与STL容器集成。

---

## 适用场景

- 需要高并发、线程安全数据库连接复用的服务端或中间件系统。
- 需要支持多字符集、跨平台数据库访问的项目。
- 需要灵活管理数据库连接生命周期和参数的场景。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法，请参考构造函数、成员函数及相关类型定义。

