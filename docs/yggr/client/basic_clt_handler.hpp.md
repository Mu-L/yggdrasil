---
# 文件：basic_clt_handler.hpp

## 简介

本头文件定义了 Yggdrasil 项目中通用的客户端处理器模板类 `basic_clt_handler`，用于管理客户端的网络连接、协议注册、数据收发、会话管理等核心功能。该类高度模块化，支持 TCP/UDP 等多种协议，适用于多种客户端场景。

## 版权声明

- 作者：xu yang
- 版权归 yggdrasil 所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件保护

使用宏 `__YGGR_CLIENT_TCP_CLIENT_HANDLER_HPP__` 防止头文件重复包含。

### 依赖

- Yggdrasil 基础定义、网络相关类型与工具
- 线程、系统控制、智能指针、容器安全封装
- Boost.Asio、类型萃取、断言等

### 命名空间

所有内容均位于 `yggr::client` 命名空间下，部分细节实现位于 `yggr::client::detail`。

### 细节实现

- `client_init`：用于初始化会话管理器和连接处理器的辅助结构体，支持拷贝和移动。
- `check_state_op`：根据协议类型（TCP/UDP）检查会话和连接状态的操作器。

### 主类模板

#### `template<...> class basic_clt_handler`

- **模板参数说明**：
  - `ClientConfig`：客户端配置类型
  - `Service_Handler`：服务处理器类型
  - `SessionMgr`：会话管理器类型
  - `OptionsSetter`：选项设置器类型（默认值）
  - `Connect_Handler`：连接处理器模板（默认 TCP）

- **主要成员类型**：
  - 会话管理器、适配器管理器、连接处理器、协议标签、错误类型等

- **主要成员函数**：
  - `connect`：发起网络连接，支持超时
  - `register_network_protocol`/`unregister_network_protocol`：注册/注销网络协议及适配器
  - `run`/`stop`/`clear`/`clear_sessions`：运行、停止、清理会话
  - `online_size`：获取在线会话数量
  - `send_packet`：发送数据包，支持多种参数组合
  - `access`/`access_of_all`：访问单个或全部会话，支持回调
  - `get_session_mgr`/`get_adapter_mgr_ptr`：获取会话管理器或适配器管理器指针
  - `check_state`：检查当前状态

- **类型安全与断言**：
  - 使用 `BOOST_MPL_ASSERT` 静态断言，确保配置类型与会话管理器类型标签一致
  - 运行时断言和空指针检查，保证健壮性

- **友元与继承**：
  - 禁止拷贝和移动（继承自 `noncopyable` 和 `nonmoveable`）
  - 友元类支持网络处理器和系统控制中心的集成

### 适用场景

该文件适用于需要统一管理客户端网络连接、协议注册、数据收发和会话生命周期的场景，便于实现高效、类型安全、可扩展的客户端通信逻辑。

---



