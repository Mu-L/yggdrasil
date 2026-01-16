# udp_packets_collecter.hpp

概述
- 提供 `udp_packets_collecter<Packet_Wrap>` 类，用于在接收 UDP 分片时按包 ID 收集分片并在组装完成后返回完整的 `Packet_Wrap` 对象。
- 依赖内部缓冲池与线程安全映射，处理并发收集场景并可回收缓冲对象以减少分配。

模板参数
- `Packet_Wrap`：分片包的封装类型（例如 `udp_packet_wrap<Buffer>`），需提供 `data_buf_type`、`id_type`、`is_completed()`、`clear()`、`operator<<` 等接口。

主要类型
- `data_buf_type`：来自 `Packet_Wrap::data_buf_type`。
- `id_type`：来自 `Packet_Wrap::id_type`，作为分片集合的键。
- `packet_wrap_ptr_type`：从内部 `safe_buffered_object` 获取的可复用 `Packet_Wrap` 智能指针。

核心 API
- `collect(buf)`：接收原始字节缓冲或已解析的 `id`+缓冲，返回当次能组成完整包时的 `packet_wrap_ptr_type`（否则返回空指针）。
  - 有 `collect(BOOST_RV_REF(data_buf_type))`、`collect(const data_buf_type&)`、`collect(const id_type&, ...)` 等重载。
- `back_buffer(packet_wrap_ptr_type)`：将未使用或已经处理完的 `Packet_Wrap` 放回内部缓冲池以复用。
- `check_state()`：扫描内部映射并移除长时间未完成或状态为 `E_state_die` 的条目，回收其资源。
- `clear()`：清空内部映射。

实现细节
- 使用两个缓冲池：
  - `_packet_wrap_buf_queue`：用于分配临时 `packet_wrap_ptr_type`，在收到单个分片时先用该对象承载分片数据。
  - `_safe_packet_wrap_buf_queue`：用于插入到 `_wrap_map` 的线程安全包装对象，保证并发访问时的安全操作。
- `_wrap_map`：类型为 `safe_unordered_map<id_type, safe_packet_wrap_ptr_type>`，用于按 ID 存储正在收集的包。
- 当单次收集未完成时，通过 `prv_collect_of_wrap` 将临时 `Packet_Wrap` 包装为线程安全对象并插入 map，返回时若合并成功则从 map 移除并返回完整对象。
- 异常与错误处理：在插入或访问安全包装对象时捕获并处理 `safe_packet_wrap_type::error_type` 与 STL 异常，并在失败时回收缓冲。
- 采用 `prv_s_handler_collect` 与 `prv_s_handler_insert_buffer` 作为回调以配合 `_wrap_map.insert` 与 `using_handler` 接口。

使用示例（伪代码）

```cpp
typedef udp_packet_wrap<std::vector<u8>> pkt_wrap;
udp_packets_collecter<pkt_wrap> collecter;

// 接收网络缓冲时
auto res = collecter.collect(received_buf);
if(res) {
    // res 是完整的包（packet_wrap_ptr_type）
    Packet out;
    res->get_packet(out);
    // 处理 out
    collecter.back_buffer(res);
}
```

注意事项
- `Packet_Wrap` 必须匹配 `udp_packets_collecter` 的语义（支持 `operator<<` 以追加分片、`is_completed()` 判定完整性）。
- 内部缓冲为静态单例容器（通过静态函数返回），在多模块环境中其生命周期与析构顺序需注意。
- 设计为了并发场景使用，依赖 `safe_container` 的线程安全语义。

文件
- 源文件：`udp_packets_collecter.hpp`（同目录）。

----
