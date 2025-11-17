# `yggr::network::packets_support::packets_checker`（文件：`packets_checker.hpp`）

## 概述
- 目的：为网络包（packet）提供简易的所有者/来源校验器，用于在接收或路由阶段验证包的 owner_id 是否与期望值匹配，并根据可选时间窗口判断包是否仍然有效。
- 位置：`yggr/network/packets_support/packets_checker.hpp`（本文档与源文件同目录）。
- 适用场景：在网络层或上层逻辑中作为 filter/validator，在把包转发到业务处理前做快速有效性检查。

## 主要组成
- 错误码注册宏：`YGGR_PP_PACKETS_CHECKER_ERROR_MAKER_DEF()`
  - 定义模块名为 `packets_checker`，错误码包含 `E_invalid_packet`，对应消息为 `"invalid_packet"`。
- `basic_owner_info_parser<OwnerInfo>`：
  - 模板帮助适配包类型，默认实现会调用 `pak.net_info().owner_id()` 和 `pak.net_info().proxy_id()` 获取 owner/proxy id。
  - 你可以自定义 `OwnerInfo` 或提供自定义 parser 来改变从包中读取 owner id 的逻辑。
- `packets_checker<OwnerInfo, time_step>`：
  - 主体模板：构造时传入期望的 `id_type`（通常是 node id 或会话 id）。
  - `operator()(const Pak& pak)` 返回一个 `error_type`（由 `error_maker_type::make_error(...)` 生成），当校验通过时返回 0（无错），否则返回 `E_invalid_packet`。 
  - 模板参数 `time_step`：
    - 当 `time_step != 0` 时，校验逻辑为：包的 owner_id 等于给定 id 且 `pak.time_alive(time_step)` 为真（表示包在 time_step 时间内有效）则通过，否则视为无效。
    - 当 `time_step == 0`（模板特化）时，仅检查 owner_id 是否匹配，不检查时间。

## API / 行为细节
- 构造函数：
  - `packets_checker(const id_type& id)`：保存期望的 id。
- 调用：
  - `error_type operator()(const Pak& pak) const`：
    - 使用 `owner_id_parser_type::owner_id(pak)` 获取包的 owner id（默认通过 `pak.net_info().owner_id()`）。
    - 若 `time_step == 0`：仅比较 owner id；匹配返回 0；不匹配返回 `error_maker_type::E_invalid_packet`。
    - 若 `time_step != 0`：同时确认 `pak.time_alive(time_step)`（包是否在 allowed 时间范围内）并比较 id；两者都为真时通过，否则返回 `E_invalid_packet`。
- 返回值：
  - 返回值类型 `error_type`（由 `YGGR_PP_PACKETS_CHECKER_ERROR_MAKER_DEF` 定义的 `error_maker_type::make_error(...)` 结果）。

## 使用示例（伪代码）
```cpp
using owner_info = MyOwnerInfo; // 定义 owner_info_type，包含 owner_id_type

// 检查 id，且包在最近 30 秒内有效
packets_checker<owner_info, 30> checker(my_node_id);

MyPacket pak = /* 从网络读取 */;
error_type err = checker(pak);
if(err) {
    // 处理无效包
    LOG_ERROR(err.message());
} else {
    // 接收并处理包
}

// 只检查 owner id（不检查时间）
packets_checker<owner_info, 0> id_only_checker(my_node_id);
```

## 可定制点
- 自定义 owner info 解析器：如果包结构不同，可提供自定义解析器替代 `basic_owner_info_parser`，例如：
  - `struct my_parser { static id_type owner_id(const Pak& p) { ... } }`，并在业务代码中用 `packets_checker<MyOwnerInfoWithCustomParser>`。
- `time_step` 的选择：根据网络延迟与业务需求调整；较短的 `time_step` 可以更严格地丢弃延迟包，较长的 `time_step` 更宽容。

## 注意事项
- `pak.time_alive(time_step)` 的实现由包类型 `Pak` 提供；请确保包类型正确实现该方法并以相同时间单位（通常为秒）返回是否仍然有效。
- `owner_id_type` 的比较语义取决于 `owner_info_type::owner_id_type`（比如整数、GUID 等），确保构造 `packets_checker` 时传入的 id 类型与包中实际存储的类型一致。
- 错误返回使用 `error_maker_type::make_error(...)`，上层可以利用该错误对象记录、转换或传播错误信息。

