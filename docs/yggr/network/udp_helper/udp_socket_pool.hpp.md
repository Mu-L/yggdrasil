**udp_socket_pool.hpp 文档**

简介：
- `udp_socket_pool.hpp` 提供了 `udp_socket_pool` 模板类及其内部的 `socket_unit` 实现，用于管理 UDP 套接字池（按使用计数选择/重用 socket），支持并发安全的容器、可选的 socket option 设置与自动回收。

主要类型：
- `detail::socket_unit<Socket, EndPoint, Service>`：
  - 封装单个 socket 实例（`shared_ptr<Socket>`），维护使用计数（`_count`）和唯一 id（基于指针转换）。
  - 提供 `get()`（取出并增加计数）、`back()`（归还并减少计数）、`close()`、`set_option()`（支持可设置的 socket option 或回调）等操作。
  - 支持拷贝/移动与 `swap`。

- `udp_socket_pool<Socket, EndPoint, Service, ver>`：
  - 管理多个 `socket_unit` 的并发容器（`safe_multi_index_container`），索引包括基于 socket id 的哈希唯一索引和基于使用计数的有序非唯一索引。
  - 提供容量限制 `_limit_size`（原子），以及 `get()`、`get(service, ops_setter)`、`back()`、`set_option()`、`close()`、`clear()` 等接口。

设计要点：
- 池中插入策略：当池未满时会新建 `socket_unit` 并插入；当已满时，会用使用计数最小（least-used）的单元替换并复用其 socket，以实现负载均衡。
- `get()` 会返回 `shared_ptr<Socket>`，内部会将该 socket 的使用计数加一；`back()` 通过 socket 指针找到对应单元并递减计数。
- 对 socket option 的设定支持两种方式：传入可设置的 `OptionSetter`（满足 `is_settable_socket_option`）或者传入回调型 `Handler`（通过 `operator()` 自行处理）。
- 容器使用 `safe_multi_index_container` 以保证在多线程环境下的并发安全访问与操作。

重要方法与行为：
- `socket_ptr_type get(service_type& service)`：不带选项的获取；可能新建 socket 或复用已有 socket。
- `template<typename OptionSetter> socket_ptr_type get(service_type& service, const OptionSetter& ops_setter)`：带选项的获取，若新建 socket 则先尝试 `su.set_option(ops_setter)`。
- `void back(socket_ptr_type psocket)`：将 socket 归还池中（通过 id 查找并递减计数）。
- `template<typename OptionSetter> bool set_option(const OptionSetter& ops_setter)`：对池中所有 socket 应用选项设置（通过容器的 handler 调用）。
- `void close()` / `void clear()`：关闭并清空所有 socket 单元。

类型约束与静态断言：
- 使用 `socket_type_checker<socket_type>::tag` 静态断言确保 `socket_type` 为 UDP 类型（`tag_udp`）。
- `ver` 模板参数用来区分 IPv4/IPv6（`is_v4_type` / `is_v6_type`），并在创建 `endpoint_type` 时选择协议版本。

使用示例（伪代码）：

```cpp
yggr::network::udp_helper::udp_socket_pool<MySocket, MyEndpoint, MyService, yggr::network::network_config::ip_ver::E_IPV4> pool(4);
auto psock = pool.get(service);
// 使用 psock 进行发送/接收
pool.back(psock);

// 设置选项到整个池
pool.set_option(my_option_setter);
```

注意事项：
- `OptionSetter` 必须要么满足 `is_settable_socket_option`（即可直接调用 `socket->set_option(opt)`），要么是可调用的回调（`handler(socket_unit&)`）。
- `socket_unit` 使用指针转整数作为 id，确保指针稳定且唯一；在特定平台/编译器上请确认 `utility::cast_pointer_to_int::cast` 的行为。
- 依赖 `boost::multi_index`、`safe_container` 和项目的 `service`/`socket` 实现；在不同环境下测试并发行为。

相关文件：
- [yggr/network/udp_helper/udp_socket_pool.hpp](udp_socket_pool.hpp)
- [yggr/network/type_traits/socket_type_checker.hpp](../type_traits/socket_type_checker.hpp)
- [yggr/safe_container/safe_multi_index_container.hpp](../../safe_container/safe_multi_index_container.hpp)
