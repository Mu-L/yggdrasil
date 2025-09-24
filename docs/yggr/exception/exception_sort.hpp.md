---
exception_sort.hpp 文档

---

# exception_sort.hpp

## 简介

该头文件为 Yggdrasil 框架定义了统一的异常错误码区间和常量。通过分段的错误码区间，便于不同模块、不同类型的异常进行分类、管理和扩展，保证错误码的唯一性和可追踪性。

## 主要内容

### 命名空间

- `yggr::exception`：主命名空间，包含所有异常相关定义。

### 核心类

#### `exception_sort`

用于定义和管理错误码区间及特殊错误码常量。

**主要内容：**
- 25个错误码区间（`E_code_start_1` ~ `E_code_end_25`），每个区间长度为0x1000，便于模块分配。
- 特殊错误码常量：
  - `E_code_stl_error`：标准库异常错误码
  - `E_code_dtl_db_error`：DTL相关错误码
  - `E_code_dtl_root_error`：DTL_ROOT错误码
  - `E_code_luabind_error`：Lua 绑定相关错误码
  - `E_code_runtime_error`：运行时错误码
  - `E_code_seh_error`：结构化异常处理错误码
  - `E_code_user_error`：用户自定义错误码

### 典型用法

- 用于异常与错误码的映射、分类、日志记录等场景。
- 结合 `error_code` 类和 `error_code_maker` 工具，实现跨模块、跨平台的统一错误处理。

### 依赖

- Yggdrasil 基础库（类型定义、静态常量工具）

## 版权声明

MIT License，2010-2024。

---



