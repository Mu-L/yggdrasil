---
error_code.hpp 文档

---

# error_code.hpp

## 简介

该头文件定义了 Yggdrasil 框架中用于统一表示错误和异常信息的核心类 `yggr::exception::error_code`。该类支持多字符集、线程安全、时间戳、线程ID等丰富信息，便于跨平台、跨模块的错误追踪和日志记录。

## 主要内容

### 命名空间

- `yggr::exception`：主命名空间，包含所有异常相关定义。

### 核心类

#### `error_code`

用于封装错误码、错误信息、发生时间、线程ID等信息。支持多种构造方式，兼容不同字符串类型和字符集。

**主要成员变量：**
- `_tm`：错误发生的UTC时间戳
- `_trd_id`：线程ID
- `_code`：错误码（`u32`）
- `_msg`：错误信息（UTF-8字符串）

**主要接口：**
- 多种构造函数，支持不同字符串类型、字符集、线程ID等
- `code()`：获取/设置错误码
- `message()`：获取/设置错误信息
- `time()`：获取/设置时间戳
- `thread_id()`：获取/设置线程ID
- `str_time()`：格式化输出时间字符串
- `to_string()`：格式化输出完整错误信息
- 支持拷贝、移动、swap等操作
- 支持流输出（`operator<<`）

### 依赖

- Yggdrasil 基础库（线程、时间、字符串、容器等模块）
- Boost 库（线程、move、enable_if等）

### 典型用法

```cpp
yggr::exception::error_code ec(1001, "file not found");
std::cout << ec.to_string() << std::endl;
```

### 其他

- 提供了 swap 支持，兼容 std/boost 的 swap 机制。
- 支持多字符集和自定义分配器，适合高性能和多语言环境。

## 版权声明

MIT License，2010-2024。

---



