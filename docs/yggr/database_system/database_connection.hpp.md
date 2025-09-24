---
`database_connection.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::database_connection` 类及其内部容器，负责封装和管理单个数据库连接对象的生命周期、线程安全访问、初始化、复用等操作。该类是数据库连接池、数据库访问器等上层组件的基础，支持多字符集、智能指针、线程安全和高效资源管理。

---

## 命名空间

- `yggr::database_system`
- `yggr::database_system::detail`
- `yggr::database_system::swap_support`

---

## 主要类

### 1. `detail::database_connection_container`

- 封装了数据库连接对象（`dtl::DBConnection`）的智能指针和状态。
- 支持拷贝、移动、swap、线程安全访问。
- 提供 `push`/`pop` 机制，实现连接对象的复用与回收。
- 支持通过 handler 方式安全访问底层连接对象。

### 2. `database_connection`

- 封装了线程安全的数据库连接容器（`safe_wrap<database_connection_container>`）。
- 禁止拷贝和移动，保证连接对象唯一性。
- 支持多字符集DSN、提示、自动提交等参数初始化。
- 提供 `push`/`pop`/`init`/`clear` 等接口，便于连接池和访问器统一管理。
- 支持 handler 方式安全访问底层连接对象，便于自定义操作和异常处理。
- 提供唯一ID（指针转整型）用于标识连接对象。
- 提供 swap 支持，便于容器操作和性能优化。

---

## 技术要点

- **线程安全**：通过 `safe_wrap` 实现多线程安全的连接对象管理。
- **资源复用**：`push`/`pop` 机制支持连接对象的高效复用，减少频繁创建销毁的开销。
- **handler访问**：通过 handler 方式安全访问底层连接，便于扩展和自定义操作。
- **多字符集支持**：支持多字符集DSN，适应国际化和多数据库环境。
- **swap友好**：提供标准和boost命名空间下的swap重载。

---

## 适用场景

- 需要高效、线程安全管理数据库连接对象的服务端或中间件系统。
- 需要与连接池、访问器等上层组件协同工作的数据库基础设施。
- 需要支持多字符集、跨平台数据库访问的项目。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法，请参考构造函数、成员函数及swap相关实现。

