
# 文件: safe_hashed_map_queue.hpp 文档

# 文件简介

safe_hashed_map_queue.hpp 是 yggdrasil 项目中安全容器模块的一个头文件，主要实现了线程安全的哈希映射队列（safe_hashed_map_queue）。该文件结合了哈希表和队列的特性，适用于需要高效键值查找和队列顺序处理的并发场景。

# 主要功能

- 提供线程安全的哈希映射队列容器 `safe_hashed_map_queue`，支持多线程环境下的安全访问和队列操作。
- 结合哈希表的高效查找与队列的顺序处理，适合缓存、任务分发等场景。
- 支持插入、查找、删除、批量提取、遍历等常用操作。
- 支持自定义 key、value、哈希函数、比较器、分配器等参数。
- 内部集成了 safe_deque、safe_multi_index_container 等安全容器，保证高效与线程安全。
- 通过 mutex（互斥锁）实现线程安全。

# 主要类型与成员

- `safe_hashed_map_queue<Key, Val, Mutex, Hash, Pred, Alloc>`：主模板类，Key 为键类型，Val 为值类型，Mutex 为互斥类型，Hash 为哈希函数，Pred 为相等比较器，Alloc 为分配器。
- 支持 `push`、`pop`、`find`、`erase`、`clear`、`size`、`empty`、`swap` 等常用队列和哈希表操作。
- 支持批量提取、遍历、条件删除等高级操作。
- 内部使用 `safe_deque`、`safe_multi_index_container` 等作为存储结构，保证高效的并发操作。

# 线程安全说明

- 所有成员函数均通过互斥锁保护，保证多线程环境下的安全性。
- 容器的创建和销毁本身不保证线程安全，建议在不同线程中创建/销毁时使用 swap 进行隔离。

# 典型用法

```cpp
yggr::safe_container::safe_hashed_map_queue<int, std::string> queue;
queue.push(1, "data");
std::string val;
if (queue.pop(val)) {
    // 取出队首元素
}
if (queue.find(1, val)) {
    // 查找 key=1 的元素
}
```

# 注意事项

- 必须根据实际业务场景合理选择 key、value 类型及哈希函数等参数。
- 不建议在多线程中直接创建/销毁 safe_hashed_map_queue 实例，推荐使用 swap 进行线程间容器转移。

# 版权声明

版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可证。



如需详细 API 说明，请参考具体成员函数实现和相关宏定义。

