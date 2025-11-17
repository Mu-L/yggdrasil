# `yggr::network::heart::heart_timer_task_mixer_pak`（文件：`heart_timer_task_mixer_pak.hpp`）

## 概要
- **目的**：为服务器提供一个基于定时器的心跳任务混合器（timer task mixer），在到达指定时间步长时触发服务器的心跳检查接口。
- **位置**：`yggr/network/heart/heart_timer_task_mixer_pak.hpp`（与该文档同目录）。
- **适用场景**：当需要在定时器线程或任务调度器中周期性运行服务器的心跳检查（例如清理超时会话或广播心跳）时，将该可调用对象作为任务放入定时器/混合任务器执行。

## 定义与模板参数
```cpp
template< typename ServerPtr,
          typename Handler_Tag,
          typename Protocol_Tag>
class heart_timer_task_mixer_pak
```
- `ServerPtr`：服务器指针类型（通常为智能指针或原始指针，必须支持 `->template check_state<Handler_Tag, Protocol_Tag>()` 调用）。
- `Handler_Tag`：用于指定 handler 类型的标签（作为模板参数传递给 `check_state`）。
- `Protocol_Tag`：用于指定协议/协议族的标签（同样传递给 `check_state`）。

内部别名（简要）：
- `state_type`：`yggr::time::timer_task_state`（定时器任务运行状态枚举）。
- `time_type`：`yggr::time::time`（时间/时钟类型）。
- `timer_type`：`yggr::time::timer<time_type>`（用于测量间隔）。

## 构造与成员
```cpp
heart_timer_task_mixer_pak(server_ptr_type psvr, const time_type& step);
```
- `psvr`：服务器实例（必须非空）。
- `step`：周期时间步长，表示两次调用间应等待的最小时间量（类型为 `time_type`）。

成员字段：
- `_psvr`：保存传入的服务器指针。
- `_step`：保存步长值。
- `_timer`：内部计时器，用于测量自上次触发以来的经过时间。

## operator() 行为
```cpp
inline u32 operator()(void);
```
- 每次调用会检查 `_timer.elapsed()` 是否大于 `_step`：
  - 若 `_step < _timer.elapsed()` 为真，则调用 `_psvr->template check_state<Handler_Tag, Protocol_Tag>()` 来执行服务器的心跳检查（或其他定期维护逻辑）；随后调用 `_timer.restart()` 重置计时器，并返回 `timer_task_state::E_timer_task_ran`（表示任务已运行）。
  - 否则返回 `timer_task_state::E_timer_task_not_ran`（表示本次调用未达到触发条件）。

返回值用途：可被上层任务调度器用来判断该任务是否真正执行并据此管理任务生命周期或统计运行情况。

## 使用示例
```cpp
#include <yggr/network/heart/heart_timer_task_mixer_pak.hpp>

// 假设 Server 类定义了模板方法：
// template<typename Handler, typename Protocol> void check_state();

using ServerPtr = std::shared_ptr<MyServer>;
using Mixer = yggr::network::heart::heart_timer_task_mixer_pak<ServerPtr, MyHandlerTag, MyProtocolTag>;

ServerPtr server = /* ... */;
// 设置步长为 5 秒（示意，实际 time_type 构造方式视 yggr::time::time 定义而定）
auto step = yggr::time::time::seconds(5);
Mixer mixer(server, step);

// 在定时器或循环中调用：
while(running) {
    // 调用调度器时，mixer() 返回是否真正执行
    auto state = mixer();
    if(state == yggr::time::timer_task_state::E_timer_task_ran) {
        // 做必要的后续处理或记录
    }
    // 休眠/等待下一次调度
}
```

说明：示例中 `time_type::seconds(5)` 为假定构造方法，具体构造/获取时间间隔的方法取决于 `yggr::time::time` 的实际接口。

