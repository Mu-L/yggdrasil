# `yggr::network::network_config::balance_tcp*_config`（文件：`network_balance_tcp_config.hpp`）

## 概述
- 目的：提供基于负载均衡 I/O 服务的 TCP 网络配置模板别名（IPv4 / IPv6 变体），方便在项目中按统一类型创建 TCP 连接/服务实例。
- 位置：`yggr/network/network_config/network_balance_tcp_config.hpp`（本文档与源文件同目录）。

## 关键点与行为
- 该头文件通过宏 `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL` 或在不使用该宏时通过 `typedef` 声明两个配置类型：
  - `balance_tcpv4_config`：面向 IPv4 的 TCP 配置。
  - `balance_tcpv6_config`：面向 IPv6 的 TCP 配置（在 `typedef` 分支为 `ip_ver::E_IPV6`）。
- 配置模板使用的参数包括：
  - 协议标签：`yggr::network::type_traits::tag_tcp`。
  - I/O 服务类型：`balance_io_service<boost::asio::io_service>`（一个封装的、支持负载均衡的 io_service）。
  - 套接字/地址类型：`boost::asio::ip::tcp` / `boost::asio::ip::address`。
  - 定时器类型：`boost::asio::deadline_timer`。
  - IP 版本：`ip_ver::E_IPV4` 或 `ip_ver::E_IPV6`。

## 源码结构说明
- 两种声明路径：
  1. 当未定义 `YGGR_TPL_CONFIG_USING_TPL` 时，文件使用 `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL(...)` 宏来声明配置类型；宏的具体展开由项目预处理器定义，通常用于减少模板重复声明或生成额外导出内容。
  2. 当定义 `YGGR_TPL_CONFIG_USING_TPL` 时，文件直接通过 `typedef network_config_template<...> balance_tcpv4_config;` 形式给出具体别名。

- 注意：在宏分支中，第二个 `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL`（用于 `balance_tcpv6_config`）的最后一个参数也写成 `ip_ver::E_IPV4`，这很可能是写错了（应为 `ip_ver::E_IPV6`）。而在 `typedef` 分支中，`balance_tcpv6_config` 使用了正确的 `ip_ver::E_IPV6`。建议检查/修正宏分支的参数以避免配置错误。

## 使用示例（伪代码）
```cpp
// 以 typedef 分支为例：
using cfg = yggr::network::network_config::balance_tcpv4_config;

cfg::link_init_type init = /* 构造或配置初始化参数 */;

// 在项目中使用 cfg 创建服务/客户端/连接器，
// 依赖于 network_config_template 定义的接口（如 socket_type、service_type 等）。
```

## 兼容性与注意事项
- `balance_io_service<boost::asio::io_service>` 是项目提供的可用于负载均衡的 I/O 服务封装；请确认其与 Boost.Asio 版本的兼容性（某些 Asio 版本使用 executor/contexts 替代旧 `io_service`）。
- 如果项目在不同平台或不同 Boost 版本之间切换，请确保 `ip_ver` 与 `address` / `endpoint` 类型的匹配正确（IPv6 下地址类型与 endpoint 行为会有所差异）。
- 强烈建议修复宏分支中 `balance_tcpv6_config` 的 `ip_ver` 参数（从 `E_IPV4` 修正为 `E_IPV6`），否则在使用宏分支时会导致 v6 配置实际上仍然使用 IPv4 常量。

