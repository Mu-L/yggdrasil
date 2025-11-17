# `yggr::network::heart::heart_timer_task_pak`（文件：`heart_timer_task_pak.hpp`）

## 概要
- **目的**：提供一个定时器任务包装，用于周期性触发服务器的心跳检查（`check_state()`），便于把心跳检测任务放入定时器或任务调度器中执行。
- **位置**：`yggr/network/heart/heart_timer_task_pak.hpp`（与该文档同目录）。
- **适用场景**：在服务器端的定时任务线程或调度器中定期运行心跳检查逻辑（例如清理超时会话、发送心跳或维护会话状态）。

## 类型定义与模板参数
```cpp
template< typename ServerPtr >
class heart_timer_task_pak
```
- `ServerPtr`：服务器指针类型（智能指针或原始指针）。被假定为支持无参成员函数 `check_state()`。

内部别名（实现内）：
- `state_type`：`yggr::time::timer_task_state`（用于表明任务是否运行）。
- `time_type`：`yggr::time::time`（时间/间隔类型）。
- `timer_type`：`yggr::time::timer<time_type>`（内部计时器用于计算 elapsed）。

## 构造与成员
```cpp
heart_timer_task_pak(server_ptr_type psvr, const time_type& step)
```
- `psvr`：服务器指针，构造时断言非空。
- `step`：时间步长，表示两次触发之间的最小间隔。

成员字段：
- `_psvr`：保存服务器引用/指针。
- `_step`：保存步长。
- `_timer`：内部计时器，用于判断是否超过步长。

## operator() 行为
```cpp
inline u32 operator()(void);
```
- 每次调用检查 `_timer.elapsed()` 是否大于 `_step`。
  - 如果已超过 `_step`：调用 `_psvr->check_state()`，重启计时器（`_timer.restart()`），并返回 `timer_task_state::E_timer_task_ran`（表示任务已执行）。
  - 否则返回 `timer_task_state::E_timer_task_not_ran`（表示未达到触发条件）。

返回值说明：上层任务调度器可以根据返回值判断该任务是否真正执行并据此统计或管理任务。 

## 使用示例
```cpp
#include <memory>
#include <yggr/network/heart/heart_timer_task_pak.hpp>

// 假设 MyServer 提供 void check_state();
using ServerPtr = std::shared_ptr<MyServer>;
using Task = yggr::network::heart::heart_timer_task_pak<ServerPtr>;

ServerPtr server = std::make_shared<MyServer>();
// 假设 time_type 提供 seconds 工厂函数或构造
auto step = yggr::time::time::seconds(5); // 示例构造，具体接口以 yggr::time::time 为准
Task task(server, step);

// 在定时器/循环中调用：
while(running) {
    auto res = task();
    if(res == yggr::time::timer_task_state::E_timer_task_ran) {
        // 处理已运行后的逻辑或记录
    }
    // 等待或休眠至下一次调度
}
```

说明：`time::time` 的具体构造/单位接口以项目实现为准，上例仅示意如何传入步长。

