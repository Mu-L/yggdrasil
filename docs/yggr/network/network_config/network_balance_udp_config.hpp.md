# `yggr::network::network_config::balance_udp*_config`（文件：`network_balance_udp_config.hpp`）

## 概述
- 目的：为基于负载均衡 I/O 服务的 UDP 提供配置别名（IPv4 / IPv6），便于在项目中统一创建 UDP 连接/服务实例。
- 位置：`yggr/network/network_config/network_balance_udp_config.hpp`（本文件与源文件同目录）。
- 适用场景：需要以项目提供的 `balance_io_service` 为基础，在不同 IP 版本下构建 UDP 套接字/服务时使用统一的配置类型别名。

## 关键包含与依赖
- 包含：
  - `yggr/network/socket_conflict_fixer.hpp`（用于处理平台/选项下的 socket 冲突或特定修正）。
  - `yggr/network/network_config/network_config_template.hpp`（配置模板定义）。
  - `yggr/network/balance_io_service.hpp`（负载均衡 I/O 服务实现）。
  - `yggr/network/type_traits/tags.hpp`（协议标签，如 `tag_udp`）。
  - `boost/asio.hpp`（Boost.Asio 的通用包含，文件中用于 `boost::asio::ip::udp` / 定时器等）。

## 宏分支与 typedef 路径
- 文件通过两种方式声明配置类型：
  1. 当未定义 `YGGR_TPL_CONFIG_USING_TPL` 时，使用 `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL(...)` 宏分别声明：
     - `balance_udpv4_config`（带 `ip_ver::E_IPV4`）
     - `balance_udpv6_config`（带 `ip_ver::E_IPV6`）
  2. 当定义 `YGGR_TPL_CONFIG_USING_TPL` 时，直接用 `typedef network_config_template<...> balance_udpv4_config;` 和 `balance_udpv6_config;` 来声明。

- 与 TCP 相似，UDP 的 `typedef` 分支在文件中明确使用了 `ip_ver::E_IPV4` 与 `ip_ver::E_IPV6`。宏分支的两个 `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL` 在本文件中也分别传入了正确的 `ip_ver` 值（注意：在 TCP 的宏分支中曾出现写错的情况，这里并未看到类似错误）。

## 导出的类型（由 template 提供）
虽然本文件只是声明/别名模板实例，但 `network_config_template` 通常会导出以下类型/别名（具体取决于模板实现）：
- `socket_type`（例如 `boost::asio::ip::udp::socket`）
- `endpoint_type` / `address_type`
- `service_type`（例如 `balance_io_service<boost::asio::io_service>`）
- `deadline_timer_type`（`boost::asio::deadline_timer`）
- `link_init_type` / `link_type` 等用于上层组件构造

## 使用示例（伪代码）
```cpp
// 以 typedef 分支为例：
using cfg4 = yggr::network::network_config::balance_udpv4_config;
using cfg6 = yggr::network::network_config::balance_udpv6_config;

cfg4::link_init_type init4 = /* 构造 IPv4 初始化参数 */;

// 创建并使用 cfg4 所定义的 service / socket / endpoint 等
```

## 注意事项与建议
- `socket_conflict_fixer.hpp` 的包含表明该模块需要在不同平台或特定构建选项下处理 socket 相关差异；若你在移植到新平台或使用不同编译器/选项，请先查看 `socket_conflict_fixer` 的实现以确认行为。
- `balance_io_service` 抽象了 `io_service`（或在新 Asio 中为 executor/context）；请确认当前项目的 Boost.Asio 版本与 `balance_io_service` 的实现是否匹配（例如 `io_service` vs `io_context` / executor 接口差异）。
- IPv6 使用时注意地址/endpoint 的构造与绑定规则（例如绑定通配符地址 `::`、是否设置 `v6_only` socket option 等）。`socket_conflict_fixer` 可能对这些选项做了兼容处理。

