# `yggr::network::session_state::session_state_def`（文件：`session_state_def.hpp`）

## 概述
- 目的：定义会话状态相关的常量集合与可配置的状态描述模板 `session_state_def`，为会话管理逻辑提供统一的状态常量与查询接口。
- 位置：`yggr/network/session_state/session_state_def.hpp`（本文档与源文件同目录）。
- 适用场景：用于会话生命周期管理（offline / need_check / online）以及作为其他模板（如 `session_state_checker`）的 `Def` 参数。

## 主要定义
### `struct tag_def`
- 常量：
  - `E_session_state_offline = 0`：离线状态。
  - `E_session_state_need_check = E_session_state_offline + 1`：需要检查的状态（例如进入需要校验或确认的中间态）。
  - `E_session_state_online = E_session_state_offline + 2`：在线状态。
  - `E_session_state_end = E_session_state_offline + 3`：状态结束标记（上界，用于静态断言/范围检查）。

用途：`tag_def` 提供一组基础常量供默认别名与宏展开时使用。

### 模板 `session_state_def<init>`
- 模板参数：
  - `u32 init`：初始状态值，必须在 `[E_session_state_offline, E_session_state_end)` 范围内。

- 导出常量（与 `tag_def` 相同）：
  - `E_session_state_offline`、`E_session_state_need_check`、`E_session_state_online`、`E_session_state_end`。

- 静态编译断言：
  - 使用 `BOOST_MPL_ASSERT` 验证 `init >= E_session_state_offline && init < E_session_state_end`，保证模板参数在合法范围内。

- 静态方法：
  - `static u32 s_init()`：返回模板参数 `init`，表示该配置的初始状态值。
  - `static u32 s_online()`：返回 `E_session_state_online`。
  - `static u32 s_need_check()`：返回 `E_session_state_need_check`。
  - `static u32 s_offline()`：返回 `E_session_state_offline`。

用途：`session_state_def` 将 `init` 与一组命名常量绑定，供会话管理与状态机使用。

## 行为与约束
- 编译期检查：如果传递给 `session_state_def` 的 `init` 参数超出有效范围，会在编译期触发 `BOOST_MPL_ASSERT`，避免在运行时出现无效状态定义。
- 语义清晰：通过 `s_init()` / `s_online()` 等静态方法，调用方可以以统一方式读取状态常量，而不用直接依赖魔法数字。

## 使用示例（伪代码）
```cpp
// 定义某个会话初始状态为 online
using my_state_def = yggr::network::session_state::session_state_def<yggr::network::session_state::tag_def::E_session_state_online>;

static_assert(my_state_def::s_init() == yggr::network::session_state::tag_def::E_session_state_online, "init should be online");

u32 cur = my_state_def::s_init();
if(cur == my_state_def::s_online()) {
    // 会话被认为是在线的
}

// 在模板中作为 Def 参数
using checker_t = yggr::network::session_state::session_state_checker< my_state_def, my_checker >;
```

## 设计注意事项与建议
- 当扩展状态集合时（例如添加 `E_session_state_connecting` 等），应调整 `E_session_state_end` 的表达式并同时更新所有依赖该范围断言的代码路径。
- 使用 `session_state_def` 的好处是集中管理状态数字与语义名称；建议所有会话/状态机相关代码都通过该模板或 `tag_def` 访问状态常量，而不要直接使用硬编码的数值。
- `BOOST_MPL_ASSERT` 在模板实例化阶段进行检查，是防御性设计的一部分，能尽早暴露配置错误。

