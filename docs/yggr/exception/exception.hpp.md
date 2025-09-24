---
exception.hpp 文档

---

# exception.hpp

## 简介

该头文件为 Yggdrasil 框架提供了统一的异常处理与日志记录机制。核心类 `yggr::exception::exception` 支持错误码收集、日志访问器绑定、线程安全队列、异常分发与处理等功能，适用于分布式、高并发系统的异常管理。

## 主要内容

### 命名空间

- `yggr::exception`：主命名空间，包含所有异常相关定义。
- `yggr::exception::detail`：内部实现细节。

### 主要类与模板

#### `exception_basic_log_helper`（抽象基类）

- 定义日志访问器的基础接口，要求实现 `append(const error_code&)` 方法。

#### `exception_log_helper<Accesser, StoreConverter=void>`

- 日志访问器适配器，支持自定义存储转换器，将 `error_code` 转换为存储格式并写入外部存储。

#### `exception`

- 异常管理核心类，负责收集、分发、处理错误码。
- 支持多线程安全队列、日志访问器绑定、异常投递与修正、异常输出等。
- 提供静态 `throw_error` 方法，支持多参数、变参模板，便于灵活抛出和记录异常。
- 支持与 `system_controller::ctrl_center` 协作，实现异常的自动修正与处理。

### 典型用法

```cpp
// 抛出并记录异常
yggr::exception::exception::throw_error(1001, "file not found");

// 绑定日志访问器
auto log_ptr = std::make_shared<MyLogAccesser>();
yggr::exception::exception ex;
ex.bind_log_accesser(log_ptr);
```

### 依赖

- Yggdrasil 基础库（线程、时间、智能指针、字符集、容器等模块）
- Boost 库（atomic、线程等）

### 设计亮点

- 支持多线程安全的异常队列
- 支持自定义日志访问器和存储格式
- 支持异常自动修正与分发
- 兼容多字符集和多平台

## 版权声明

MIT License，2010-2024。

---

