---
error_code_maker.hpp 文档

---

# error_code_maker.hpp

## 简介

该头文件为 Yggdrasil 框架提供了异常与错误码的统一转换工具。其核心思想是将不同类型的异常（包括标准库异常、Boost 异常等）转换为统一的 `yggr::exception::error_code` 类型，便于跨模块、跨平台的错误处理和日志记录。

## 主要内容

### 命名空间

- `yggr::exception`：主命名空间，包含所有异常相关定义。
- `yggr::exception::detail`：内部实现细节。

### 结构体与模板

- `yggr_inner_exception_code_def`  
  定义内部异常的错误码常量。

- `detail::root_exception_maker<Err>`  
  模板结构体，将异常类型 `Err` 转换为 `error_code`。对 `std::exception` 和 `boost::system::error_code` 提供了特化。

- `error_code_maker<Err>`  
  通用异常到错误码的转换器。根据异常类型自动选择合适的转换策略。对 `boost::system::system_error` 和 `boost::regex_error` 也有特化。

### 典型用法

```cpp
try {
    // ... 可能抛出异常的代码 ...
} catch (const std::exception& e) {
    yggr::exception::error_code_maker<std::exception> maker;
    auto code = maker(e);
    // 处理 code
}
```

### 支持的异常类型

- 标准库异常（`std::exception` 及其子类）
- Boost 系统错误（`boost::system::error_code`, `boost::system::system_error`）
- Boost 正则表达式错误（`boost::regex_error`）
- 其他自定义异常类型

### 依赖

- Yggdrasil 基础库
- Boost 库（system, archive, regex, mpl, type_traits）

## 版权声明

MIT License，2010-2024。

---



