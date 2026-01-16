# network_packet.hpp 文档

## 概述
- 文件： [yggr/network/network_packet.hpp](yggr/network/network_packet.hpp#L1-L761)
- 描述：`network_packet` 是基于 `basic_network_packet` 的模板化封装，结合网络所属者信息（`NetInfo`）、数据描述（`DataInfoDef`）与数据包缓冲管理，提供序列化/反序列化、字节序处理、时间检查与与任务中心互操作的功能。该类型可作为任务/消息在网络与任务中心间传递的载体。

## 模板参数
- `Archive_Partner`：序列化/反序列化策略/伙伴类型。
- `DataInfoDef`：数据描述定义类型（数据 ID、版本等）。
- `NetInfo`：网络所属者信息类型（例如 `network_info<ID>`）。
- `Size`：用于表示数据长度的无符号整型（默认为 `u32`）。必须为无符号整数类型。
- `DataInfo_Parser`：解析 `DataInfoDef` 的解析器模板，默认 `network_data_info_parser`。
- `NetInfo_Parser`：解析 `NetInfo` 的解析器模板，默认 `task_owner_info_parser`。
- `Base_Packet`：底层包类型模板（默认为 `basic_network_packet`）。

## 主要类型别名
- `packet_tag_type`：`tag_pak_dynamic`（表示动态包标签）。
- `buf_type`, `data_info_type`, `data_id_type`, `data_ver_type`：继承自 `base_type`。
- `net_info_type` / `owner_info_type`：`NetInfo`。
- `owner_id_type`：由 `NetInfo_Parser` 定义的 owner id 类型。
- `size_container_type`：`size_container<size_type>`，用于处理长度字段。

## 构造与赋值
- 多种构造函数支持：
  - 空构造、使用 `NetInfo` 构造、带上数据对象或数据缓冲的多种组合。
  - 支持从其它 `network_packet<Other_Archive_Partner,...>` 的移动与拷贝构造/赋值。
- `assign(...)` 系列函数用于批量设置 `net_info` 与数据缓冲或从另一个包赋值。
- 支持移动语义（BOOST 移动宏）与拷贝语义。

## 数据访问与查询
- `net_info()` / `owner_info()`：访问 `NetInfo`。
- `owner_id()`：返回 `owner_id_type`，从 `NetInfo` 获取。
- `net_info_buf()` / `net_info_size()`：访问底层 `NetInfo` 的字节缓冲与大小。
- `data_size()`：数据负载大小（来自 `base_type::size()`）。
- `data_buf()`：获取数据部分字节缓冲指针。
- `size()`：返回总项数（`_net_info.size() + base_type::size()`）。

## 时间与有效性
- `time_alive(tm_step)`：通过 `_net_info.time_alive()` 判断时间是否在阈值内。
- `update_time()` / `update_time(tm)`：更新 `NetInfo` 的时间字段。

## 数据与缓冲管理
- `clear()`：清除数据与 `NetInfo`。
- `swap()`：支持与其它 `network_packet` 交换（也在 `swap_support` 中引入 ADL 支持）。
- 静态信息函数：`size_size()`, `size_container_size()`, `limit_buf_size()` 等提供和大小字段相关的常量或查询。

## 发送/任务中心 支持
- 通过 `owner_info` / `owner_id` / `data_info` 等 getter 类型（嵌套 struct）方便传递给函数式工具或任务中心。
- 在 `yggr::task_center::support::task_real_data_getter` 特化中，`network_packet` 被视为任务的真实数据类型，getter 返回对包本身的地址，以便任务中心直接使用包作为任务体。

## 互操作性
- 提供与 `std::swap` / `boost::swap` 的 ADL 支持（`swap_support::swap` 导入到 `std`/`boost` 命名空间）。
- 对 `network_packet` 的 `std::hash` / `boost::hash` 暂未直接实现，但可通过 `data_info`/`net_info` 的字段自定义哈希。

## 注意事项
- `Size` 必须为无符号整数类型（通过 BOOST_MPL_ASSERT 强制检查）。
- `NetInfo` 与相关解析器需提供所需接口（例如 `buf()`, `buf_size()`, `owner_id()` 等）。
- 使用移动/拷贝构造与赋值时注意底层 `base_type` 的移动语义与 `NetInfo` 的移动语义。

## 示例
```cpp
using pkt_t = yggr::network::network_packet<ArchivePartner, DataInfoDef, network_info<u32>>;
pkt_t pkt(net_info);
pkt.save(my_obj); // 保存序列化对象到数据缓冲

send(network_socket, pkt.net_info_buf(), pkt.net_info_size());
send(network_socket, pkt.data_buf(), pkt.data_size());
```

## 参考
- 源码： [yggr/network/network_packet.hpp](yggr/network/network_packet.hpp#L1-L761)

---
