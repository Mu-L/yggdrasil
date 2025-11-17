# `yggr::network::heart::heart_dst_fixer`（文件：`heart_dst_fixer.hpp`）

## 概要
- **目的**：`heart_dst_fixer` 用于处理心跳（heart）包并维护会话（session）在线状态。它提供两类操作：
  - 在收到数据包时判断是否为心跳包并作出相应响应（`check_packet`）；
  - 在定期心跳检查流程中根据当前状态推进状态机（`check`）。
- **位置**：`yggr/network/heart/heart_dst_fixer.hpp`（与该文档同目录）。
- **模板参数**：
  - `Heart_Data`：心跳包的数据类型（例如 `heart_data`），该类型必须提供静态 `data_info()` 与 `size()`、`set_last()` 等接口以供判断与更新。

## 主要接口说明
### 模板结构
```cpp
template<typename Heart_Data>
struct heart_dst_fixer
{
    typedef Heart_Data heart_data_type;
    ...
};
```

### check_packet
原型：
```cpp
template<typename Def, typename Packer, typename SessionPtr>
std::pair<u32, bool> check_packet(const Packer& pak, SessionPtr sptr) const;
```
行为摘要：
- 首先断言 `sptr` 非空。
- 如果 `pak.data_info() == heart_data_type::data_info()`（即包是心跳包）：
  - 尝试 `pak.load(hd)` 将包加载为 `heart_data_type hd`；加载失败则返回 `(Def::s_offline(), false)`。
  - 要求 `hd.size() == 1`（文件中断言），否则视为非法并返回 `(Def::s_offline(), false)`。
  - 成功时调用 `hd.set_last()`（将 last 时间点设为 now），构造 `send_data_type sdata(owner_info_type(sptr->get_id()), hd)` 并调用 `sptr->send_packet(sdata)`（向对端回发 heart 包或 ack）。
  - 返回 `(Def::s_online(), false)` —— 表示会话为在线，且包已消费（第二值 `false` 表示不需要进一步处理/转发）。
- 若非心跳包，返回 `(Def::s_online(), true)` —— 表示会话保持在线，且该包应该继续按常规处理（`true` 表示可继续处理）。

类型依赖说明（在函数体内）：
- `session_ptr_type`：与 `SessionPtr` 对应。
- `session_type`：由 `mplex::pointer_to_value_t<session_ptr_type>::type` 得到（指针所指的实际会话类型）。
- `send_data_type`：`session_type::send_data_type`，用于构建要发送/回包的数据。
- `owner_info_type`：`send_data_type::owner_info_type`，用于填充发送数据的所有者 ID（`sptr->get_id()`）。

语义提示：`check_packet` 返回的 `std::pair<u32,bool>` 含义通常为 `(new_state, should_continue_processing_packet)`，其中 `new_state` 来自 `Def`（协议定义）提供的状态常量。

### check
原型：
```cpp
template<typename Def, typename State, typename SessionPtr>
void check(State& state, SessionPtr sptr) const;
```
行为摘要：
- 若 `sptr` 为空则直接返回。
- 若 `state == Def::s_online()`：把状态改为 `Def::s_need_check()`（表示下一轮需要检查）。
- 若 `state == Def::s_need_check()`：把状态改为 `Def::s_offline()`（表示在两轮内未收到心跳，判为离线）。
- 否则调用 `sptr->handler_close_level_error()`（处理未知/错误状态）。

状态变更通过私有成员 `change_state` 执行，使用原子比较交换以保证并发下的状态修改正确。

### change_state（私有）
原型：
```cpp
template<typename State>
void change_state(State& sat, u32 new_sat) const;
```
实现要点：
- 以 `old_sat = sat.load()` 开始循环，调用 `sat.compare_exchange_weak(old_sat, new_sat)` 尝试将状态从 `old_sat` 变为 `new_sat`，直到成功或发现 `old_sat == new_sat`。
- 要求 `State` 提供 `load()` 与 `compare_exchange_weak(old,new)` 接口（例如 `std::atomic<u32>` 或项目中等效的原子类型）。

## 依赖与假设
- 头文件包含 `yggr/mplex/pointer_to_value_t.hpp`，用于从智能指针类型 `SessionPtr` 推断 `session_type`。
- `Def`（协议定义）需提供静态方法/常量：`s_offline()`, `s_online()`, `s_need_check()` 等，用来表示会话状态值。
- `Packer` 必须提供 `data_info()` 与 `load(...)` 接口；`heart_data_type::data_info()` 用于包类型判断。
- `SessionPtr` 指向的 `session_type` 必须提供：
  - `send_packet(send_data_type)` 或 `send_packet(...)` 方法，以便回发心跳；
  - `get_id()` 方法，以便创建 `owner_info_type`；
  - `handler_close_level_error()` 用于错误处理（`check` 中调用）。

## 使用示例（伪代码）
```cpp
// 在接收包处理流程中：
auto result = heart_fixer.check_packet<MyDef>(packet, session_ptr);
// result.first == new state, result.second == should_continue
if(!result.second) {
    // 心跳包已处理，不再继续常规处理
    session_state.store(result.first);
} else {
    // 常规包，继续其他处理
}

// 在周期性心跳检查任务中：
heart_fixer.check<MyDef>(session_state, session_ptr);
// check 会根据当前 state 做推进（online -> need_check -> offline）或触发关闭
```

## 注意事项与建议
- `assert(sptr)`：`check_packet` 假定 `sptr` 非空并断言；在生产代码或不可信输入时应更稳健地处理空指针。
- `hd.size() == 1` 的强制性：源文件中对心跳数据长度做了断言并在不满足时返回离线，确保发送方的 `heart_data` 格式符合约定。
- 并发安全：
  - `change_state` 使用原子 CAS，适用于 `State` 为原子类型的场景；但对 `SessionPtr` 的访问（如 `send_packet`）的并发安全取决于 session 实现，应在上层保证互斥或线程安全。
- 返回值语义：`check_packet` 的 `bool` 标记可用于决定是否交给后续层继续处理当前数据包。

