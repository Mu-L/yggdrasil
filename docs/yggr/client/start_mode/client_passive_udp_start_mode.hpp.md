---
# 文件：client_passive_udp_start_mode.hpp

## 简介

本头文件定义了 Yggdrasil 项目中客户端被动 UDP 启动模式的策略类模板 `client_passive_udp_start_mode`，用于在 UDP 客户端场景下，处理连接建立后的数据接收、会话创建、对象移动与交换等逻辑。该模式适用于服务端主动推送数据的 UDP 场景。

## 版权声明

- 作者：xu yang
- 版权归 yggdrasil 所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件保护

使用宏 `__YGGR_CLIENT_START_MODE_CLIENT_PASSIVE_UDP_START_MODE_HPP__` 防止头文件重复包含。

### 依赖

- Yggdrasil 基础定义、网络相关类型、字节序转换
- 移动语义与对象交换工具
- 元编程与类型萃取工具
- Boost.Asio、Boost 类型萃取
- C 断言

### 命名空间

所有内容均位于 `yggr::client::start_mode` 命名空间下，并提供 `swap` 支持到 `std` 和 `boost` 命名空间。

### 类模板

#### `template<typename Recv_Packet, typename Start_Data_Generator, typename Session_Creator> struct client_passive_udp_start_mode`

- **模板参数说明**：
  - `Recv_Packet`：接收数据包类型
  - `Start_Data_Generator`：启动数据生成器类型
  - `Session_Creator`：会话创建器类型

- **主要成员类型**：
  - `recv_packet_type`：接收包类型
  - `start_data_generator`：启动数据生成器
  - `session_creator_type`：会话创建器
  - `start_data_type`：启动数据类型（由生成器定义）

- **构造与移动/拷贝支持**：
  - 支持默认、拷贝、移动构造与赋值
  - 支持 `swap` 操作，便于高效对象管理

- **主要成员函数**：
  - `operator()(ConnPtr pconn, Session_Mgr& smgr) const`  
    入口操作符，处理新连接，调用私有辅助函数进行后续处理。
  - `prv_create_helper(ConnPtr pconn, Session_Mgr_Ptr psmgr, recv_packet_type& pak)`  
    辅助函数，校验类型和指针有效性，生成启动数据，创建会话并启动。
  - `swap`  
    支持与其他同类型对象高效交换内部数据。

- **类型安全与断言**：
  - 使用 `BOOST_MPL_ASSERT` 静态断言，确保会话管理器类型标签为 `tag_client`。
  - 运行时断言和空指针检查，保证健壮性。

- **成员变量**：
  - `mutable recv_packet_type _pak;`  
    存储用于启动的接收包对象。

### swap 支持

- 提供 `swap` 函数模板，支持标准库和 Boost 的 `swap` 调用，便于容器和算法的高效操作。

### 适用场景

该文件适用于需要被动接收 UDP 数据并自动管理会话生命周期的客户端场景，便于实现高效、类型安全的网络通信逻辑，特别适合需要对象移动和高效交换的场合。

---



