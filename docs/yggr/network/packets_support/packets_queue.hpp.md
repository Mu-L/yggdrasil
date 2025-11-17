# `yggr::network::packets_support::opackets_queue`（文件：`packets_queue.hpp`）

## 概述
- 目的：提供一个用于串行化并管理发送包的轻量队列包装器，配合连接对象（`Conn`）的 `exec_send_packet` 接口，实现按顺序发送与后台排队功能。
- 位置：`yggr/network/packets_support/packets_queue.hpp`（本文件与源文件同目录）。
- 适用场景：用于网络 I/O 实现中，将多个发送请求按顺序调度到连接层，避免并发写入冲突。

## 主要类型与结构
- 模板类：`template<typename Conn> class opackets_queue`。
  - `conn_type`：连接/链接类型（需实现 `exec_send_packet` 方法）。
  - `gate_type`：`boost::atomic<bool>`，用于表示“发送门”状态（是否可以直接发送）。

- 内部类：
  - `base_opacket_container`：抽象基类，保存包-处理器二元并定义 `empty()` 与 `send_packet(conn)` 接口。
  - `opacket_container<Pak, Handler>`：具体实现，持有可变 `pak`（mutable，允许在 `send_packet` 中移动/读取）与 handler，`send_packet` 调用 `conn.exec_send_packet(_pak, _handler)`。

- 容器类型：
  - `queue_type`：`safe_container::safe_deque<shared_ptr<base_opacket_container>>`，用于线程安全地保存待发送包容器。
  - `_gate`：原子 boolean，true 表示门打开（可直接发送），false 表示门关闭（需要排队）。

## 行为与方法
- 构造/析构：默认构造把 `_gate` 设为 `true`（可立即发送）。

- `send_packet(conn, Pak& pak, handler)`：
  1. 包装 handler 为 `args_holder` 形式并传给队列的 `using_handler`。
  2. 在 `prv_handler_send_packet` 回调中：
     - 尝试通过 `_gate.compare_exchange_strong(true, false)` 抢占发送门：若成功，则表示当前无正在发送任务，函数返回 `true`，并直接由调用者执行 `conn.exec_send_packet(pak, handler)`；
     - 若失败（已有正在发送），则把 `opacket_container` 构造并 push 到 `base`（队列后端），等待后续 `next_send()` 触发发送。
  3. `send_packet` 的设计使得首次发送走直通路径，后续并发调用进入排队以保证顺序。

- `next_send(conn)`：
  - 从队列 `using_handler` 获取下一个 `base_opacket_container_ptr_type`（`prv_handler_next_send`），如果返回非空，调用 `ptr->send_packet(conn)` 触发下一次发送；如果队列为空，`_gate` 会被设置为 `true`（允许下次直通发送）。

- `clear()`：
  - 通过 `using_handler` 把内部队列内容交换到临时容器并把 `_gate` 设回 `true`，用于关闭/清理时安全清空待发送包并恢复门状态。

## 并发/线程语义
- 线程安全：队列底层使用 `safe_deque` 并通过 `using_handler` 提供与 `prv_handler_*` 的回调机制安全访问内部容器；同时 `_gate` 使用 `boost::atomic<bool>` 做原子抢占，避免竞态。
- 发送保证：本队列保证按入队顺序发送包；当 `_gate` 打开时第一个包直接发送并把门置闭（false），随后包入队；在发送完成后需调用者调用 `next_send` 来继续发送队列中的下一个包（或由连接层在发送完成回调中调用）。
- 可变性的处理：`opacket_container` 中 `_pak` 被声明为 `mutable`，以允许 `send_packet` 在 `const` 上下文中移动/修改包内容。

## 内部回调逻辑细节
- `prv_handler_send_packet(base, pak, any_handler)`：
  - 通过 `utility::args_holder_ref_wrap_static_cast` 拿到 handler 的真实类型指针；若为 null 返回 false。
  - 使用 `_gate.compare_exchange_strong(true, false)` 判断是否抢占到直通发送权限：
    - 成功：`base` 应为空，返回 true（外部会直接发送）。
    - 失败：构造 `opacket_container` 并 `push_back` 到 `base`（队列），返回 false。

- `prv_handler_next_send(base)`：
  - 如果 `base.empty()`：把 `_gate` 置为 `true`（打开门），并返回空；
  - 否则：move 出 `base.front()` 并 pop，返回该容器以供发送。

- `prv_handler_clear(base, out)`：
  - 把 `base.swap(out)`（交换出所有元素），并把 `_gate` 设回 `true`。

## 使用示例（伪代码）
```cpp
using queue_t = yggr::network::packets_support::opackets_queue<MyConn>;
queue_t q;

MyPacket pak = /* fill */;
q.send_packet(conn, pak, [](const boost::system::error_code& ec){
    // send complete handler
});

// 在 send 完成的回调处（由 conn 层实现），应调用：
q.next_send(conn);

// 在关闭连接或清理时：
q.clear();
```

## 注意事项与建议
- `next_send` 必须在每次发送完成后由连接层（或发送完成的 handler）调用，否则队列中的后续包不会被触发发送。
- `send_packet` 在无法分配 `shared_ptr`（`construct_shared` 失败）时会返回 false，从而可能使包被丢弃；上层应检测并处理该失败情况（如重试或记录错误）。
- `handler` 必须至少保持在 `send_packet` 返回后的生命周期里直到发送完成回调触发（handler 被以 `args_holder` 包装并存储/转发）。
- 该实现假设 `conn.exec_send_packet` 是同步触发异步发送或直接进行发送；请阅读连接实现以确保 `next_send` 的调用点正确（通常在发送完成的异步回调中）。

