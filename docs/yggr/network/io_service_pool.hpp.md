# io_service_pool.hpp 文档

## 概述
- **文件**: [yggr/network/io_service_pool.hpp](yggr/network/io_service_pool.hpp#L1-L400)
- **描述**: `io_service_pool` 是一个通用的 IO service 池管理器模板，负责创建和管理多个 `Service` 实例与对应的 `work` 对象，按策略分配并提供线程组来运行这些服务。适用于需要多线程驱动多个 Boost.Asio 风格服务实例的场景。

## 模板参数
- `Service`：服务类型，需提供 `work` 内部类型、`run()`, `run_one()`, `stop()`, `reset()`, `stopped()` 等接口。
- `Thread_Config`：线程配置类型（默认 `thread::boost_thread_config_type`），该类型需提供 `thread_type` 与 `thread_group_type`。
- `Allocator`：用于分配 `service_ptr_type` / `work_ptr_type` 的分配器模板（默认项目容器分配器）。
- `Saver`：保存 `shared_ptr` 的容器模板，默认使用 `container::vector`。
- `Selector`：选择一个 `service` 的策略模板，默认 `normal_io_service_selector`，可替换为 `balance_io_service_selector` 或自定义策略。

## 关键类型别名
- `service_type` / `work_type`
- `service_ptr_type`：`yggr::shared_ptr<service_type>`
- `work_ptr_type`：`yggr::shared_ptr<work_type>`
- `saver_type`：保存 `service_ptr_type` 的容器
- `work_saver_type`：保存 `work_ptr_type` 的容器
- `selector_type`：由 `Selector<saver_type>` 实例化

## 构造与初始化
- 默认构造：创建一个大小为 1 的 `_saver` 并调用 `prv_init()`。
- 构造(`size_type`)：按指定大小初始化 `_saver`（最小为 1），然后 `prv_init()`。
- 构造(`Saver<size_type,...> params`)：按提供参数集合逐个使用 `Service(size_type)` 构造服务并创建对应的 `work` 对象。
- `prv_init()` / `prv_init(params)`：内部创建 `Service` 实例并为每个服务创建 `work_type`，保存到 `_saver` 和 `_work_saver`。

## 运行与停止
- `void run()`：
  - 使用原子 `_brun` 通过 `compare_exchange_strong` 从 `false` -> `true` 启动；若已在运行则返回。
  - 为 `_saver` 中的每个服务创建线程，调用 `prv_service_run(service_ptr)` 在新线程内循环 `service->run()`。
- `void run_one()`：与 `run()` 类似，但线程调用 `prv_service_run_one(service_ptr)`，循环调用 `service->run_one()`。
- `void stop()`：
  - 原子地设置 `_brun` 为 `false`（前提是当前为 `true`），然后对每个服务调用 `stop()`（若服务存在且未停止）。
  - 调用 `join()` 等待所有线程结束。
  - 遍历服务，若服务已停止则 `reset()` 并再次 `stop()`（代码中包含一处逻辑判断，注意条件检查）。
- `void join()`：等待线程组中所有线程结束。

## 访问器
- `inline bool is_running() const`：返回 `_brun` 的当前值。
- `inline size_type size() const`：返回 `_saver.size()`。
- `inline service_type& get_service()`：通过 `_selector()` 选择一个 `service_ptr_type` 并返回引用（断言指针非空）。

## 异常处理
- `prv_service_run` / `prv_service_run_one` 在循环中捕获 `boost::system::system_error` 与 `compatibility::stl_exception`，并将其封装为项目的 `exception::exception::throw_error`，使用系统错误码 `system_controller::system_code::E_IO_SERVICE_POOL`。

## 实现细节与注意点
- 使用 `yggr::shared_ptr` 管理服务与 work 对象，并在 `_work_saver` 中保存 `work_ptr` 以防止 `io_service` 在没有活跃 work 时退出。
- 线程由 `thread_group_type _trd_group` 管理，创建线程时使用 `boost::bind` 绑定成员函数与 `service_ptr`。
- 原子变量 `_brun` 保证并发启动/停止的安全，`compare_exchange_strong` 用于避免重复启动/停止。
- `prv_service_run` 与 `prv_service_run_one` 在每次循环尾部都会调用 `ps->stop(); ps->reset();`，以保证在异常或 run 返回后服务得到停止与复位；调用者应注意服务的 `reset()`/`stop()` 语义。
- 析构函数断言 `_brun` 为 false，意味着用户应在销毁前显式调用 `stop()` 并 `join()`。

## 依赖
- 项目头：`yggr/base/yggrdef.h`, `yggr/thread/boost_thread_config.hpp`, `yggr/nonable/noncopyable.hpp`, `yggr/smart_ptr_ex/shared_ptr.hpp`, `yggr/ptr_val/ptr_val_operator.hpp`, `yggr/container/vector.hpp`, `yggr/network/normal_io_service_selector.hpp`, `yggr/network/balance_io_service_selector.hpp` 等。
- 使用 `boost::atomic`、`boost::bind`、`boost::system::system_error`。

## 使用示例
```cpp
// 假设 Service 为 yggr::network::io_service_like
io_service_pool<Service> pool(4);
pool.run(); // 启动 4 个服务的线程循环
// ... 使用 pool.get_service() 分发任务
pool.stop();
pool.join();
```

## 建议与注意
- 在销毁 `io_service_pool` 前必须确保调用 `stop()` 并等待线程结束，否则析构会触发断言。
- 若 `Service` 的构造或 `work` 创建可能抛出异常，`prv_init` 会对失败情况断言并跳过该槽位，使用者应确保参数合法或捕获异常。
- 如需自定义服务选择策略，可提供自定义 `Selector` 模板以替代默认 `normal_io_service_selector`。

## 参考
- 源码： [yggr/network/io_service_pool.hpp](yggr/network/io_service_pool.hpp#L1-L400)

---
