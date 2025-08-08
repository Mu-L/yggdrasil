---
# 文件：client_config_template.hpp

## 简介

本头文件为 Yggdrasil 项目中的客户端配置模板，提供了统一的客户端配置结构和错误码定义方式。通过宏和模板，便于扩展和复用，适用于多种客户端类型的配置需求。

## 版权声明

- 作者：xu yang
- 版权归 yggdrasil 所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件保护

使用宏 `__YGGR_CLIENT_CLIENT_CONFIG_CLIENT_CONFIG_TEMPLATE_HPP__` 防止头文件重复包含。

### 依赖

- Yggdrasil 基础定义头文件 `yggrdef.h`
- 错误码生成相关头文件 `error_make.hpp`
- 异常处理相关头文件 `exception.hpp` 和 `exception_sort.hpp`

### 命名空间

所有内容均位于 `yggr::client::client_config` 命名空间下。

### 宏定义

#### `YGGR_PP_CLIENT_CONFIG_TEMPLATE_DECL(__name__, Tag)`

- 用于快速声明一个带有错误码定义和消息的客户端配置结构体。
- 包含类型标签 `tag_type`，以及一组与客户端处理相关的错误码和对应的错误消息。

### 模板类

#### `template<typename Tag> struct client_config_template`

- 泛型客户端配置模板，`Tag` 用于标识配置类型。
- 内部定义了一组与客户端处理相关的错误码（如无效访问、无效主机和端口、空连接、连接分配内存不足、无效客户端等）。
- 每个错误码都配有对应的错误消息，便于异常处理和调试。

### 错误码定义

- 错误码范围由 `exception::exception_sort::E_code_start_3` 到 `E_code_end_3`。
- 支持的错误码包括：
  - `E_invalid_access`：无效访问
  - `E_invalid_host_and_port`：无效主机和端口
  - `E_empty_conn`：空连接
  - `E_invalid_conn_alloc`：连接分配内存不足
  - `E_invalid_client`：无效客户端

### 适用场景

该文件适用于需要统一管理和扩展客户端配置及错误处理的场景，便于后续维护和多客户端类型的支持。

---



