**data_info_def.hpp 文档**

简介：
- `data_info_def.hpp` 定义了 `network_data_info_def` 模板，用于将自定义的 ID 与版本类型绑定为数据包信息类型（`yggr::packet::packet_info`）的别名封装，方便在网络模块中统一描述数据/消息的 ID 和版本。

模板参数：
- `ID`：数据包的标识类型（例如整型、枚举或自定义 id 类型）。
- `Ver`：数据包的版本类型（通常为整型）。

主要类型别名：
- `data_id_type`：等同于模板参数 `ID`。
- `data_ver_type`：等同于模板参数 `Ver`。
- `data_info_type`：等同于 `yggr::packet::packet_info<ID, Ver>`，用于表示数据包的元信息（id + 版本）。

用途与示例：
- 该模板用于在声明网络消息/数据结构时提供标准化的元信息类型。例如：

```cpp
using my_data_info = yggr::network::support::network_data_info_def<std::uint32_t, std::uint16_t>;
my_data_info::data_info_type info; // yggr::packet::packet_info<std::uint32_t, std::uint16_t>
```

集成提示：
- `data_info_type` 可与项目的序列化、路由或消息分发机制协同使用，以便按 ID/版本做消息解析与兼容处理。

文件： [yggr/network/support/data_info_def.hpp](data_info_def.hpp)
