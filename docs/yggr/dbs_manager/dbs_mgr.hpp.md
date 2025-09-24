---
dbs_mgr.hpp 文档

---

## 1. 版权声明与头文件保护

- 顶部为 MIT 许可证声明。
- 使用 include guard 防止重复包含。

## 2. 依赖头文件

- 包含 YGGR 基础类型、智能指针、不可拷贝/不可移动特性、any 类型、参数宏、线程安全容器等。
- 使用 Boost 库的 enable_if 等工具。

## 3. 命名空间

- 所有内容均在 `yggr::dbs_manager` 命名空间下。

## 4. 内部命令对象

### dbs_mgr_basic_command

- 模板参数：`Conn`, `InUserData`, `OutUserData`
- 作用：数据库命令的抽象基类，定义了纯虚函数 `execute`，用于执行数据库操作。

### dbs_mgr_command

- 模板参数：`Conn`, `InUserData`, `OutUserData`, `Handler`
- 作用：继承自 `dbs_mgr_basic_command`，实现具体的数据库操作命令，持有 handler 并在 `execute` 时调用。

## 5. dbs_mgr（数据库管理器）

- 模板参数：`Key`, `Conn`, `Accesser`, `InUserData`, `OutUserData`
- 禁止拷贝和移动。
- 主要成员类型：
  - `key_type`：命令 key 类型。
  - `conn_type`：数据库连接类型。
  - `init_type`：连接初始化类型。
  - `accesser_type`：访问器类型。
  - `in_user_data_type`/`out_user_data_type`：输入/输出用户数据类型。
- 主要成员变量：
  - `_conn_wrap`：线程安全数据库连接包装。
  - `_cmd_map`：线程安全命令映射表。
- 主要方法：
  - 构造与析构：支持多参数构造，析构时清理资源。
  - `init`：初始化数据库连接（支持变参模板）。
  - `register_command`/`unregister_command`：注册/注销数据库操作命令，支持 handler 或对象批量注册。
  - `execute`：根据 key 执行已注册的数据库命令，支持多种参数组合（key、输入数据、输出数据）。
  - `run_command`：直接运行 handler，支持多种参数组合。
  - `reconnect`：重连数据库，支持多参数和 init_type。
  - `clear`：清理连接和命令表。

## 6. 适用场景

- 适用于需要统一管理数据库连接和操作命令的场景。
- 支持多线程安全操作，便于扩展和集成到更复杂的异步/分布式系统中。

---
