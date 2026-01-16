**connection.hpp 文档**

简介：
- `connection.hpp` 定义了模板类 `connection<Linker, OPacket, IPacket, NetworkIO>`，它基于 `NetworkIO`（默认 `tcp_async_strand_io`） 提供对发送/接收包的高层封装并增加一个简单的启/禁控制（gate）。该类适用于基于 strand 的异步 IO 场景（TCP/UDP）。

模板参数：
- `Linker`：连接器/关联器类型（用于管理链接生命周期与回调）。
- `OPacket`：出站包类型（发送用）。
- `IPacket`：入站包类型（接收用）。
- `NetworkIO`：底层网络 IO 策略模板，签名为 `NetworkIO<Linker, OPacket, IPacket>`，默认值为 `yggr::network::io::tcp_async_strand_io`。

继承与别名：
- 继承自 `NetworkIO<Linker, OPacket, IPacket>`，并引入多个别名以暴露底层类型：`service_type`、`protocol_type`、`endpoint_type`、`link_type`、`send_data_type`（等于 `opacket_type`）、`recv_data_type`（等于 `ipacket_type`）等。

主要功能：
- 发送：
  - `template<typename NetInfo, typename Data, typename Handler> void send_packet(const NetInfo& netinfo, const Data& data, const Handler& handler)`：构造发送包并通过基类发送。
  - `void next_send()`：触发基类的发送队列处理（如果底层实现需要）。
  - `template<typename Handler> void send_packet(send_data_type& pak, const Handler& handler)`：以已构造的包发送。
- 接收：
  - `template<typename Pak, typename Tuple_Handler> void recv_packet(const Tuple_Handler& handler)`：调用基类的接收接口以异步接收指定类型的包并在完成时调用 handler。
- 关闭：
  - `void close()`：关闭连接——将内部原子门 `_gate` 置为 false 并调用基类 `close()`。

控制机制：
- `gate_type _gate`（原子 bool）用于启/禁发送与接收操作：当 `_gate` 为 false 时，`send_packet`、`recv_packet`、`next_send` 等方法会立即返回，不执行底层 IO 操作。`close()` 会把 `_gate` 置为 false。

并发与构造：
- 提供 C++11 可变参构造（以及基于预处理器宏的替代实现以兼容无变参支持的编译器），将参数转发给基类 `NetworkIO` 的构造函数。

使用示例（伪代码）：

```cpp
using my_conn = yggr::network::connection<MyLinker, MyOPacket, MyIPacket>;
MyLinker::link_init_type init = /* ... */;
my_conn conn(init, /* other args forwarded to NetworkIO */);

conn.send_packet(netinfo, data, [](const boost::system::error_code& ec){ /* sent */ });
conn.recv_packet<MyIPacket>([](MyIPacket& pak){ /* received */ });

conn.close();
```

注意事项：
- `connection` 只是对底层 `NetworkIO` 的薄封装，实际的网络行为（如如何排队、如何在 strand 中执行、超时/重连策略等）由 `NetworkIO` 实现决定。
- `_gate` 的语义是简单启/禁；调用方若在并发上下文中频繁切换 gate 状态，应确保调用顺序的正确性以避免丢失或竞争。
- 若需支持更多控制（例如优雅关闭、排空发送队列后关闭等），应在 `NetworkIO` 或 `Linker` 层实现相应逻辑。

相关文件：
- [yggr/network/io/tcp_async_strand_io.hpp](io/tcp_async_strand_io.hpp)
- [yggr/network/io/udp_async_strand_io.hpp](io/udp_async_strand_io.hpp)
