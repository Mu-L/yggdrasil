# udp_packet_wrap.hpp

概述
- 提供 `udp_packet<Buffer, Verify>` 与 `udp_packet_wrap<Buffer, Verify>` 两个主要模板：
  - `udp_packet` 表示单个 UDP 分片包（包含包 id、包头、数据缓冲与校验码）。
  - `udp_packet_wrap` 用于将任意大包拆分为多个 `udp_packet`（静态或动态包），或将分片收集、校验并重组为原始包。

模板参数
- `Buffer`：底层字节缓冲容器类型（要求元素大小为 1，例如 `std::vector<u8>` 或类似）。
- `Verify`：校验工具类型（默认 `encryption_tool::md5_tool`），需提供 `encrypt`/`check_type` 等接口。

`udp_packet` 关键点
- 常量：
  - `E_INFO_SIZE`：包 id 长度 + 包头长度。
  - `E_VERIFY_SIZE`：校验码长度（由 `Verify` 决定）。
  - `E_MAX_LENGTH`、`E_MAX_DATA_LENGTH`、`E_LIMIT_LENGTH`：限制单分片总长与数据区长度。
  - `E_unknown`/`E_static`/`E_dynamic`：分片类型标记。
- 提供从缓冲构造、转为缓冲（`to_buffer`/`from_buffer`）、访问 id/header/data、比较、swap、移动/拷贝支持。
- `to_buffer` 会在数据前依次写入 id、header、data，然后计算并附加校验码。
- `from_buffer` 解析 id/header/data 并校验校验码（若校验失败返回 false）。

`udp_packet_wrap` 关键点
- 用途：将大包拆分为多个 `udp_packet`（`split_packet`）或将收到的 `udp_packet` 分片收集并重组（`collect`、`prv_collect_detail`、`merge_data_buf`、`prv_merge_data`）。
- 支持两种包模式：静态 (`tag_pak_static`) 和动态 (`tag_pak_dynamic`)：
  - 静态：直接按 `E_MAX_DATA_LENGTH` 分割原始数据缓冲。
  - 动态：先构造 `size_container`（包含 info/data 长度），再把 size + info + data 一并切分。
- 状态与控制：
  - `_id`、`_now_count`、`_count`、`_type`、`_bcompleted`、`_udp_packet_vt` 保存分片信息。
  - `empty()`, `clear()`, `is_completed()`, `check_state()` 等方法管理状态机。
- 合并与重建：
  - `merge_data_buf` 按分片顺序拷贝数据到目标缓冲。
  - `prv_merge_data` 根据包类型把合并后的缓冲重建为目标 Packet（静态或动态分别处理）。
- 辅助：提供 `operator<<`/`operator>>` 重载用于将缓冲/包推入或从 `udp_packet_wrap` 拉出最终 `Packet`。

实现注意事项
- 强制检测 `Buffer` 的元素大小为 1（`BOOST_MPL_ASSERT`）。
- 采用 `encryption_tool::md5_tool` 默认校验；可以替换 `Verify` 类型以改变校验算法或长度。
- 对分片索引、计数、重组有严格断言，且在收集过程中对重复/冲突分片进行保守处理（保持已有分片不被覆盖）。
- `E_MAX_DATA_LENGTH` 与 `E_MAX_LENGTH` 决定了单个 UDP 分片的最大可用数据量；超出时会拆分为多片。

示例（伪代码）

```cpp
typedef std::vector<u8> buf_t;
udp_packet_wrap<buf_t> wrap;
// 将大包拆分并读取分片：
MyPacket pak = ...; // 可为 static/dynamic 型 packet
wrap.split_packet(pak);
for(size_t i = 0; i < wrap.count(); ++i) {
    auto frag = wrap[i]; // 每个 frag 是单个 udp 分片原始缓冲
    send_raw(frag);
}

// 在接收端：
udp_packet_wrap<buf_t> recv_wrap;
recv_wrap.collect(received_frag_buf);
if(recv_wrap.is_completed()) {
    MyPacket out;
    recv_wrap.get_packet(out);
    // 使用 out
}
```

文件
- 源文件：`udp_packet_wrap.hpp`（请参阅实现获取完整的断言与边界检查细节）。

----
