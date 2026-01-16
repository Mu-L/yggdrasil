**udp_conn_checker.hpp 文档**

简介：
- `udp_conn_checker.hpp` 定义了 `udp_conn_checker` 模板类，用于生成和验证基于随机值+校验（默认使用 MD5）的连接检查数据，通常作为 UDP 控制数据（start_data）在握手/连接确认流程中使用。

模板参数：
- `Tool`：校验/加密工具类型，默认 `yggr::encryption_tool::md5_tool`。该工具需提供类型别名 `check_type` 及方法 `encrypt(const std::string&)` 返回 `check_type`。
- `TaskDataInfo`：任务/数据包信息类型，默认为 `task_center::default_task_data_info_type`，用于 `YGGR_FAST_CAL_TASK_IMPORT_TPL` 宏注册包 ID/版本信息。

主要成员与语义：
- `val_type _val`：用于存放随机或指定的整数值（用于生成校验）。
- `check_type _chk`：校验值，由 `Tool::encrypt` 对 `_val` 字符串化后的结果生成。

主要接口：
- 构造：
  - `udp_conn_checker()`：默认构造，`_val` 置为 0，`_chk` 空。
  - `udp_conn_checker(int n)`：如果 `n==0` 则使用 `random::gen_random<u32>()` 生成随机值，否则使用指定的 `n`；然后基于 `_val` 产生 `_chk`。
  - 拷贝/移动构造与赋值：支持值语义的拷贝与移动，并提供 `swap` 实现。
- 成员方法：
  - `bool check() const`：重新计算 `_val` 的加密并与 `_chk` 比较，匹配则返回 true。

序列化：
- 类通过 `yggr::serialization::access` 提供 `serialize` 模板方法，对 `_val` 和 `_chk` 进行序列化（NVP 名称分别为 `val`、`chk`，实际名称依序列化宏实现）。

集成细节：
- 此类型在文件中使用 `YGGR_FAST_CAL_TASK_IMPORT_TPL` 宏注册为一个 start_data 包（ID 为 `start_data_def::E_id_end - 1`，版本 `1`）。请参阅 [start_data_def.hpp](../start_data/start_data_def.hpp) 了解 ID 范围约定。
- 文件底部提供 `swap` 的非成员模板（`swap_support::swap`）并将其引入 `std` 和 `boost` 命名空间以支持通用 `swap` 调用。

使用示例：

```cpp
// 创建随机检查器
yggr::network::udp_ctrl_data::udp_conn_checker<> chk; // 随机值
// 验证
if(chk.check()) { /* usually true immediately */ }

// 指定值
yggr::network::udp_ctrl_data::udp_conn_checker<> chk2(12345);
bool ok = chk2.check();
```

注意事项：
- `Tool` 类型必须满足接口约定：提供 `check_type` 别名以及 `encrypt(const std::string&)` 方法。
- `random::gen_random<u32>()` 的实现决定了生成值的分布；若需要可预测性测试，请传入固定 `n`。
- `boost::move` / `YGGR_COPYABLE_AND_MOVABLE` 宏在移动语义上有特定约定，请保持与库其余部分一致。

相关文件：
- [yggr/network/udp_ctrl_data/udp_conn_checker.hpp](udp_conn_checker.hpp)
- [yggr/encryption_tool/md5_tool.hpp](../../encryption_tool/md5_tool.hpp)
- [yggr/network/start_data/start_data_def.hpp](../start_data/start_data_def.hpp)
