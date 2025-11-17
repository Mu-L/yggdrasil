# `yggr::network::network_config::udpv*_config`（文件：`network_udp_config.hpp`）

## 概述
- 目的：为项目提供基于 Boost.Asio 的 UDP 配置别名（IPv4 / IPv6），便于统一声明 socket/endpoint/service/定时器等类型。
- 位置：`yggr/network/network_config/network_udp_config.hpp`（本文档与源文件同目录）。
- 说明：文件通过宏 `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL`（或在启用 `YGGR_TPL_CONFIG_USING_TPL` 时通过 `typedef network_config_template<...>`）声明 `udpv4_config` 与 `udpv6_config` 两个配置类型。

## 关键包含与依赖
- 包含：
  - `yggr/network/socket_conflict_fixer.hpp`（处理平台或构建选项下的 socket 差异与兼容性修正）。
  - `yggr/network/network_config/network_config_template.hpp`（提供 `network_config_template` 与 `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL` 宏）。
  - `yggr/network/type_traits/tags.hpp`（协议标签，例如 `tag_udp`）。
  - `boost/asio.hpp`（用于 socket、endpoint 与定时器等类型）。

## 宏分支与 typedef 路径
- 当未定义 `YGGR_TPL_CONFIG_USING_TPL` 时，使用 `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL` 宏生成两个轻量类：
  - `udpv4_config`：使用 `ip_ver::E_IPV4`。
  - `udpv6_config`：使用 `ip_ver::E_IPV6`。
- 当定义 `YGGR_TPL_CONFIG_USING_TPL` 时，文件通过 `typedef network_config_template<...> udpv4_config;` 与 `udpv6_config;` 明确生成类型别名。

## 导出/可用的类型别名（由宏或模板提供）
通常，`udpv*_config` 会导出以下别名（取决于 `network_config_template`）：
- `protocol_tag_type`（例如 `yggr::network::type_traits::tag_udp`）
- `service_type`（例如 `boost::asio::io_service` 或项目自定义的 `balance_io_service`）
- `protocol_type`、`socket_type`、`endpoint_type`、`address_type`
- `deadline_timer_type`（例如 `boost::asio::deadline_timer`）
- 静态常量：`E_NOW_IP_VERSION` 与 `is_v4()` / `is_v6()` 方法

## 使用示例（伪代码）
```cpp
using cfg4 = yggr::network::network_config::udpv4_config;
using cfg6 = yggr::network::network_config::udpv6_config;

static_assert(cfg4::is_v4(), "cfg4 应为 IPv4");

cfg4::socket_type sock(io_service);
cfg4::endpoint_type ep(cfg4::address_type::from_string("127.0.0.1"), 12345);

// 在创建发送/接收逻辑时使用 cfg4/ cfg6 导出的类型
```

## 注意事项与建议
- `socket_conflict_fixer.hpp` 的包含提示此模块对不同平台的 socket 行为有兼容性处理；在移植或跨平台构建时请先检查该文件的实现。
- Boost.Asio 在不同版本间有 API 变化（例如 `io_service` -> `io_context`、executor/contexts 的引入）；如果项目升级了 Boost，请确认 `service_type` 的传递与使用方式仍然正确。
- 对于 IPv6，注意地址/endpoint 的构造、绑定（如绑定 `::`）以及 socket 选项（如 `v6_only`）；`socket_conflict_fixer` 可能包含相关兼容处理。
- 保持所有 `network_config` 相关文件中 `ip_ver` 参数的一致性，避免因宏分支或笔误把 IPv6 配置误设为 IPv4。

