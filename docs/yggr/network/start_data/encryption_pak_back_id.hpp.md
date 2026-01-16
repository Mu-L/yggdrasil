**encryption_pak_back_id.hpp 文档**

简介：
- `encryption_pak_back_id` 是一个模板化的启动数据（Start Data）类型，用于在会话/连接建立流程中携带目标会话 ID 与用于加密/验证的固定长度密钥（back id + key）。它继承自任务数据描述类型，可被序列化和通过项目的 start_data 生成/加载机制创建。

模板参数：
- `ID`：表示会话或目标 ID 的类型（如整型、字符串或自定义 id 类型）。
- `Key`：密钥容器类型（支持 `begin()`/`end()`、`size()` 和构造/赋值，例如 `yggr::ids::id_n<N>` 或 `std::vector<u8>`）。
- `key_len`：编译期常量，指定密钥长度（字节数）。
- `TaskDataInfo`（可选）：任务/数据描述信息模板基类，默认使用 `task_center::default_task_data_info_type`，用于与任务中心集成（包含 ID、版本等元信息）。

主要常量与类型：
- `E_key_len`：静态常量，等于模板参数 `key_len`。
- `id_type`、`key_type`：分别为 `ID` 与 `Key`。
- `task_data_info_type`：继承的任务数据元类型。

序列化与版本：
- 通过 `yggr::serialization::access` 提供 `serialize(Archive&, u32 version)`，序列化字段为 `_id` 与 `_key`。
- 使用宏 `YGGR_FAST_CAL_TASK_IMPORT_TPL` 声明了 start data 的 ID（注：文件中注释显示 E_pak_id = start_data_def::E_id_start + 2，版本为 1）。

构造与赋值：
- 默认构造：`encryption_pak_back_id()`，将 `_id` 设为默认值。
- 值构造：`encryption_pak_back_id(const id_type& nid, const key_type& nkey)`，将 `nid` 与 `nkey` 复制/转换为内部 `_id` 与 `_key`（并断言 `_key.size() == E_key_len`）。
- 支持移动构造/赋值与拷贝构造/赋值，并提供 `swap()` 辅助函数与 `std`/`boost` 的 `swap` 重载支持。

访问器：
- `const id_type& id() const`：返回 ID。
- `const key_type& key() const`：返回密钥容器。

start_data 框架集成：
- 实现了 `start_data_generator<encryption_pak_back_id>`：当调用 generator(id) 时，会使用 `yggr::ids::id_generator` 生成一个固定长度的随机/伪随机密钥（`pwd_cont_type`），并返回带该密钥的 `start_data`。
- 实现了 `start_data_loader<encryption_pak_back_id>`：从包（Packet）中 `pak.load(sdata)` 恢复数据实例。

使用示例（伪代码）：

```cpp
// 通过 generator 创建 start_data
using S = yggr::network::start_data::encryption_pak_back_id<std::uint64_t, yggr::ids::id_n<16>, 16>;
S s = yggr::network::start_data::start_data_generator<S>()(some_id);

// 访问字段
auto id = s.id();
auto key = s.key();
```

注意事项：
- `key_type` 必须支持通过 `begin()/end()` 构建内部 `_key`，且 `nkey.size()` 必须等于模板参数 `key_len`，否则构造时会触发断言。
- 该类型依赖项目的任务数据导入/导出与序列化机制（`YGGR_FAST_CAL_TASK_IMPORT_TPL`、`yggr::serialization`），确保在使用时包含相应的注册与序列化支持。
- `start_data_generator` 使用 `yggr::ids::id_generator` 来生成密钥容器，生成策略可根据实际需求替换为更合适的随机/安全生成器。

文件： [yggr/network/start_data/encryption_pak_back_id.hpp](yggr/network/start_data/encryption_pak_back_id.hpp)
