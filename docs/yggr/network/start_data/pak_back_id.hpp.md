**pak_back_id.hpp 文档**

简介：
- `pak_back_id` 是一个简单的启动数据（Start Data）模板类型，用于在会话/连接建立流程中携带目标会话 ID（back id）。它可被序列化并集成到项目的 start_data 生成/加载框架中。

模板参数：
- `ID`：表示会话或目标 ID 的类型（例如整型或自定义 id 类型）。
- `TaskDataInfo`（可选）：任务/数据描述信息类型，默认为 `task_center::default_task_data_info_type`，用于与任务中心集成（包含 start_data 的 ID 与版本信息）。

主要常量与类型：
- `id_type`：等同于模板参数 `ID`。
- `task_data_info_type`：等同于 `TaskDataInfo`。

序列化与版本：
- 使用 `yggr::serialization` 的 `serialize(Archive&, u32)` 函数序列化 `_id` 字段。
- 使用宏 `YGGR_FAST_CAL_TASK_IMPORT_TPL` 声明该 start_data 的标识（文件中为 `start_data_def::E_id_start + 1`，版本为 1）。

构造与赋值：
- 默认构造：`pak_back_id()`，将 `_id` 设为默认值。
- 显式构造：`pak_back_id(const id_type& nid)`，用给定 ID 初始化。
- 支持移动与拷贝构造/赋值，并提供 `swap()` 与 `std`/`boost` 的 `swap` 支持。

访问器：
- `const id_type& id() const`：返回内部的 ID 值。

start_data 框架集成：
- 实现了 `start_data_generator<pak_back_id>`：调用 `generator(id)` 将返回一个以该 `id` 初始化的 `pak_back_id` 实例。
- 实现了 `start_data_loader<pak_back_id>`：从包（Packet）中 `pak.load(sdata)` 恢复数据实例。

使用示例（伪代码）：

```cpp
using S = yggr::network::start_data::pak_back_id<std::uint64_t>;
S s = yggr::network::start_data::start_data_generator<S>()(some_id);
auto id = s.id();
```

注意事项：
- `pak_back_id` 为轻量类型，主要用于传递目标 ID；若需要携带额外的认证/密钥信息，请参见 `encryption_pak_back_id` 等更复杂的 start_data 类型。
- 确保在序列化/反序列化时包含相应的 `yggr::serialization` 注册/访问支持。

文件： [yggr/network/start_data/pak_back_id.hpp](yggr/network/start_data/pak_back_id.hpp)
