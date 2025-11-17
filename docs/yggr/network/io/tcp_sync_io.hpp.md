# `yggr::network::io::tcp_sync_io`（文件：`tcp_sync_io.hpp`）

## 概述
- 目的：这是一个基于 Boost.Asio 的同步（blocking）TCP I/O 封装模板，提供同步发送/接收接口并结合一个发送队列与接收缓冲复用池。
- 注意：源文件顶部包含 `#error "now discard it"` 注释，表明该实现当前已弃用/不再使用（注：文档仍然对源码进行说明以便参考或迁移）。
- 位置：`yggr/network/io/tcp_sync_io.hpp`（该文档放置在同一目录）。
- 适用场景：需要阻塞式（同步）读写语义的通信场景或作为对比参考；项目当前会话框架上可能不再启用此类。

## 主要模板参数与类型别名
- 模板参数：
  - `Linker`：上层连接器/协议实现类型（必须提供 `protocol_tag_type`、`service_type`、`socket_type`、`get_link()`、`close()`、`link_init_type` 等）。
  - `OPacket`：发送数据包类型（`send_data_type`）。
  - `IPacket`：接收数据包类型（`recv_data_type`）。

- 常见别名（摘选）：
  - `linker_type`、`opacket_type`、`ipacket_type`
  - `protocol_tag_type`、`service_type`、`socket_type`、`deadline_timer_type`
  - `send_data_type` / `recv_data_type`
  - `send_data_buf_type` / `recv_data_buf_type` / `data_buf_type`

- 类型断言：
  - 使用 `BOOST_MPL_ASSERT` 确保 `service_type` 与 `link_init_type` 相同；并确保发送与接收缓冲类型一致（`send_data_buf_type == recv_data_buf_type`）。

## 静态/辅助类型
- `tag_static_type` / `tag_dynamic_type`：用于在编译期区分静态包（fixed-size）与动态包（包含 size header + info + data）。
- `recv_buf_queue_type`：基于 `safe_container::safe_buffered_object` 的接收缓冲池类型；类中定义了静态成员 `_s_recv_buf_queue` 用于复用接收缓冲，减少频繁分配。 
- `out_queue_type`：`yggr::network::packets_support::opackets_queue<this_type>`，用于串行化发送请求。

## 错误定义
- 使用宏 `YGGR_PP_NETWORK_IO_ERROR_DEF("tcp_sync_io")` 注册该模块的错误码（例如 `E_invalid_recv_data`, `E_invalid_recv_size` 等）。
- 在检测到非法接收长度、无可用缓冲或其他严重错误时，会：
  - 通过用户 handler 返回一个对应的 `boost::system::error_code`；
  - 并且在若干路径中调用 `exception::exception::throw_error(error_maker_type::make_error(...))` 抛出更高层次的异常以供上层捕获/记录。

## 发送（同步）流程
- 提供的接口：
  - `send_packet(Pak& pak, const Handler& handler)`：将包交给 `_out_queue`，由队列调度执行实际发送。
  - `exec_send_packet` / `prv_send_packet`：根据包的 `packet_tag_type`（静态/动态）调用不同实现。

- 静态包（`tag_static_type`）发送：
  - 将 `pak.data_buf()` 与 `pak.size()` 包装为一个 `boost::asio::const_buffer` 数组，调用 `boost::asio::write(linker_type::get_link(), bufs, transfer_all(), ec)`，这是同步阻塞写。
  - 完成后立即调用用户 `handler(e)`，返回同步完成状态。

- 动态包（`tag_dynamic_type`）发送：
  - 构造 `size_container_type`（将 net_info_size 与 data_size 打包并进行 `hton`），并取 `net_info` 数据指针；
  - 将 size、net_info、data 三段组成 `const_buffer` 数组并同步 `write`；
  - 写完后调用 `handler(e)`。

- 注意：发送是同步阻塞操作，可能会阻塞调用线程直到写入完成或发生错误。

