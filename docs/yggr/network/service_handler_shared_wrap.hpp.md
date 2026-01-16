# service_handler_shared_wrap.hpp 文档

## 概述
- 文件： [yggr/network/service_handler_shared_wrap.hpp](yggr/network/service_handler_shared_wrap.hpp#L1-L200)
- 描述：`service_handler_shared_wrap<Service_Handler>` 是对 `Service_Handler` 指针的轻量封装，内部保存 `yggr::shared_ptr<Service_Handler>`，并将常用的服务管理接口委托给被包装的实例。用于在需要将 `Service_Handler` 以值语义传递或保存时保持共享所有权与简单代理调用。

## 模板参数
- `Service_Handler`：被包装的服务管理类型，需提供下列成员类型/方法：
  - 成员类型：`signal_set_type`, `service_type`, `io_service_pool_type`。
  - 方法：`service_pool()`, `signal_set()`, `get_service()`, `add_signal(u32)`, `remove_signal(u32)`, `clear_signal()`, `join()`, `set_signal_handler(handler)`, `cancel_signal_handler()`, `is_running()`, `run()`, `stop()`。

## 构造与赋值
- 构造：接受 `service_handler_ptr_type`（即 `::yggr::shared_ptr<Service_Handler>`）并断言非空。
- 支持移动与拷贝构造/赋值（使用 BOOST 的移动宏与 `copy_or_move_or_swap`）。
- `swap()` 提供移动与普通交换实现，并在 `swap_support` 中提供 ADL 支持。

## 主要方法（委托）
- `io_service_pool_type& service_pool()`：返回底层 `Service_Handler::service_pool()`。
- `signal_set_type& signal_set()`：返回 `signal_set()`。
- `service_type& get_service()`：返回当前 service 引用。
- `bool add_signal(u32 sig)` / `bool remove_signal(u32 sig)` / `void clear_signal()`：信号管理接口。
- `void join()`：等待服务完成（委托 `join()`）。
- `template<typename Handler> void set_signal_handler(const Handler& handler)`：设置信号处理回调。
- `bool cancel_signal_handler()`：取消信号处理回调。
- `bool is_running() const`：查询运行状态。
- `void run()` / `void stop()`：控制服务运行与停止。

全部方法都在调用前断言内部 shared_ptr 非空。

## 行为与注意事项
- 该包装类本质上是一个代理，所有操作都直接委托给 `_psh`。因此它不会改变 `Service_Handler` 的语义，但便于共享所有权和作为值传递。
- 构造时使用 `assert(_psh)`，意味着传入空指针会在调试构建中触发断言。
- 该类型不提供线程安全保护，底层 `Service_Handler` 的线程安全性由其自身或共享策略保证。

## 使用示例
```cpp
::yggr::shared_ptr<MyServiceHandler> sh = ::yggr::make_shared<MyServiceHandler>(init);
service_handler_shared_wrap<MyServiceHandler> wrap(sh);

wrap.add_signal(SIGINT);
wrap.run();
// ...
wrap.stop();
wrap.join();
```

## 参考
- 源码： [yggr/network/service_handler_shared_wrap.hpp](yggr/network/service_handler_shared_wrap.hpp#L1-L200)
