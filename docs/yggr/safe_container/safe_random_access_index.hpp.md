
# 文件: safe_random_access_index.hpp 文档

# 文件简介

safe_random_access_index.hpp 是 yggdrasil 项目中安全容器模块的一个头文件，主要实现了多索引随机访问表（multi_index random access index）的线程安全优化版本。该文件依赖 Boost、多索引容器和 yggdrasil 自身的基础设施，通过模板和宏实现高性能、线程安全的随机访问索引操作。

# 主要功能

- 提供线程安全的多索引随机访问表（safe_random_access_index），支持多线程环境下的安全访问和修改。
- 针对 Boost.MultiIndex 及自定义容器，支持底层随机访问索引类型的灵活切换和优化。
- 支持多种构造、赋值、交换、插入、删除、查找、遍历、替换、修改、线性操作（如 push/pop/assign）等标准随机访问索引操作，并通过宏自动生成大量样板代码。
- 通过 mutex（互斥锁）实现线程安全，支持读写锁粒度控制。
- 提供与标准库和 Boost 的 swap 兼容性。

# 主要类型与成员

- `safe_random_access_index_ha`：主模板类，支持多种参数配置，封装了随机访问索引的线程安全实现。
- `mutex_type`、`read_lock_type`、`write_lock_type`：线程安全相关类型。
- 支持 `insert`、`erase`、`find`、`replace`、`modify`、`extract`、`emplace`、`push_back`、`pop_back`、`assign` 等常用随机访问索引操作，均为线程安全实现。
- 支持多种构造函数、赋值运算符、swap、比较等操作，兼容标准容器接口。

# 线程安全说明

- 所有成员函数均通过互斥锁保护，保证多线程环境下的安全性。
- 容器的创建和销毁本身不保证线程安全，建议在不同线程中创建/销毁时使用 swap 进行隔离。
- 禁止通过回调函数将容器内部的迭代器、引用、指针等泄漏到容器外部并保存或使用。

# 兼容性与宏

- 通过宏判断是否启用优化实现（`YGGR_NOT_USE_SAFE_CONTAINER_OPTIMIZATION`）。
- 通过大量 YGGR_PP_ 开头的宏生成样板代码，减少重复劳动。
- 支持 Boost.MultiIndex 容器的特性和完美转发。

# 注意事项

- 仅在未定义 `YGGR_NOT_USE_SAFE_CONTAINER_OPTIMIZATION` 时启用本优化实现。
- 必须先包含 safe_multi_index_random_access_index.hpp。
- 不建议在多线程中直接创建/销毁 safe_random_access_index_ha 实例，推荐使用 swap 进行线程间容器转移。
- 禁止将容器内部的迭代器、引用、指针等通过回调泄漏到外部。

# 版权声明

版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可证。



如需详细 API 说明，请参考具体成员函数实现和相关宏定义。

