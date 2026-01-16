# network_info.hpp 文档

## 概述
- 文件： [yggr/network/network_info.hpp](yggr/network/network_info.hpp#L1-L661)
- 描述：`network_info<ID>` 是一个以字节缓冲为底层的通用容器，用于存储与传输与“拥有者 ID”（`ID`）相关联的时间戳和一系列 owner id 元素。它封装了时间（以毫秒为单位）和若干 owner id 的序列，提供序列化友好的接口（直接访问底层字节缓冲）、时间更新、元素增删改查与字节序（hton/ntoh）处理。

## 设计要点
- 模板参数：`ID`（owner id 类型），可为内置整数或类类型（如字符串/自定义 ID 容器）。
- 底层缓冲：`buf_type = yggr::string`（单字节元素）用于存放二进制数据，布局为 [time (time_type bytes)] [owner_id_0] [owner_id_1] ...。
- 编码：时间与 owner id 在存入缓冲时使用 `::yggr::network::hton` 进行主机到网络字节序转换，读取时使用 `ntoh` 恢复。
- 支持 owner id 的多种字节宽度：静态断言限制 `sizeof(owner_id_type)` 为 4、8、16 或 32 字节。
- 对于 class 型 `owner_id_type`（例如字符串或容器），使用专用 helper 将其视作内存块进行拷贝，否则按原生字节拷贝。

## 主要类型别名
- `owner_id_type`：模板参数 `ID`。
- `time_type`：定义为 `yggr::s64`。
- `buf_type`：`yggr::string`。
- `buf_val_type`：`buf_type::value_type`（应为 1 字节）。

## 常量与布局
- `E_time_idx_s = 0`：时间字段起始索引。
- `E_time_length = sizeof(time_type)`。
- `E_id_idx_s = E_time_length`：第一个 owner id 的起始索引。
- `E_id_length = sizeof(owner_id_type)`。
- `E_init_length = E_time_length + E_id_length`：最小缓冲长度（含时间与一个 owner id）。

## 构造函数
- 默认构造：分配 `_buf` 长度为 `E_init_length` 并写入当前时间（毫秒、以网络字节序存储）。
- 从任意容器/迭代器构造：接受 `Buffer` 容器或迭代器范围拷贝数据到 `_buf`。
- 移动/拷贝构造支持（使用 BOOST 的移动宏）。
- 从 `owner_id_type` 构造：初始化时间并把该 owner id 写入缓冲（会字节序转换）。

## 赋值与交换
- 支持对 `buf_type`、容器、以及 `network_info` 本身的赋值。
- `swap()` 支持移动与普通 swap，且提供 `swap_support::swap`、并在 `std`/`boost` 命名空间中引入对应重载以支持 ADL。

## 状态检查与查询
- `effective()`：检查缓冲是否满足最小结构并且剩余字节能整除 `E_id_length`。
- `empty()`：缓冲是否为空。
- `size()`：返回 owner id 元素数量（不含时间字段），仅在 `effective()` 为 true 时有效。
- `buf_size()`：返回底层缓冲字节数。
- `hash()`：对除时间外的字节段计算哈希值。

## 时间相关
- `time()`：返回以主机字节序表示的时间（毫秒）。
- `update_time()`：使用当前时间更新时间字段（网络字节序写入）。
- `update_time(time_type tm)`：设置指定时间值（会先转网络字节序）。
- `time_alive(tm_step)`：判断距当前时间是否在给定步长内。

## owner id 操作
- `set_now_owner_id(const owner_id_type& nid)`：将最后一项替换为 `nid`（写入网络序）。
- `owner_id()` / `owner_id(nidx)`：获取最后一项或指定索引的 owner id（返回主机字节序的值或对象）。
- `push(const owner_id_type& nid)`：向序列尾部添加一个 owner id（写入网络序）。
- `pop()`：弹出并返回最后一个 owner id（返回主机序值）。
- `modify(size_type nidx, const owner_id_type& nid)`：修改索引处元素，成功返回 true。
- `front()` / `back()`：获取首/末元素（主机序）。

## 内部辅助
- `detail::network_info_owner_id_creator`：根据 `owner_id_type` 是否为 class 类型选择不同的从缓冲生成 `owner_id_type` 的实现（容器通过构造迭代器范围，原生类型通过 memcpy）。
- `detail::network_info_owner_id_buffer_pointer`：用于获取 `owner_id_type` 的底层字节指针，以便将其原始字节附加到 `_buf`。

## 迭代/容器互操作
- 提供接受任意容器输入的构造与赋值（使用 `container_ex::is_container` 与 iterator 辅助）。

## 比较与哈希支持
- 提供 `operator==` / `operator!=`，比较为 `compare_eq`。
- 提供 `hash_value`（用于 Boost.Hash）和在支持 C++11 `std::hash` 的情况下对 `network_info<ID>` 提供 std::hash 特化。

## 异常和断言
- 多处使用 `BOOST_STATIC_ASSERT` 与 `assert` 进行边界和类型尺寸检查，确保 `buf_val_type` 为 1 字节以及 `owner_id_type` 的尺寸限制。
- 对无效操作（如在非 effective 的缓冲上调用某些操作）有早期返回与断言保护。

## 使用示例
```cpp
// 假设 ID 为 u32
using info_type = yggr::network::network_info<u32>;
info_type info;
info.update_time();
info.push((u32)0x12345678);
info.push((u32)0x9abcdef0);

u32 last = info.back();
size_t n = info.size();

// 以字节缓冲发送
const u8* data = info.buf();
size_t len = info.buf_size();
```

## 注意事项
- `owner_id_type` 为类类型时，`network_info` 假定其内存布局适合直接按字节传输（即可通过 `begin()`/`end()` 获取连续内存），否则请提供与之配套的序列化方案。
- 对于跨平台与对齐敏感的自定义类型，确保 `mplex::strict_sizeof<OwnerID>` 返回的大小与实际传输期望一致。
- 该类以网络字节序存储时间与 ID 字段，传输前无需额外转换。

## 参考
- 源码： [yggr/network/network_info.hpp](yggr/network/network_info.hpp#L1-L661)

---
