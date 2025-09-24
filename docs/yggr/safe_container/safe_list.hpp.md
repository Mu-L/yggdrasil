
# 文件: safe_list.hpp 文档

# 文件简介

`safe_list.hpp` 是 yggdrasil 项目中安全容器模块的一个头文件，主要实现了线程安全的 list 容器（safe_list）的优化版本。该文件依赖于 Boost 库，并通过多种宏和模板技巧，提供了高性能、线程安全的 list 操作。

# 主要功能

- 提供线程安全的 list 容器 `safe_list`，支持多线程环境下的安全访问和修改。
- 针对 Boost 1.70.0 及以上版本，支持自定义底层容器类型（如 `boost::container::list` 或 `yggr::container::detail::list`）。
- 支持多种构造、赋值、交换、插入、删除、访问等标准 list 操作，并通过宏自动生成大量样板代码。
- 支持节点的高效创建与销毁，避免多线程下的资源竞争。
- 通过 mutex（互斥锁）实现线程安全，支持读写锁粒度控制。
- 提供与标准库和 Boost 的 swap 兼容性。

# 主要类型与成员

- `safe_list<Val, Mutex, Ax, List>`：主模板类，Val 为元素类型，Mutex 为互斥类型，Ax 为分配器，List 为底层容器模板。
- `base_type`：底层容器类型。
- `mutex_type`、`read_lock_type`、`write_lock_type`：线程安全相关类型。
- `push_front`、`push_back`、`pop_front`、`pop_back` 等常用 list 操作，均为线程安全实现。
- `emplace`、`emplace_front`、`emplace_back`：支持原地构造元素。
- 支持多种构造函数、赋值运算符、swap、比较等操作，兼容标准容器接口。

# 线程安全说明

- 所有成员函数均通过互斥锁保护，保证多线程环境下的安全性。
- 容器的创建和销毁本身不保证线程安全，建议在不同线程中创建/销毁时使用 swap 进行隔离。
- 禁止通过回调函数将容器内部的迭代器、引用、指针等泄漏到容器外部并保存或使用。

# 兼容性与宏

- 通过 BOOST_VERSION 宏判断 Boost 版本，自动适配不同实现。
- 通过大量 YGGR_PP_ 开头的宏生成样板代码，减少重复劳动。
- 支持 BOOST_CONTAINER_PERFECT_FORWARDING，自动适配完美转发特性。

# 典型用法

```cpp
#include <yggr/safe_container/safe_list.hpp>

yggr::safe_container::safe_list<int> slist;
slist.push_back(1);
slist.push_front(2);
int val;
if (slist.pop_back(val)) {
    // 使用 val
}
```

# 注意事项

- 仅在未定义 `YGGR_NOT_USE_SAFE_CONTAINER_OPTIMIZATION` 时启用本优化实现。
- 必须先包含 safe_list.hpp。
- 不建议在多线程中直接创建/销毁 safe_list 实例，推荐使用 swap 进行线程间容器转移。
- 禁止将容器内部的迭代器、引用、指针等通过回调泄漏到外部。

# 版权声明

版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可证。



如需详细 API 说明，请参考具体成员函数实现和相关宏定义。

