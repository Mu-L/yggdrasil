# `yggr::network::network_config::network_config_template`（文件：`network_config_template.hpp`）

## 概述
- 目的：提供一个可复用的网络配置模板 `network_config_template`，以及一个用于快速声明配置的宏 `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL`。该模板用于在项目中声明基于不同协议（TCP/UDP）、IP 版本（IPv4/IPv6）与 I/O 服务的配置别名。
- 位置：`yggr/network/network_config/network_config_template.hpp`（本文档与源文件同目录）。
- 适用场景：以类型别名或宏声明的方式统一描述网络协议类型（socket/endpoint/地址/定时器等），便于在不同模块间共享配置定义。

## 主要定义
### `struct ip_ver`
- 常量：
  - `E_IPV4` = `PF_INET`
  - `E_IPV6` = `PF_INET6`
- 提供静态方法：`v4()` / `v6()` 返回对应常量。
- 用途：作为模板参数或宏参数传递当前配置的 IP 版本。

### 宏：`YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL(__name__, Protocol_Tag, Service, Protocol, Address, DeadLineTimer, V)`
- 作用：为减轻编译器模板解析的内存压力（并避免复杂模板实例化），使用宏声明一个轻量的配置类 `class __name__`，该类包含：
  - 静态常量 `E_NOW_IP_VERSION = V`。
  - 别名：`protocol_tag_type`, `service_type`, `protocol_type`, `socket_type`, `endpoint_type`, `address_type`, `deadline_timer_type`。
  - 使用 Boost.MPL 生成 `is_v4_type` / `is_v6_type`，并提供 `is_v4()` / `is_v6()` 静态方法。
- 用法示例（宏展开等价）：
  - `YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL(balance_tcpv4_config, tag_tcp, balance_io_service<...>, boost::asio::ip::tcp, boost::asio::ip::address, boost::asio::deadline_timer, ip_ver::E_IPV4)`
  - 生成的 `balance_tcpv4_config` 类具有 `socket_type`、`endpoint_type` 等可供上层使用。

### 模板类：`template<typename Protocol_Tag, typename Service, typename Protocol, typename Address, typename DeadLineTimer, u32 V> class network_config_template`
- 提供同宏相同的别名与静态常量 `E_NOW_IP_VERSION`、`is_v4_type` / `is_v6_type`，并实现 `is_v4()` / `is_v6()` 方法。
- 推荐在需要完整模板功能或在启用 `YGGR_TPL_CONFIG_USING_TPL` 宏时使用 `typedef network_config_template<...> name;` 来定义配置别名。

### Socket 类型检查宏
- 在文件末尾有两处宏：
  - `YGGR_PP_SOCKET_TYPE_CHECKER_DEF(boost::asio::ip::tcp::socket, yggr::network::type_traits::tag_tcp)`
  - `YGGR_PP_SOCKET_TYPE_CHECKER_DEF(boost::asio::ip::udp::socket, yggr::network::type_traits::tag_udp)`
- 这些宏用于在编译期/静态分析中绑定 socket 类型与协议标签，帮助类型检查与静态断言。

## 使用建议与示例
- 通过宏声明的轻量类（`YGGR_PP_NETWORK_CONFIG_TEMPLATE_DECL`）适合在头文件中频繁使用以减少编译器模板实例化负担。
- 通过 `network_config_template` 生成的 `typedef` 更利于调试与浏览器友好（IDE 能更好地显示模板成员）。

示例：
```cpp
// 宏或 typedef 分支均可：
using cfg_v4 = yggr::network::network_config::balance_tcpv4_config;
static_assert(cfg_v4::is_v4(), "should be v4");

cfg_v4::socket_type sock(io_service);
cfg_v4::endpoint_type ep(cfg_v4::address_type::from_string("127.0.0.1"), 8080);
```

## 兼容性与注意事项
- `Service` 参数通常为 `balance_io_service<boost::asio::io_service>`（或在新 Asio 里以 executor/context 风格封装的类型）；当项目迁移到较新 Boost.Asio（`io_context`/executor）时，需确保 `Service` 的接口兼容性。
- `ip_ver` 使用底层平台常量 `PF_INET` / `PF_INET6`，在某些平台或交叉编译场景中请确认这些常量的可用性。
- 宏方式与模板方式应保持语义一致：如果你在多个配置头使用宏声明，请检视参数是否传错（例如把 `ip_ver::E_IPV4` 错写为 `E_IPV6`）以免引入难以察觉的配置错误。
