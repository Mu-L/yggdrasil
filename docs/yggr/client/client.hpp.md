---
# 文件：client.hpp

## 简介

本头文件定义了 Yggdrasil 项目中通用的客户端包装类模板 `client`，用于对底层 Handler 进行统一封装，简化客户端对象的构造与生命周期管理。该类支持 C++11 可变参数模板和 Boost 预处理器两种构造方式，兼容不同编译环境。

## 版权声明

- 作者：xu yang
- 版权归 yggdrasil 所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件保护

使用宏 `__YGGR_CLIENT_CLIENT_HPP__` 防止头文件重复包含。

### 依赖

- Yggdrasil 基础定义
- 参数宏工具 `foo_params.hpp`

### 命名空间

所有内容均位于 `yggr::client` 命名空间下。

### 类模板

#### `template<typename Handler> class client`

- **模板参数说明**：
  - `Handler`：底层处理器类型（如 `basic_clt_handler`）

- **主要成员类型**：
  - `base_type`：Handler 类型别名

- **构造与析构**：
  - 支持 C++11 可变参数模板构造，自动转发参数给 Handler
  - 若不支持可变参数模板，则通过 Boost 预处理器宏生成多参数构造函数
  - 析构函数默认

- **成员函数继承**：
  - 公开继承 Handler 的 `join`、`run`、`stop` 等接口，便于直接调用

### 适用场景

该文件适用于需要对底层 Handler 进行统一封装和管理的客户端场景，便于扩展、复用和简化客户端对象的构造与生命周期控制。

---

