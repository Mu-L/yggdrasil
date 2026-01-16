**balance_io_service.hpp 文档**

简介：
- `balance_io_service.hpp` 定义了模板类 `balance_io_service<Service>`，用于在 `Service`（通常为 `io_service` 或类似的事件/工作服务）上维护一个原子计数，支持基于该计数的比较操作，用于在多服务场景下实现负载均衡选择策略。

主要类型与行为：
- `balance_io_service<Service>`：继承自 `Service`，并增加了私有成员 `boost::atomic<u64> _count`，用于记录当前“负载”或引用计数。
  - 构造：默认构造将 `_count` 初始化为 `1`；也提供带 `concurrency_hint` 的显式构造（转发给 `Service` 构造函数）。
  - 类型转换：提供 `operator base_service_type&()` 和 `org_service()` 访问底层 `Service` 实例。
  - 计数操作：`ex()` 增加计数，`unex()` 减少计数；`count()` 返回当前计数值。
  - 比较接口：
    - `template<typename OService> s32 compare(const balance_io_service<OService>& right) const`：比较两个 `balance_io_service` 的计数，返回 -1/0/1。支持不同 `Service` 模板参数间的比较（以 `count()` 为依据）。
    - `compare_eq(...)`：判断计数是否相等（或是否为同一对象）。

- 非成员运算符：库提供跨模板参数的比较操作符（`==`, `!=`, `<`, `<=`, `>`, `>=`），均基于上述 `compare`/`compare_eq` 接口实现，便于在容器或选择器（如 `balance_io_service_selector`）中使用。

用途与示例：
- 将多个 `balance_io_service` 实例放入集合（如 `std::vector<shared_ptr<balance_io_service<io_service>>>`），通过比较计数选择最空闲的服务：

```cpp
// 伪代码
std::vector<yggr::shared_ptr<yggr::network::balance_io_service<boost::asio::io_service>>> svs = /* init */;
// 选择最小 load 的服务
auto it = std::min_element(svs.begin(), svs.end(), [](auto &a, auto &b){ return *a < *b; });
(*it)->ex(); // 分配一个任务
// 任务完成后
(*it)->unex();
```

注意事项：
- `_count` 初始值为 `1`（而非 0），因此计数语义为“基线 + 当前负载”，使用者应按此设计分配/释放计数。
- `ex()` 和 `unex()` 未做边界检查（例如避免下溢），调用方应保证调用配对性。
- 该类继承自 `Service`，因此构造时可传递 `concurrency_hint` 给基类（若 `Service` 支持）。
- 在并发场景中，计数为原子类型以保证线程安全，但对复杂负载衡量可能需要更细粒度的指标（如队列长度、任务等待时间等）。

相关文件：
- [yggr/network/balance_io_service_selector.hpp](balance_io_service_selector.hpp)
