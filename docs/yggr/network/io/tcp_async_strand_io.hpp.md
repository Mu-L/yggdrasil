# `yggr::network::io::tcp_async_strand_io`（文件：`tcp_async_strand_io.hpp`）

## 概要
- **目的**：基于 Boost.Asio 的异步 I/O 封装，提供一个以 `strand` 串行化回调、支持静态/动态包格式的 TCP 异步发送/接收实现，继承自 `Linker`（由上层链接器/协议实现提供）。
- **位置**：`yggr/network/io/tcp_async_strand_io.hpp`（与该文档同目录）。
- **适用场景**：作为网络层通信的 I/O 实现被连接器/会话复用，提供封包发送队列、异步读写、接收缓冲池与错误处理。

## 主要模板参数与别名
模板参数：
- `Linker`：协议/连接层实现类型（需要提供 `protocol_tag_type`、`service_type`、`socket_type`、`deadline_timer_type`、`get_link()` 等接口）。
- `OPacket`：发送数据包类型（`send_data_type`），应定义 `buf_type`, `packet_tag_type`, `data_buf()`, `size()` 等接口。
- `IPacket`：接收数据包类型（`recv_data_type`），应定义 `buf_type`, `size_container_type`, `net_info_type`, `packet_tag_type` 等。

常用别名（摘选）：
- `send_data_type` / `recv_data_type`
- `service_type` / `strand_type`（`service_type::strand`）
- `data_buf_type`（`send_data_buf_type`）
- `recv_buf_queue_type`：静态接收缓冲池队列类型（`safe_buffered_object<wrap_recv_buf_type>`）

编译期断言：
- 使用 `BOOST_MPL_ASSERT` 验证 `service_type` 与 `link_init_type` 相同；验证发送/接收缓冲类型一致。

## 错误与异常定义
- 文件内部使用宏：`YGGR_PP_NETWORK_IO_ERROR_DEF("tcp_async_strand_io")` 来注册 I/O 相关错误码（例如接收大小/头/数据错误）。这些错误在处理失败时会通过 `exception::exception::throw_error` 抛出（见 `handler_recv_*` 中的错误路径）。

## 发送流程（send）
- 公共方法：
  - `send_packet(Pak& pak, Handler handler)`：将包放入 `out_queue`，由队列调度实际发送。
  - `next_send()`：通知队列继续下一次发送。
  - `exec_send_packet` -> `prv_send_packet`：根据包的 `packet_tag_type`（静态/动态）分别处理：
    - 静态包（`tag_static_type`）：将数据指针包装为单一 `const_buffer` 并调用 `boost::asio::async_write`。
    - 动态包（`tag_dynamic_type`）：先生成 `size_container`（包含 net_info_size 与 data_size），再把 size、net_info、data 三段组成 `const_buffer` 数组并 `async_write`。
- 所有 async 写操作通过 `_strand.wrap(handler)` 来保证 handler 在该 `strand` 中串行执行。

## 接收流程（recv）
- 对外接口：`recv_packet<TupleHandler>(handler)`，通过 `prv_recv_packet<Pak>(handler, tag*)` 分发到静态或动态处理。

- 静态包接收（`prv_recv_packet` + `handler_recv_data_of_static`）：
  - 从 `_s_recv_buf_queue`（静态缓冲池）取出缓冲区指针 `precv_buf`，检查缓冲大小 `pak_type::buf_size()`。
  - 使用 `async_read` 读取固定长度 `buf_size` 到该缓冲区，回调 `handler_recv_data_of_static`。
  - 回调中如果读取未完成且无错误，继续 `async_read` 剩余字节；如发生错误或其它异常，归还缓冲区并调用用户 handler 以及抛出 `E_invalid_recv_data` 错误。
  - 成功读取后构造 `pak_type` 并将缓冲区还回队列，然后调用用户 handler（通过 `prv_s_call_handler_0` / `prv_s_call_handler_1`）。

- 动态包接收（`prv_recv_packet` + `handler_recv_size` + `handler_recv_data_of_dynamic`）：
  - 首先读取 `size_container`（固定大小），回调 `handler_recv_size`。
  - 在 `handler_recv_size` 中将 `size_container` ntoh，校验 `effective()` 和 `data_buf_size` 与 `limit_buf_size()`；如超限或非法返回错误。
  - 分配/调整缓冲区以容纳 header + data，通过 `async_read` 读取两段（info + data），回调 `handler_recv_data_of_dynamic`。
  - 回调中构造 `net_info` 和 `pak_type(net_info, data_ptr, data_end)` 并交给用户 handler；异常路径会抛出 `E_invalid_recv_size` 或 `E_invalid_recv_data`。

- 接收回调中使用 `utility::args_holder_nv` / `basic_args_holder_nv_type` 封装 tuple 风格的 handler（例如 `(on_recv, on_complete)`），并通过 `prv_s_call_handler_0`/`1` 调用。

## 缓冲池与静态成员
- 类声明了一个静态 `recv_buf_queue_type tcp_async_strand_io:: _s_recv_buf_queue` 用于复用接收缓冲，避免频繁分配。
- 池在类模板实例化后静态定义（既见文件底部的定义），用于所有该模板实例共享缓冲区资源。

## 线程与同步
- 使用 `strand_type _strand` 将所有异步 handler 包装，保证 handler 在 `strand` 中串行调用，避免并发回调带来的竞态。
- 输出队列 `_out_queue` （`opackets_queue<this_type>`）负责串行化发送请求，减少并发发送冲突。

## 错误处理与用户 handler 调用约定
- 用户 handler 以 tuple (`handler_type`) 形式传入，`prv_s_call_handler_0` 将以 `(err_code, pak)` 的方式调用第一个函数对象，`prv_s_call_handler_1` 则调用第二个（通常为完成/cleanup 回调）。
- 在接收过程中发生错误时，除了调用用户 handler 以外，代码会使用 `exception::exception::throw_error(error_maker_type::make_error(...))` 抛出由 `YGGR_PP_NETWORK_IO_ERROR_DEF` 定义的错误码，以便上层记录或处理。

## 使用示例（伪代码）
```cpp
// Linker 类型由上层提供，必须提供 get_link(), close(), check_state(), strand 等。
using IO = yggr::network::io::tcp_async_strand_io<MyLinker, MyOPacket, MyIPacket>;

MyLinker::link_init_type link_init = /* ... */;
IO io(link_init);

// 发送示例：
MyOPacket outpak = /* 填充 */;
io.send_packet(outpak, [](const boost::system::error_code& err){ /* send complete */ });

// 接收示例：
auto recv_handler = std::make_tuple(
    [](const boost::system::error_code& err, MyIPacket pak){ /* on recv */ },
    [](){ /* on complete */ }
);
io.recv_packet<MyIPacket>(recv_handler);
```

## 注意事项与建议
- 确保 `OPacket` / `IPacket` 的缓冲接口与 `buf()` / `buf_size()` / `size_container_size()` 等一致，错误适配会导致读取/写入异常或抛错。
- `strand` 保证 handler 串行化，但若 `IO` 实例被多线程共享，仍需保证 `linker`/`server` 层的线程安全语义。
- 异常路径中有抛出错误的语句，若上层不捕获会导致终止，请在上层捕获或在 handler 中做好错误处理。
- 根据平台/编译器，`boost::shared_from_raw(this)` 用于在绑定回调时保持对象生命周期，请确保 `this` 在 shared_from_raw 场景下有效。

