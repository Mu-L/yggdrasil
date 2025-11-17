# `yggr::network::heart::heart_data`（文件：`heart_data.hpp`）

## 概述
- **目的**：`heart_data` 是用于心跳（heartbeat）包的数据类型封装，保存心跳时间点信息并提供拷贝/移动/交换、序列化和便利访问方法。
- **位置**：`yggr/network/heart/heart_data.hpp`（与该文档同目录）。
- **模板参数**：
  - `Time`：时间类型，默认 `yggr::time::time`。
  - `TaskDataInfo`：任务数据描述类型，默认 `task_center::default_task_data_info_type`（用于任务注册/导入宏）。

## 主要特性与实现要点
- 内部表示：使用 `::yggr::vector<time_type>`（别名为 `_tm_vt`）来记录时间戳：
  - 构造时在 `_tm_vt` 中至少放入一个默认构造的时间点（开始时间占位）。
  - 当只存在一个元素时，表示仅有起始时间；若存在两个元素，第二个为最近时间点（last）。

- 宏/序列化/任务导入：
  - 使用宏 `YGGR_FAST_CAL_TASK_IMPORT_TPL(task_data_info_type, this_type, (heart_packet_def::E_id_start + 1), 1);` 将该类型注册为一个任务导入/包定义（包含包 ID 与版本号）。
  - 紧接 `YGGR_PP_CHECK_HEART_PACKET_ID((this_type::E_pak_id));` 用于在预处理/编译期检查包 ID 的合法性（项目内部宏校验）。
  - 提供 `serialize(Archive& ar, const u32 version)` 函数，使用 `yggr::serialization`（NVP）序列化 `_tm_vt`。

- 拷贝/移动管理：
  - 支持 Boost 风格的可拷贝/可移动（`BOOST_COPYABLE_AND_MOVABLE(this_type)`）并重载移动/拷贝构造与赋值运算符。
  - 使用 `copy_or_move_or_swap` 与 `boost::move` 在移动赋值中高效迁移数据。
  - 提供成员 `swap`（接受右值引用或左值引用的两种重载），并在命名空间 `swap_support` 中提供非成员 `swap` 以便 ADL（并在 `std` / `boost` 中导入）。

- 时间/接口函数：
  - `size()`：返回 `_tm_vt.size()`。
  - `set_start()`：将 `_tm_vt[0]` 设为当前时间（默认构造的 `time_type()` 表示 now）。
  - `set_last()`：如果 `_tm_vt` 只有一个元素则 push_back(now)，否则将 `_tm_vt[1]` 设为当前时间。
  - `start()` / `last()`：返回对应时间，`last()` 在只有一个元素时返回 `time_type(0)`。
  - `tm_step()`：返回间隔 `last - start`（在只有一个元素时返回 `time_type(0)`)。

## 公有类型别名
- `time_type` —— 第一个模板参数 `Time`。
- `task_data_info_type` —— 第二个模板参数 `TaskDataInfo`。

## 序列化与版本控制
- `serialize(Archive&, const u32 version)` 仅序列化 `_tm_vt`（`YGGR_SERIALIZATION_NVP(_tm_vt)`）。
- 构造/宏中指定了包 ID 与版本（见 `YGGR_FAST_CAL_TASK_IMPORT_TPL` 的参数），在网络协议/任务中心中用于向后兼容性与识别。

## swap 支持（非成员）
- 在 `yggr::network::heart::swap_support` 中定义了通用 `swap(heart_data<...>&, heart_data<...>&)`，并通过 `using` 导入至 `std` 与 `boost` 命名空间，方便与标准 `swap` 协同使用。

## 使用示例
```cpp
#include <iostream>
#include <yggr/network/heart/heart_data.hpp>

using hd = yggr::network::heart::heart_data<>; // 使用默认 time 与 TaskDataInfo

int main() {
    hd h;
    // 初始只有 start
    std::cout << "size=" << h.size() << "\n"; // 1

    h.set_start(); // reset start to now
    h.set_last();  // set last to now (push_back if needed)

    auto s = h.start();
    auto l = h.last();
    auto step = h.tm_step();

    std::cout << "step: " << step.total_milliseconds() << " ms\n"; // 假设 time_type 有该方法

    // 交换示例
    hd a, b;
    yggr::network::heart::swap(a, b); // ADL 支持
}
```

说明：示例使用 `time_type` 的 `total_milliseconds()` 作为演示；实际时间 API 取决于 `yggr::time::time` 实现。

## 注意事项与最佳实践
- 空/边界语义：
  - `start()` 假定 `_tm_vt` 非空（构造函数保证了这一点）；调用前无需检查 `_tm_vt.empty()`，但若你以非典型方式构建对象请注意。
  - `last()` 在只有一个元素时返回 `time_type(0)`（用于表示未设置 last）。

- 版本与兼容性：
  - 因为序列化只包含 `_tm_vt`，后续版本若需要添加字段请维护 `YGGR_FAST_CAL_TASK_IMPORT_TPL` 中的版本号以保证反序列化兼容。

- 移动语义：
  - 移动构造与移动赋值已实现，尽量在需要时使用右值语义以获得更好性能。

- 线程/并发：
  - `heart_data` 本身不是线程安全的（包含可变容器 `_tm_vt`）。当多个线程可能并发访问/修改同一实例时，请外部同步（锁或其他并发策略）。
