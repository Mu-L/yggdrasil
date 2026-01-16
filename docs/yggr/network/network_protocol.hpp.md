# network_protocol.hpp 文档

## 概述
- 文件： [yggr/network/network_protocol.hpp](yggr/network/network_protocol.hpp#L1-L421)
- 描述：模板 `network_protocol<Msg, TaskDataInfo, ID, Ver, Cal_T>` 将消息类型 `Msg` 与任务中心的数据描述（`TaskDataInfo`）绑定，用作网络/任务调度中的协议载体。它封装消息实例并提供序列化接口与与其他协议模板的互操作性（复制、移动、赋值、swap 等）。

## 模板参数
- `Msg`：消息数据类型（value 类型）。
- `TaskDataInfo`：任务数据描述类型（用于生成静态 ID/版本/任务计算类型）。
- `ID` / `Ver`：由 `task_data_info_parser<TaskDataInfo>` 导出的静态 `data_id_type` 和 `data_ver_type`。
- `Cal_T`：任务计算类型，默认 `task_center::task_cal_type::E_CAL_FAST`。

## 行为与功能
- 通过宏 `YGGR_CAL_TASK_IMPORT_TPL` 将 `TaskDataInfo` 的 ID/版本与任务计算策略导入到协议类型（用于任务中心互操作）。
- 序列化：提供私有 `serialize(Archive&, u32 version)`，序列化 `_msg` 成员。
- 构造：
  - 支持完备的构造覆盖：转发构造（可变模板或预处理生成重载）、从 `Msg` 的拷贝/移动构造、以及从其它 `network_protocol`（兼容不同 TaskDataInfo/ID/Ver/Cal_T）进行构造。
- 赋值：支持从 `Msg`、其他 `network_protocol`（不同 TaskDataInfo/ID/Ver/Cal_T）的赋值，以及移动/拷贝赋值；实现中使用 `copy_or_move_or_swap` 最小化不必要复制。
- swap：提供对 `Msg` 与不同 `network_protocol` 之间的交换重载，并在 `swap_support` 中导入到 ADL 范围。
- 访问：提供隐式转换到 `msg_type&` / `const msg_type&`，以及 `msg()` 访问器。

## 类型与约束
- `value_type` = `msg_type`。
- 通过 `BOOST_COPYABLE_AND_MOVABLE` 宏启用移动语义兼容性。

## 使用示例
```cpp
// 定义协议类型
using proto_t = yggr::network::network_protocol<MyMsg, MyTaskDataInfo, MyID, MyVer>;

// 构造
proto_t p(msg_instance);

// 序列化（示意）
// ar & p; // 序列化库会通过 private serialize 访问

// 访问消息
MyMsg& m = p.msg();
```

## 注意事项
- `TaskDataInfo` 必须与 `task_center::support::task_data_info_parser` 合作，能导出静态 `data_id_type` 与 `data_ver_type`。
- `serialize` 为私有并由 `yggr::serialization::access` 友元访问。
- 设计允许不同 `network_protocol` 变体之间方便地转换与交换，便于任务中心或网络层对不同版本/数据描述的互操作。

## 参考
- 源码： [yggr/network/network_protocol.hpp](yggr/network/network_protocol.hpp#L1-L421)

---
