**data_info_parser.hpp 文档**

简介：
- `data_info_parser.hpp` 提供了两个模版工具和一个方便的宏，用于从数据类型或定义中解析与获取网络数据的 ID、版本及组合信息（`data_info`）。该文件把“类型 -> (id, ver, info)” 的映射规则统一封装，便于消息路由、序列化与兼容处理。

主要组件：

- `YGGR_PP_NETWORK_DATA_INFO_PARSER_DEF(__type__, __data_id__, __data_ver__)` 宏：
  - 为指定的基础类型 `__type__` （例如 `s32`、`u8` 等）生成 `network_data_info_getter<Info_Def, __type__>` 的特化实现。
  - 特化实现会提供静态方法 `data_id()`、`data_ver()` 和 `data_info()`，返回指定的常量 ID、版本以及构造好的 `data_info_type`。

- `network_data_info_getter<Info_Def, T>` 模板：
  - 默认版本期望类型 `T` 自身暴露 `data_id_type`、`data_ver_type`、`data_info_type` 等成员，并提供对应的静态方法（`data_id()`、`data_ver()`、`data_info()`）。
  - 使用 `BOOST_MPL_ASSERT` 断言确保 `Info_Def` 中的 ID/Ver/Info 类型与 `T` 的类型一致。

- `network_data_info_parser<Info_Def>` 模板：
  - 提供静态接口：
    - `template<typename T> static data_id_type data_id()` —— 通过 `network_data_info_getter<Info_Def, T>::data_id()` 获取。
    - `template<typename T> static data_ver_type data_ver()`
    - `template<typename T> static data_info_type data_info()`
  - 还提供对已有 `data_info_type` 值的解析辅助：
    - `static const data_id_type& data_id(const data_info_type& info)` 返回 info 的第 0 个元素（ID）。
    - `static const data_ver_type& data_ver(const data_info_type& info)` 返回 info 的第 1 个元素（版本）。

类型说明：
- `Info_Def`：通常来自 `network_data_info_def`（如 `data_info_def.hpp` 中定义的别名），包含 `data_id_type`、`data_ver_type`、`data_info_type`。
- `data_info_type`：项目中使用的包元信息类型（例如 `yggr::packet::packet_info<ID, Ver>`）。

常见用法示例：

1) 使用 `network_data_info_parser` 从消息类型 `MyMsg` 获取 ID/版本（假设 `MyMsg` 已按项目约定定义静态成员或已通过宏特化）：

```cpp
using parser = yggr::network::support::network_data_info_parser<MyInfoDef>;
auto id = parser::data_id<MyMsg>();
auto ver = parser::data_ver<MyMsg>();
auto info = parser::data_info<MyMsg>();
```

2) 解析已有 `data_info_type` 实例：

```cpp
auto id_ref = parser::data_id(info_instance);
auto ver_ref = parser::data_ver(info_instance);
```

注意事项：
- 默认 `network_data_info_getter` 会使用 `BOOST_MPL_ASSERT` 确保类型一致性，若你为自定义类型提供特化，请确保类型别名与方法签名匹配。
- 文件末尾使用 `YGGR_PP_NETWORK_DATA_INFO_PARSER_DEF` 为常见基础类型（`char`, `s8`, `u8`, `s16`, `u16`, `s32`, `u32`, `s64`, `u64`, `f32`, `f64`，以及可选的 `wchar_t`, `c8`, `c16`, `c32`）生成了特化，映射到 `yggr::task_center::task_data_id_def` 中的 ID 常量，版本默认为 `1`。

相关文件：
- [yggr/network/support/data_info_parser.hpp](data_info_parser.hpp)
- [yggr/network/support/data_info_def.hpp](data_info_def.hpp)
