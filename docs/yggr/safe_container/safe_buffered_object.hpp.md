
# 文件: safe_buffered_object.hpp 文档

# 文件简介

safe_buffered_object.hpp 是 yggdrasil 项目中安全容器模块的一个头文件，主要实现了线程安全的缓冲对象（safe_buffered_object）。该文件依赖于 yggdrasil 的 safe_deque、智能指针、线程库等基础设施，提供了带缓冲区的对象管理功能，适用于高并发场景下的数据缓存与批量处理。

# 主要功能

- 提供线程安全的缓冲对象容器 `safe_buffered_object`，支持多线程环境下的安全访问和批量数据处理。
- 支持自定义缓冲区大小，自动管理数据的入队和出队。
- 支持对象的插入、批量提取、清空、遍历等常用操作。
- 内部基于 `safe_deque` 实现，保证高效的队列操作和线程安全。
- 支持对象的智能指针管理，防止资源泄漏。
- 通过 mutex（互斥锁）实现线程安全。

# 主要类型与成员

- `safe_buffered_object<T, Mutex, Alloc>`：主模板类，T 为元素类型，Mutex 为互斥类型，Alloc 为分配器。
- 支持 `push_back`、`pop_front`、`extract_all`、`clear`、`size`、`empty` 等常用缓冲区操作。
- 支持缓冲区满时的自动处理策略（如批量转移、回调等）。
- 内部使用 `safe_deque` 作为存储结构，支持高效的并发队列操作。

# 线程安全说明

- 所有成员函数均通过互斥锁保护，保证多线程环境下的安全性。
- 容器的创建和销毁本身不保证线程安全，建议在不同线程中创建/销毁时使用 swap 进行隔离。

# 典型用法

```cpp
yggr::safe_container::safe_buffered_object<int> buffer(100); // 缓冲区大小为100
buffer.push_back(1);
std::vector<int> batch;
buffer.extract_all(batch); // 批量提取所有数据
```

# 注意事项

- 缓冲区大小可自定义，需根据实际业务场景合理设置。
- 不建议在多线程中直接创建/销毁 safe_buffered_object 实例，推荐使用 swap 进行线程间容器转移。

# 版权声明

版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可证。



如需详细 API 说明，请参考具体成员函数实现和相关宏定义。

