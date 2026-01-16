# service_handler.hpp 文档

## 概述
- 文件： [yggr/network/service_handler.hpp](yggr/network/service_handler.hpp#L1-L200)
- 描述：`service_handler<Service,...>` 是对 `io_service_pool` 与 `boost::asio::signal_set` 的封装，负责管理服务池的生命周期、信号注册与处理、以及对外提供服务访问接口。常用于统一控制多个 IO service 驱动的服务实例。

## 模板参数
- `Service`：单个服务的类型（需与 `io_service_pool`/`service` 约定接口）。
- `SignalSet`：信号集类型，默认 `boost::asio::signal_set`。
- `Thread_Config`：线程配置类型，默认 `thread::boost_thread_config_type`。
- `Allocator`、`Saver`、`Selector`：用于 `io_service_pool` 的容器/分配器/选择策略模板，保持与 `io_service_pool` 的相同默认值。

## 主要类型别名
- `signal_set_type`、`service_type`、`thread_config_type`。
- `io_service_pool_type`：`network::io_service_pool<service_type, thread_config_type, Allocator, Saver, Selector>`。
- `init_type`：初始化类型（`size_type`）。

## 构造与析构
- 构造：`service_handler(const size_type& size)` 会创建 `_service_pool(size)` 并用 `_service_pool.get_service()` 初始化 `_sig_set`。
- 析构断言 `_service_pool` 未运行（要求在销毁前调用 `stop()`）。

## 主要方法
- `io_service_pool_type& service_pool()`：访问内部 `io_service_pool`。
- `signal_set_type& signal_set()`：访问信号集。
- `service_type& get_service()`：通过 `service_pool.get_service()` 获取单个服务引用。
- 信号管理：
  - `bool add_signal(u32 sig)`：添加信号并返回是否成功。
  - `bool remove_signal(u32 sig)`：移除信号并返回是否成功。
  - `void clear_signal()`：清空信号集。
  - `template<typename Handler> void set_signal_handler(const Handler& handler)`：注册信号回调，调用 `_sig_set.async_wait(handler)`。
  - `bool cancel_signal_handler()`：取消信号处理并返回是否成功。
- 生命周期控制：
  - `void run()`：启动内部 `io_service_pool`（会创建并启动线程执行服务）。
  - `void stop()`：停止 `io_service_pool`。
  - `void join()`：等待 `_service_pool.join()`（等所有线程完成）。
- 状态查询：`bool is_running() const`。

## 实现要点
- 内部成员 `_service_pool` 必须先于 `_sig_set` 构造（因为 `_sig_set` 以 `_service_pool.get_service()` 初始化）。
- 信号添加/移除/取消都使用 `boost::system::error_code` 以避免抛出异常，并返回操作是否成功。
- `set_signal_handler` 使用异步等待（`async_wait`）与用户提供的回调结合，回调通常用于在接收到信号时调用 `stop()`。

## 使用示例
```cpp
service_handler<MyService> sh(4); // 4 个服务实例
sh.add_signal(SIGINT);
sh.set_signal_handler([&sh](const boost::system::error_code& ec, int sig){ sh.stop(); });
sh.run();
// 程序运行期间处理网络事件
sh.join();
```

## 注意事项
- 在销毁 `service_handler` 前请确保已调用 `stop()` 并等待 `join()`，否则析构断言会触发。
- `SignalSet` 在不同平台上对信号的支持存在差异（例如 Windows 上 `SIGBREAK`），使用时请考虑跨平台兼容性。
- `io_service_pool` 的参数（`Allocator`/`Saver`/`Selector`）可替换以适应不同的服务分配与选择策略。

## 参考
- 源码： [yggr/network/service_handler.hpp](yggr/network/service_handler.hpp#L1-L200)