## 接收（同步）流程
- 提供的接口：
  - `recv_packet<Pak>(const Tuple_Handler& handler)`：根据 `Pak::packet_tag_type` 选择静态或动态接收实现（`prv_recv_packet`）。

- 静态包接收：
  - 从 `_s_recv_buf_queue.drop()` 取出缓冲对象指针；若无可用缓冲，则通过 handler 返回 `boost::asio::error::no_buffer_space` 并结束。
  - 根据 `pak_type::buf_size()` 调整缓冲大小并调用 `boost::asio::read(linker_type::get_link(), bufs, transfer_all(), ec)`，这是同步读取固定长度。
  - 读取完成后：若读取字节数不匹配，返回错误并抛出 `E_invalid_recv_data`；成功则构造 `pak_type pak(recv_buf)` 并调用用户 handler。
  - 注意：实现中在若干路径存在重复的 handler 调用与抛出异常（源码包含冗余/多次错误路径调用），需注意上层行为。

- 动态包接收：
  - 先同步读取 `size_container`（固定长度），调用 `handler_recv_size` 处理；
  - `handler_recv_size` 将 `size_container` ntoh，校验 `effective()`、`data_buf_size` 与 `limit_buf_size()`，并计算总的 header+data 长度；
  - 为 header+data 分配/调整缓冲区并同步读取两段（info + data），调用 `handler_recv_data_of_dynamic`；
  - 读取成功后构造 `net_info` 与 `pak_type(net_info, data_ptr, data_end)` 并调用用户 handler；错误路径返回适当的 `boost::asio::error_code` 并抛出 `E_invalid_recv_size` / `E_invalid_recv_data`。

- 注意：所有读取操作为阻塞调用，可能在等待网络或长时间连接时阻塞调用线程。

## 缓冲池与静态成员
- 类定义了静态成员 `recv_buf_queue_type tcp_sync_io:: _s_recv_buf_queue`，用于跨实例共享接收缓冲资源。
- 使用模式：`drop()` 从池中取出一个缓冲智能指针，使用后通过 `back(precv_buf)` 放回池中；若池空会向用户返回 `no_buffer_space` 错误。

## 线程与同步语义
- 该类型为同步实现，未使用 `strand` 或异步 handler 串行化机制；调用者必须在多线程场景下自行保证线程安全。
- 发送队列 `_out_queue` 用于对发送请求做队列化管理，但底层 `prv_send_packet` 仍执行阻塞写。

## 使用示例（伪代码）
```cpp
// 假设存在 MyLinker, MyOPacket, MyIPacket 定义
using sync_io = yggr::network::io::tcp_sync_io<MyLinker, MyOPacket, MyIPacket>;

MyLinker::link_init_type init = /* ... */;
sync_io io(init);

// 发送（阻塞）
MyOPacket outpak = /* 构造并填充 */;
io.send_packet(outpak, [](const boost::system::error_code& ec){
    if(!ec) { /* 发送成功 */ }
    else { /* 处理错误 */ }
});

// 接收（阻塞）：handler 为 tuple，首元素接收 (error_code, packet)
auto handler = std::make_tuple(
    [](const boost::system::error_code& ec, MyIPacket pak){
        if(!ec) { /* 处理 pak */ }
    },
    [](){ /* 可选的完成/cleanup 回调 */ }
);

io.recv_packet<MyIPacket>(handler);
```

## 注意事项与建议
- 该实现为阻塞 API，不适合直接在事件循环或异步回调线程中长时间调用；若需并发处理，请考虑异步版本（例如 `tcp_async_strand_io`）。
- 源码含 `#error "now discard it"`，表明代码在当前工程中被弃用，若要启用请先确认上层会话框架支持同步 I/O。 
- 源码在错误路径中存在多处重复的 handler 调用与抛出异常（可能为历史遗留），建议在复用/维护时清理这些路径以避免重复通知上层。
- 使用 `_s_recv_buf_queue` 可以减少内存分配但池耗尽时会直接返回 `no_buffer_space` 错误，上层应准备好重试或扩大池容量。

