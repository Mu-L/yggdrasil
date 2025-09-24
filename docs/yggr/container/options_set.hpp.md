---
# 文件：options_set.hpp

## 简介

`options_set.hpp` 是 yggdrasil 项目中用于实现带有可选参数的 set/multiset 容器的头文件。该文件基于 Boost.Container 的 `set` 和 `multiset`，通过模板参数扩展了比较器、分配器和选项类型，支持灵活的容器定制，兼容多种 Boost 版本。


## 主要内容

- 头文件保护宏，防止重复包含。
- 依赖 Boost.Container 及yggdrasil自身的相关模块，兼容不同 Boost 版本。
- 提供 `options_set` 和 `options_multiset` 两个主要模板类，分别对应 set 和 multiset 容器，支持自定义比较器、分配器和选项参数。
- 支持多种构造、赋值、插入、删除、查找等操作，接口丰富，类型安全。
- 通过 SFINAE、类型萃取等高级 C++ 技术，保证灵活性和可扩展性。
- 命名空间组织合理，便于与其他模块集成和扩展。

## 用法说明

- 适用于需要自定义比较器、分配器或特殊选项的 set/multiset 场景。
- 直接包含本头文件，并使用 `yggr::container::options_set` 或 `yggr::options_set` 即可。
- 支持与 Boost.Container 的 set/multiset 互操作，便于与第三方库集成。

## 设计说明

- 通过模板参数和类型萃取机制，极大增强了 set/multiset 的灵活性和可扩展性。
- 兼容多版本 Boost 和多种 C++ 标准，适合跨平台和长期维护项目。
- 采用现代 C++ 技术，保证类型安全和接口丰富性。

---

如需详细了解各成员函数和宏的具体实现，请参考源码及相关依赖头文件。

