**basic_network_packet.hpp 文档**

简介：
- `basic_network_packet.hpp` 定义了模板类 `basic_network_packet<Archive_Partner, DataInfoDef, DataInfo_Parser>`，它建立在 `yggr::packet::packet` 之上，封装了网络数据包的缓冲区与数据元信息（ID/版本），并提供一套兼容的序列化/反序列化、保存/加载和元信息处理接口。

模板参数：
- `Archive_Partner`：归档（archive）伙伴类型，要求其模式为网络模式（`E_Mode_Network`）。
- `DataInfoDef`：数据包信息定义类型（通常来自 `data_info_def.hpp`），包含 `data_id_type`、`data_ver_type` 和 `data_info_type`。
- `DataInfo_Parser`：用于从类型推导 `data_info` 的解析器模板，默认为 `yggr::network::support::network_data_info_parser`。

主要类型别名：
- `data_id_type`、`data_ver_type`、`data_info_type`：来自 `DataInfo_Parser`，表示数据包的 ID、版本与组合信息类型。
- `buf_type`：底层缓冲区类型（来自基类 `yggr::packet::packet`）。

功能概览：
- 管理数据元信息：成员 `_data_info`（可变）保存当前包的 `data_info`，并提供 `data_info()`、`data_id()`、`data_ver()` 访问器。
- Serialization 容器封装：通过内部 `detail::serialize_info_container` 与 `detail::serialize_container` 模板，支持在序列化时同时传递 `data_info` 与实际对象，并在保存/加载时区分不同的序列化阶段（`E_SAVE`、`E_LOAD`、`E_LOAD_INFO` 等）。
- 保存/加载接口：
  - `template<typename T> bool save(const T& t)`：自动推断 `T` 的 `data_info` 并将对象与 info 一起序列化到缓冲区。
  - `template<typename T> bool load(T& t) const`：从缓冲区反序列化对象（使用 `_data_info` 作为上下文）。
  - `compatibility_save(const data_info_type& data_info, const T& t)`：显式指定 `data_info` 的保存接口（兼容旧版或特殊场景）。
- 信息恢复：`restore_info()` 用于在需要时仅加载 `_data_info` 的信息部分（例如，解密后恢复包头信息）。
- 赋值与交换：支持多种构造/赋值（从缓冲区、从其他 archive partner 的包、移动/拷贝等），并实现 `swap`、非成员 `swap` 适配到 `std` 与 `boost`。
- 比较操作：提供与 `data_info_type` 和其他 `basic_network_packet` 实例的比较（`compare_eq`）以及一组非成员 `operator==/!=` 重载。

设计要点与约束：
- `Archive_Partner` 必须处于网络归档模式（由静态断言验证）。
- `_data_info` 可变且在序列化过程中与对象一起传输；序列化容器使用不同的 Flag 类型区分保存/加载/头部加载阶段。
- 错误码/异常：文件定义了 `ERROR_MAKER` 错误码集合（`E_invalid_version`、`E_invalid_id_type`、`E_invalid_version_type`）用于上层错误处理。

示例用法：

```cpp
using my_packet = yggr::network::basic_network_packet<MyArchivePartner, MyDataInfoDef>;
MyDataInfoDef::data_info_type info = /* 构造 data_info */;
my_packet pak(info, buf_begin, buf_end);
// 保存对象
MyObj obj;
pak.save(obj);
// 加载对象
MyObj out;
pak.load(out);
```

备注与注意事项：
- 在跨 ArchivePartner 的构造/赋值中，缓冲区会做拷贝或移动，并尝试保留 `data_info`。
- `restore_info()` 是在需要单独恢复包的头部信息（例如在加密/解密流程中）时使用的重要工具。
- `basic_network_packet` 侧重于包头信息与缓冲区管理，具体的包格式与序列化细节由 `Archive_Partner` 与序列化策略决定。

相关文件：
- [yggr/packet/packet.hpp](../packet/packet.hpp)
- [yggr/network/support/data_info_parser.hpp](support/data_info_parser.hpp)
- [yggr/network/support/data_info_def.hpp](support/data_info_def.hpp)
