**session_creator.hpp 文档**

简介：
- `session_creator` 是一个用于根据启动数据（`Start_Data`）和连接对象（`Conn`）创建会话（`Session`）实例的模板类。它协调 ID 生成、checker/crypher 的创建、选项设置以及连接生命周期管理。

模板参数：
- `Start_Data`：启动会话时使用的数据类型。
- `Conn`：连接类型（`conn_type`），通常由 `shared_ptr<Conn>` 包装。
- `ID_Creator`（可选）：用于根据 `Start_Data` 生成会话 ID 的类型，默认 `session_id_creator<Start_Data>`。
- `Checker_Creator`（可选）：用于生成 session checker 的类型，默认 `session_checker_creator<Start_Data>`。
- `Crypher_Creator`（可选）：用于生成 session crypher 的类型，默认 `session_crypher_creator<Start_Data>`。
- `Options_Setter`（可选）：用于在创建后设置/验证会话选项的策略类型，默认 `default_options_setter_type`。

主要类型别名：
- `start_data_type`、`conn_type`、`conn_ptr_type`、`id_creator_type`、`checker_creator_type`、`crypher_creator_type`、`options_setter_type`。

主要成员与行为：
- 构造：
  - `session_creator(const conn_ptr_type& pconn, start_data_type start_data)`：接受连接指针和启动数据，并保存为内部状态。
- `create<SessionPtr, AdapterMgrPtr>(padp_mgr) -> SessionPtr`：创建 `Session` 的关键方法。
  - 要求：`SessionPtr` 指向的 `session_type` 的 `conn_ptr_type` 必须与 `conn_ptr_type` 相同（通过静态断言验证）。
  - 流程：
    1. 若 `_pconn` 为空则返回空 `SessionPtr`。
    2. 使用 `id_creator_type` 生成会话 ID（`sid = idc(_start_data)`）；若 `sid` 无效则关闭连接并返回空。
    3. 使用静态（共享）创建器：`chc`（checker_creator）和 `crc`（crypher_creator）、以及 `opt_setter`（options_setter）。
    4. 分配并构造 `session_type`，传入 `sid`、`_pconn`、`padp_mgr`、`chc(_start_data)`、`crc(_start_data)` 以及本地/远端 endpoint 信息。
    5. 若构造成功，则调用 `opt_setter(*sptr)` 进行可选设置/验证。若设置失败则关闭会话并返回空。
  - 异常与失败处理：构造或 ID 生成失败时会关闭 `_pconn` 并返回空 `SessionPtr`。
- `cancel()`：关闭内部连接 `_pconn`。
- `get()`：返回当前 `_pconn`。
- `start_data()`：访问（非 const / const）启动数据。

线程与生命周期注意：
- `_pconn` 被声明为 `mutable`，并由 `create` 在成功/失败路径中管理其所有权（例如关闭连接）。
- `create` 中使用 `yggr_nothrow_new` 与 `session_ptr_type` 封装的异常安全路径，确保出现异常时连接被关闭以避免泄露。

自定义扩展：
- 通过提供自定义的 `ID_Creator`、`Checker_Creator`、`Crypher_Creator` 或 `Options_Setter`，可以改变会话 ID 的生成规则、checker/crypher 的初始化以及创建后的选项验证行为。

示例（伪代码）：

```cpp
using my_session_creator = yggr::network::session_helper::session_creator<MyStartData, MyConn>;
my_session_creator creator(pconn, start_data);
auto session_ptr = creator.create<MySessionPtr>(adapter_mgr_ptr);
if(session_ptr) {
    // 会话创建成功
}
```

swap 支持：
- 提供 `swap(session_creator& l, session_creator& r)` 在 `yggr::network::session_helper::swap_support` 命名空间中，并导入到 `yggr::network::session_helper`、`std` 与 `boost` 名下，便于通用 `swap` 调用。

文件： [yggr/network/session_helper/session_creator.hpp](session_creator.hpp)
