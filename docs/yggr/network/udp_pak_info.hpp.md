# udp_pak_info.hpp

概述
- 定义 UDP 包相关的基础类型：`udp_pak_id`（包 ID）与 `udp_pak_header`（包头）。
- 这些类型用于标识 UDP 分片、描述分片索引/计数/数据长度/类型，并提供缓冲序列化/反序列化与交换/比较操作。

类型说明
- `udp_pak_id`：
  - 内部使用 `u64` 作为 `id_type`，常量 `E_LENGTH = sizeof(id_type)`（通常为 8 字节）。
  - 提供从/到缓冲的序列化接口：`to_buffer<Buffer>()`、`to_buffer(Buffer&)` 与 `from_buffer`（支持容器和迭代器重载）。
  - 支持移动/拷贝构造与赋值、`swap`、以及与 `id_type` 的比较运算（`operator==`/`!=`）。

- `udp_pak_header`：
  - 常量 `E_LENGTH = 8`，并定义字段的偏移与长度：`idx(2B)`、`count(2B)`、`size(2B)`、`type(2B)`。
  - 成员字段：`u16 idx, count, size, type`，分别表示分片索引、总分片数、当前分片数据长度、分片类型（如 static/dynamic 标识）。
  - 提供 `to_buffer`/`from_buffer`（容器与迭代器版本）来做网络字节序的读写（内部使用 `yggr::network::hton/ntoh`）。
  - 支持移动/拷贝赋值、`swap`、并导出到 `swap_support`/`std`/`boost` 命名空间以便 ADL `swap`。

字节序与缓冲细节
- `to_buffer` 将字段转换为网络字节序（`hton`）并写入固定长度缓冲；`from_buffer` 则从缓冲读取并使用 `ntoh` 恢复主机字节序。
- 支持直接将值 reinterpret_cast 到目标缓冲的元素类型，但假定缓冲元素大小为 1 字节，且内存对齐安全。

用例示例（伪代码）

```cpp
udp_pak_id id(12345);
auto id_buf = id.to_buffer<std::vector<uint8_t>>();

udp_pak_header hdr(0, 3, 512, udp_packet::E_static);
auto hbuf = hdr.to_buffer<std::vector<uint8_t>>();

// 解析
udp_pak_id id2;
if(id2.from_buffer(id_buf)) {
    // ok
}
udp_pak_header hdr2;
if(hdr2.from_buffer(hbuf)) {
    // ok
}
```

注意事项
- 直接使用 reinterpret_cast 操作缓冲时，请确保目标缓冲类型的 value_type 字节宽度为 1 字节。
- `udp_pak_header::from_buffer(InputIter s, InputIter e)` 使用 `iterator_ex::advance_copy` 从任意迭代器抽取固定偏移的字节序列，兼容非随机访问迭代器。
- 这些类型是 UDP 包拆分/重组与校验的基础，通常与 `udp_packet` / `udp_packet_wrap` / `udp_packets_collecter` 搭配使用。

文件
- 源文件：`udp_pak_info.hpp`（位于同目录）。

----
