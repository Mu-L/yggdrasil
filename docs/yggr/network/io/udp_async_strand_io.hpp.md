# `yggr::network::io::udp_async_strand_io`（文件：`udp_async_strand_io.hpp`）

## 概述
- 目的：基于 Boost.Asio 的 UDP 异步 I/O 封装，使用 `strand` 串行化发送回调并通过 `opackets_queue` 对发送请求做队列化管理。
- 位置：`yggr/network/io/udp_async_strand_io.hpp`（本文件与源文件同目录）。
- 适用场景：需要按序列化发送 UDP 包且在异步上下文中保证回调串行化的场景。

## 关键特性摘要
- 提供模板类 `udp_async_strand_io<Linker, OPacket, IPacket>`，继承自 `Linker`。
- 使用 `udp_packet_wrap<data_buf_type>` 把发送包拆分成多个数据缓冲段，并通过 `async_send_to` 发送。
- 通过 `service_type::strand`（`_strand`）保证回调串行化：`_strand.wrap(handler)`。
- 内部有发送队列类型 `opackets_queue<this_type>`；接收相关函数 `recv_packet` 在packets_support中实现。
- 错误定义：使用 `YGGR_PP_NETWORK_IO_ERROR_DEF("udp_async_strand_io")` 注册模块错误码。

## 模板参数与类型别名（概览）
- `Linker`：上层连接器类型，需提供 `protocol_tag_type`、`service_type`、`socket_type`、`endpoint_type`、`link_init_type`、`get_link()` 等。
- `OPacket`：发送包类型，要求提供 `buf_type` 等用于构建缓冲段的接口。
- `IPacket`：接收包类型（本类未实现接收逻辑，但保持模板一致性）。

- 常见别名：`linker_type`, `send_data_type`, `recv_data_type`, `data_buf_type`, `strand_type`。

## 构造函数要点
- 构造函数会根据 Boost.Asio 版本获取对应的 `io_service`/`executor` 上下文来初始化 `_strand`：
  - 当 `BOOST_ASIO_VERSION < 101400` 时使用 `link_init.get_io_service()`。
  - 否则使用 `static_cast<service_type&>(link_init.get_executor().context())`。
- 同时支持带 `endpoint` 与可选 `DHandler` 的重载构造函数。

## 发送流程（异步）
- 外部接口：
  - `send_packet(Pak& pak, const Handler& handler)`：把包交给 `_out_queue`，队列负责调度 `exec_send_packet`。
  - `next_send()`：通知队列继续下一个发送任务。

- 实际发送（`exec_send_packet`）步骤：
  1. 使用 `udp_packet_wrap<data_buf_type> wrap(pak)` 计算分片数量 `wrap.count()`。
  2. 为每个分片调用 `wrap.get_data_buf(i, data_bufs[i])`，并把每段包装成 `boost::asio::const_buffer` 放入 `bufs`。
  3. 调用 `linker_type::get_link().socket().async_send_to(bufs, linker_type::get_link().remote_endpoint(), _strand.wrap(handler));`。

- 注意：如果 `data_bufs[i].empty()` 则会清空 `data_bufs` 与 `bufs` 并跳出循环（表示无数据可发送），随后仍会调用 `async_send_to`（实际行为取决于 `bufs` 的状态）。

## 接收：未实现
- `recv_packet(const Tuple_Handler& handler)` 在此实现中为空（未提供接收逻辑）。若需要接收功能，应由 `Linker` 或派生类实现，或者另用 `udp_async_recv_*` 实现。

## 同步/线程语义
- 发送回调通过 `_strand` 包装以保证在 `strand` 中串行执行，从而避免多线程回调竞争问题。
- 虽然发送被串行化，但 `async_send_to` 本身是异步且不会阻塞调用线程。

## 缓冲/包装器说明
- `udp_packet_wrap<data_buf_type>` 被用作统一的发送包分片器，负责把 `Pak` 表示的逻辑包映射为连续或离散的数据缓冲段集合。
- 本实现把每一段转换为 `boost::asio::buffer`，并一次性传给 `async_send_to`（scatter-gather 发送）。

## 错误处理
- 本类仅注册了模块错误宏，实际错误处理通过用户传入的 `handler` 接收（`boost::system::error_code`）；更多细化错误由 `Linker` 或上层协议处理。

## 使用示例（伪代码）
```cpp
using IO = yggr::network::io::udp_async_strand_io<MyLinker, MyOPacket, MyIPacket>;

MyLinker::link_init_type init = /* ... */;
IO io(init);

MyOPacket pak = /* 填充 */;

io.send_packet(pak, [](const boost::system::error_code& ec, std::size_t bytes_sent){
    if(!ec) {
        // 发送成功
    } else {
        // 处理错误
    }
});

// 接收未实现，需由上层或其他组件提供。
```

## 建议与注意事项
- 如果你想要完整的 UDP 收/发模块，请明确接收语义：是否使用 `async_receive_from`、是否需要缓冲池、是否需要重组逻辑等；当前类只处理发送。
- 注意 `async_send_to` 的 `bufs` 在调用时必须保持有效直到 handler 被调用，因此 `data_bufs` 的生命周期必须长于异步操作（当前函数里 `data_bufs` 是局部变量，但被复制到 `bufs`，需要确保底层缓冲仍然存在，通常 `udp_packet_wrap` / `Pak` 必须保证在 handler 执行前数据有效）。
- `_strand.wrap(handler)` 保证了 handler 在 strand 上串行执行，但若 handler 捕获了 `this` 指针，请确保对象的生命周期管理（shared_from_this 等）。

