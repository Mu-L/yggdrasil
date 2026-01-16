# normal_io_service_selector.hpp 文档

## 概述
- 文件： [yggr/network/normal_io_service_selector.hpp](yggr/network/normal_io_service_selector.hpp#L1-L200)
- 描述：`normal_io_service_selector<Saver>` 提供一个简单的轮询选择器，用于在保存 `Service` 智能指针或对象的容器（`Saver`）中按循环顺序选择下一个服务实例。常用于 `io_service_pool` 等场景，实现均匀分配请求到多个服务实例。

## 模板参数
- `Saver`：保存服务对象/指针的容器类型（例如 `container::vector<service_ptr_type>`）。`Saver` 需要提供 `begin()`, `end()`, `size()`、`value_type`、以及 `iterator`/`const_iterator`。

## 行为与接口
- 构造：`normal_io_service_selector(saver_type& saver)` 接受对容器的引用并将内部迭代器 `_next` 初始化为 `saver.begin()`。构造时断言容器非空。
- 拷贝构造：复制引用与迭代器位置，仍断言容器非空。
- 调用操作：`saver_val_type& operator()()` 返回当前 `_next` 所指向的元素引用，然后将 `_next` 前进；若到达容器末尾则回绕到 `begin()`。

特性：
- 轮询（round-robin）选择策略，简单且无锁（依赖调用者同步容器访问或保证在并发场景下容器只读）。
- 假定 `Saver` 在 selector 生命周期内至少有一个元素（构造时断言）。

## 使用示例
```cpp
// 假设 saver_type 是 std::vector<std::shared_ptr<MyService>>
normal_io_service_selector<saver_type> selector(saver);

auto& service = selector(); // 获取下一个 service 引用
service->post(task);
```

## 注意事项
- `normal_io_service_selector` 保存的是对 `Saver` 的引用；确保 `Saver` 在 selector 生命周期内有效。
- 该类不是线程安全的：在多线程同时调用 `operator()` 时需要外部同步或使用线程安全的容器/选择器实现（如 `balance_io_service_selector`）。
- 构造与拷贝构造会断言 `Saver::size()` 非零，传入空容器将触发断言。

## 实现要点
- 内部仅保存容器引用 `_saver` 与迭代器 `_next`。
- `operator()` 返回对当前元素的引用后移动迭代器，末尾时回绕为 `begin()`，实现高效的循环访问。

## 参考
- 源码： [yggr/network/normal_io_service_selector.hpp](yggr/network/normal_io_service_selector.hpp#L1-L200)
