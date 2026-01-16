# udp_linker.hpp

概述
- 提供 `udp_linker<Config>` 类（以及内部 `detail::udp_linker_link_c<Config>`），用于封装 UDP socket 的基本操作与定时器管理。
- 支持保存/更新远端 endpoint、本地/本机地址解析、socket 选项设置/获取、shutdown/close、定时器控制，以及一个可选的 socket 销毁回调。

模板参数
- `Config`：配置类型，必须包含 `service_type`、`protocol_type`、`socket_type`、`endpoint_type`、`address_type` 和 `deadline_timer_type`，以及 `protocol_tag_type` 为 `tag_udp`。

主要类型
- `detail::udp_linker_link_c<Config>`：内部包装，包含对 `socket_type` 的引用与可安全更新的远端 `endpoint`。
- `link_type`：上面的内部包装类型。
- `socket_destroyer_type`：`boost::function1<void, socket_type&>`，可提供自定义销毁逻辑（例如在析构时释放底层资源）。

构造与析构
- 多种构造函数：支持仅传 `socket`、`socket+endpoint`，以及可附带 `socket_destroyer` 回调的构造。
- 析构时会取消定时器并调用 `_socket_destroyer`（若已设置）。

主要 API
- `connect(const endpoint_type& ep)`：设置要发送/接收的远端 endpoint（不发起连接，因为 UDP 无需建立连接）。
- `set_option` / `get_option`：与 socket option 相关的设置/获取接口，支持 option 类型或 handler 回调。
- `shut_down_all` / `shut_down_send` / `shut_down_recv` / `close`：shutdown/close 操作（包装 `_link` 的实现并捕获异常）。
- 地址/端口/endpoint 访问：`local_endpoint`, `localhost_endpoint`, `remote_endpoint`, `local_address`/`remote_address` 等及其字符串/Socket_Info 转换。
- `update_remote_endpoint(const endpoint_type& ep)`：更新远端 endpoint 并返回 true。
- 定时器：`expires_at_timer_wait`, `expires_from_now_timer_wait`, `timer_cancel`, `timer_finish`, `deadline_timer`。
- 底层访问：`get_link()`, `get_service()`, `get_init_object()`, `get_socket_destroyer()`, `clear_socket_destroyer()`。

异常处理
- 捕获 `boost::system::system_error` 与 STL 异常并通过 `exception::exception::throw_error` 转换，使用 `system_controller::system_code::E_UDP_BASE_NETWORK_SYSTEM`（或在定时器相关处使用 TCP 常量，源文件如此实现）。

实现细节与注意
- `detail::udp_linker_link_c` 使用 `safe_wrap` 来存储远端 endpoint，使更新/读取线程安全。
- `localhost_endpoint()` 使用 DNS resolver 解析本机主机名并匹配地址族（IPv4/IPv6）。
- `udp_linker` 非拷贝、非移动（继承 `noncopyable` 与 `nonmoveable`）。
- `socket_destroyer_type` 是可选的，适用于需要在析构时执行自定义清理逻辑的场景。
- 代码中存在对 Boost.Asio 版本的条件编译分支以适配不同接口（`get_io_service()` vs `get_executor()`）。

示例（伪代码）

```cpp
typedef udp_linker<MyConfig> my_udp_linker;
my_udp_linker l(sock);
l.connect(remote_ep); // 设置 remote endpoint
l.set_option(boost::asio::socket_base::broadcast(true));

l.expires_from_now_timer_wait(boost::posix_time::seconds(3),
	[](const boost::system::error_code&){ /* timeout handler */ });
```

文件
- 源文件：`udp_linker.hpp`（参见实现以获取异常处理与版本分支细节）。

----
