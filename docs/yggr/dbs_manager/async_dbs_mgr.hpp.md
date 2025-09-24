---
async_dbs_mgr.hpp 文档

---

## 1. 版权声明与头文件保护

- 文件顶部包含 MIT 许可证声明。
- 使用 include guard 防止重复包含。

## 2. 依赖头文件

- 包含了 YGGR 基础定义、线程、数据库管理、智能指针、安全队列等相关头文件。
- 使用了 Boost 库的原子操作和线程相关功能。

## 3. 命名空间

- 所有内容均在 `yggr::dbs_manager` 命名空间下。

## 4. 通知基类与派生类

### basic_db_notify

- 模板参数：`Runner`, `InUserData`, `OutUserData`
- 作用：定义数据库操作通知的基础接口，包含纯虚函数 `execute()`，用于执行数据库操作。
- 禁止拷贝和移动。

### db_notify

- 模板参数：`Runner`, `Key`, `Handler`, `InUserData`, `OutUserData`
- 作用：继承自 `basic_db_notify`，实现带 key 和 handler 的数据库操作通知，支持带/不带 handler 的特化。

### db_cmd_notify

- 模板参数：`Runner`, `Handler1`, `Handler2`, `InUserData`, `OutUserData`
- 作用：用于命令型数据库操作通知，支持命令执行和后处理 handler。

## 5. async_dbs_mgr（异步数据库管理器）

- 模板参数：`Key`, `Conn`, `Accesser`, `InUserData`, `OutUserData`, `Thread_Config`
- 继承自 `dbs_mgr`，扩展为异步操作。
- 主要成员：
  - `run_state_type _run_state`：运行状态原子变量。
  - `notify_queue_type _notify_queue`：线程安全通知队列。
  - `thread_group_type _trd_group`：线程组。
- 主要方法：
  - `async_execute`：异步执行数据库操作，支持多种参数组合（key、handler、userdata）。
  - `async_run_command`：异步执行命令型数据库操作。
  - `start`：启动指定数量的工作线程，处理异步队列。
  - `stop`/`join`：停止和等待线程结束。
  - `clear_notify`/`clear`：清理通知队列和管理器内容。
  - 内部通过 `prv_handler_run` 和 `prv_handler_execute` 实现异步任务的调度和执行。

---

### 适用场景

- 适用于需要多线程异步处理数据库操作的场景。
- 支持自定义 key、连接、访问器、用户数据类型和线程配置。

---
