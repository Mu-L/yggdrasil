# `yggr::network::sender_checker::sender_adapter_checker`（文件：`sender_adapter_checker.hpp`）

## 概述
- 目的：在发送前检查目标 `NetEntity`（或包内的目标 id）是否启用了对应的发送适配器（adapter）。
- 位置：`yggr/network/sender_checker/sender_adapter_checker.hpp`（该文档与源文件同目录）。
- 适用场景：用于路由/分发层，在向网络实体发送数据前，根据注册的 adapter 策略判断是否允许发送。

## 主要职责与行为
- `sender_adapter_checker` 是一个无状态工具型结构，提供若干静态和实例方法用以检查发送许可：
  - `pro_s_chk_send_enable<Data, NetEntityPtr>(NetEntityPtr pentity)`：静态模板，基于 `Data` 类型（发送数据类型）查询实体的 `adapter_mgr` 是否允许 `E_to_src`（到源）方向的适配器。
  - `pro_s_chk_send_enable<NetEntityPtr, ID>(NetEntityPtr pentity, const ID& id)`：静态模板，用给定的 `id`（通常为 adapter id）调用 `adapter_mgr::check_enable_adapter(id, tag_send, E_to_src)` 检查对应适配器是否启用发送。

- 对外 operator 与重载：
  - `operator()(NetEntityPtr pentity, const Key&, const NetInfo&, const Data&, const Handler&)`：默认的检查入口，基于 `Data` 类型调用 `pro_s_chk_send_enable`（使用 `id_parser_type` 与 `adapter_mgr_type` 的 tag_send 类型）。
  - `send_packet(NetEntityPtr pentity, const Key&, Pak& pak, const Handler&)`：从 `Pak` 中解析 `tag_send` 对应的 id，并调用 `pro_s_chk_send_enable(pentity, id)`。
  - `send_packet(NetEntityPtr pentity, const Key&, const Pak& pak)`：常量重载，行为与上面类似但不接受 handler。

- 依赖与假设：
  - 假设 `NetEntityPtr::value_type` 定义了 `adapter_mgr_type` 和 `adapter_mgr_ptr_type`。
  - 假设 `adapter_mgr_type` 提供：`check_enable_adapter(id, tag, reg_def_type::E_to_src)` 以及 `template check_enable_adapter<Data>(reg_def_type::E_to_src)` 等接口。
  - 使用 `adapter::adapter_register_type_def` 中的常量（如 `E_to_src`）表示方向。

## 模板/类型细节
- `reg_def_type`：别名为 `adapter::adapter_register_type_def`，用于取得方向常量（send/recv/both）。
- `tag_def_type`：别名为 `adapter::adapter_default_tag_def`，用于取得默认 tag（如 `E_tag_send`）。
- `id_parser_type`：从 `adapter_mgr_type::id_parser_type` 获取，用来从包（`Pak`）中解析对应的 adapter id（例如 `parser.template value_id<tag_send_type>(pak)`）。

## 使用示例（伪代码）
```cpp
using checker_t = yggr::network::sender_checker::sender_adapter_checker;

// 假设 pentity 是 std::shared_ptr<NetEntity>
checker_t chk;

// 通用检查（基于 Data 类型）
bool ok = chk(pentity, key, netinfo, data, handler);

// 通过包检查（解析包内 id）
bool ok2 = chk.send_packet(pentity, key, pak, handler);

if(!ok2) {
    // 目标实体未启用对应适配器，取消发送
}
```

## 注意事项与建议
- `sender_adapter_checker` 只负责查询适配器是否启用发送，不负责实际的发送或错误处理。
- `id_parser_type` 的行为依赖于 `adapter_mgr` 的实现：如果 `parser.template value_id<tag_send_type>(pak)` 抛出或返回无效 id，`pro_s_chk_send_enable` 可能返回 false。上层应对包解析异常或无效 id 做容错处理。
- `NetEntityPtr` 可以为空指针，代码中对 `pentity` 做了空检查：当 `pentity` 为空或 `get_adapter_mgr_ptr()` 返回空时会返回 false（表示不可发送）。
- `send_packet` 的两个重载支持非常相似的语义：一个用于可修改包并带 handler 的场景，另一个用于只读包检查。

