**start_data_def.hpp 文档**

简介：
- `start_data_def.hpp` 定义了项目中 start_data（启动数据）使用的 ID 范围常量以及用于检查 start_data ID 是否在合法范围内的宏。

主要内容：
- 结构体 `start_data_def`：
  - `E_id_start`：起始 ID 常量，值为 `0x00008000`。
  - `E_id_end`：结束 ID 常量，值为 `0x00008100`。
- 宏 `YGGR_PP_CHECK_START_DATA_ID(__id__)`：
  - 用途：检查给定的 start_data ID 是否在 [E_id_start, E_id_end)（或项目约定的范围）内。
  - 实现：基于 `YGGR_PP_IS_IN_RANGE`（来自预处理辅助）并传入 `start_data_def` 的范围值。

用途与约定：
- 所有自定义的 start_data 类型在声明或注册时应使用该宏（或在宏中使用该 ID 范围）来确保其 ID 位于项目分配的范围内。示例：`YGGR_PP_CHECK_START_DATA_ID(E_pak_id);`。
- 该文件为 start_data 系统提供命名空间隔离（`yggr::network::start_data`），并与序列化及 start_data 注册机制配合使用。

示例（伪代码）：

```cpp
// 在某个 start_data 头文件中：
YGGR_FAST_CAL_TASK_IMPORT_TPL(task_data_info_type, this_type, (start_data_def::E_id_start + 1), 1)
YGGR_PP_CHECK_START_DATA_ID(E_pak_id);
```

注意事项：
- 若需要扩展或划分更多 start_data ID 区间，应在此文件中调整 `E_id_start`/`E_id_end` 或新增更细的子区间常量，并确保不会与其他系统的 ID 冲突。

文件： [yggr/network/start_data/start_data_def.hpp](start_data_def.hpp)
