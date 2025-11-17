# `yggr::network::heart::heart_src_fixer`（文件：`heart_src_fixer.hpp`）

## 概要
- **目的**：`heart_src_fixer` 用于在发送/源端维护心跳逻辑：处理接收的数据包（判断是否心跳包）并在周期性检查中发起心跳包或推进状态机。
- **位置**：`yggr/network/heart/heart_src_fixer.hpp`（与该文档同目录）。
- **模板参数**：
  - `Heart_Data`：心跳包的数据类型（例如 `heart_data`），需提供 `data_info()`、`size()` 与默认构造等接口。

## 主要接口说明
### 模板结构
```cpp
template<typename Heart_Data>
struct heart_src_fixer
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
- 断言 `sptr` 非空。
- 若 `pak.data_info() == heart_data_type::data_info()`（包为心跳包）：
  - 尝试 `pak.load(hd)` 将包加载为 `heart_data_type hd`；加载失败返回 `(Def::s_offline(), false)`。
  - 要求 `hd.size() == 2`（文件中断言）；若不满足返回 `(Def::s_offline(), false)`。
  - 成功时返回 `(Def::s_online(), false)`，表示会话在线且数据包被消费（第二值 `false` 表示不继续常规处理）。
- 若非心跳包，返回 `(Def::s_online(), true)`，表示会话在线且该包应继续后续处理。

类型依赖说明：
- `session_type`：由 `mplex::pointer_to_value_t<SessionPtr>::type` 推断。
- 使用 `session_type::send_data_type` 与其 `owner_info_type`；`sptr->get_id()` 用于构造 owner info（当需要发送心跳包时）。

### check
原型：
```cpp
template<typename Def, typename State, typename SessionPtr>
void check(State& state, SessionPtr sptr) const;
```
行为摘要：
- 若 `sptr` 为空则直接返回。
- 若 `state == Def::s_online()`：将状态推进为 `Def::s_need_check()`（下一轮需要检查）。
- 若 `state == Def::s_need_check()`：构造默认 `heart_data_type`，通过 `send_data_type` 封包并用 `sptr->send_packet(sdata)` 发送，然后将状态推进为 `Def::s_offline()`（表示已发送探测，下一轮若仍无响应则离线）。
- 否则调用 `sptr->handler_close_level_error()` 以处理异常状态。

状态修改由 `change_state` 私有方法完成（见下）。

### change_state（私有）
实现要点：
- 使用原子加载和 `compare_exchange_weak` 循环完成无锁更新，以保证在并发环境下状态变更的正确性。
- 要求 `State` 类型提供 `load()` 与 `compare_exchange_weak(old, new)` 接口（例如 `std::atomic<u32>` 或项目等价类型）。

## 语义与依赖
- `Def`（协议定义）：需提供静态状态常量/方法 `s_offline()`, `s_online()`, `s_need_check()` 等以标识会话状态值。
- `Packer`：需实现 `data_info()`（用于类型判断）和 `load(...)`（用于反序列化心跳数据）。
- `SessionPtr`：所指类型需支持 `get_id()`、`send_packet(...)` 和 `handler_close_level_error()` 等操作。
- `mplex::pointer_to_value_t` 被用于从智能指针推断实际 session 类型。

## 使用示例（伪代码）
```cpp
// 在接收包流程中：
auto res = heart_src_fixer.check_packet<MyDef>(packet, session_ptr);
// res.first -> new state; res.second -> should_continue
if(!res.second) {
    session_state.store(res.first);
    // 心跳包已处理
} else {
    // 非心跳包，继续常规处理
}

// 在周期心跳检查中：
heart_src_fixer.check<MyDef>(session_state, session_ptr);
// 当 state==s_need_check 时会发送心跳包并把状态变为 s_offline
```

