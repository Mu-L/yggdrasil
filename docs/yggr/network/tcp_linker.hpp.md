# tcp_linker.hpp

概述
- 提供 `tcp_linker<Config>` 类，作为对底层 TCP socket 与定时器的轻量封装。
- 管理套接字打开/关闭、关闭模式（send/recv/all）、异步连接、socket 选项设置/读取、本地/远端 endpoint 访问与定时器管理。

模板参数
- `Config`：配置类型，必须包含：
  - `protocol_tag_type`（应为 `yggr::network::type_traits::tag_tcp`）
  - `service_type`（io_service / executor context）
  - `protocol_type`（如 `boost::asio::ip::tcp`）
  - `socket_type`, `endpoint_type`, `address_type`, `deadline_timer_type`
  - 静态常量 `E_NOW_IP_VERSION` 与 `is_v4()`/`is_v6()` 等

关键成员类型
- `link_type`：底层 socket 类型。
- `link_init_type`：用于构造 socket 与定时器的 service/初始化对象。

构造与析构
- `tcp_linker(link_init_type& init)`：通过 `init` 初始化内部 `_socket` 与 `_deadline_timer`。
- 析构时会 `timer_cancel()` 并断言 socket 已关闭。

主要 API
- 连接：
  - `connect(const Tuple_Handler& handler)`：当 socket 未打开时按 IPv4/IPv6 打开对应协议并调用 `async_connect`。
- 关闭与关闭子功能：
  - `close()`：取消定时器、shutdown、close，并处理异常（转为 `exception::exception`）。
  - `shut_down_all()`, `shut_down_send()`, `shut_down_recv()`：分别调用 `_socket.shutdown(...)`。
- socket 选项：
  - `set_option(opt)`：对满足 `is_settable_socket_option` 的类型调用 `_socket.set_option`，并捕获异常；也支持传入 handler（函数对象）进行自定义设置。
  - `get_option(opt)`：类似地获取选项或使用 handler 回调。
- 地址/端口/endpoint 访问器：
  - `is_open()`, `local_endpoint()`, `localhost_endpoint()`, `remote_endpoint()`, 以及 `local_address()` / `remote_address()` / `local_port()` / `remote_port()`。
  - `*_socket_info()` / `str_*()` 等转换为便于显示或上层使用的类型（地址/端口字符串、`Socket_Info` 类型等）。
  - 注意 `localhost_endpoint()` 会解析主机名并匹配 IPv4/IPv6 与本地 socket 的地址族。
- 定时器：
  - `expires_at_timer_wait`, `expires_from_now_timer_wait`：分别设置到期时间并 `async_wait`。
  - `timer_cancel()`, `timer_finish()`：取消或设置为永远到期。
  - `deadline_timer()`：返回内部定时器引用。
- 访问底层：
  - `get_link()`, `get_service()`, `get_init_object()`：直接访问内部 socket、服务与初始化对象。

异常处理
- 对 boost 异常与 STL 异常进行捕获并通过 `exception::exception::throw_error` 转换，使用 `system_controller::system_code::E_TCP_BASE_NETWORK_SYSTEM` 作为系统码。

实现细节与注意
- 使用 `boost::enable_shared_from_raw` 以便从裸指针创建 shared_ptr（注意用法场景）。
- `is_v4()`/`is_v6()` 通过 `Config` 静态方法/常量决定。
- `set_option` / `get_option` 使用 type_traits (`is_settable_socket_option` / `is_gettable_socket_option`) 来区分选项类型与 handler 回调重载。
- `localhost_endpoint()` 在不同 Boost.Asio 版本中分别使用 `get_io_service()` 或 `get_executor()` 获取 resolver。
- `update_remote_endpoint` 返回 `false`（未实现，保留占位）。

示例（伪代码）

```cpp
typedef tcp_linker<MyConfig> my_linker;
my_linker linker(io_service);
linker.connect(boost::make_tuple(endpoint, handler));
linker.set_option(boost::asio::socket_base::reuse_address(true));

// 设置定时器
linker.expires_from_now_timer_wait(boost::posix_time::seconds(5),
	[](const boost::system::error_code&){ /* timeout */ });
```

文件
- 源文件：`tcp_linker.hpp`（请参阅实现以获取版本特定细节与异常处理逻辑）。

----
自动生成：基于 yggr/network/tcp_linker.hpp 的概要文档。