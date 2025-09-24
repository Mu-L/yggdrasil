---
# 文件：unordered_set.hpp

## 简介

`unordered_set.hpp` 是 yggdrasil 项目中用于无序集合容器（unordered_set/unordered_multiset）实现的头文件。该文件基于 Boost.Unordered 或标准库的 `unordered_set`，并结合 yggdrasil 项目的类型萃取、节点句柄、兼容性适配等机制，提供了灵活、可扩展的无序集合容器实现，兼容多种 C++ 标准和第三方库。


## 主要内容

- 头文件保护宏，防止重复包含。
- 依赖 Boost.Unordered、标准库 `<unordered_set>` 及yggdrasil自身的相关模块。
- 通过宏和条件编译，自动选择使用 Boost 还是 STL 的 unordered_set/unordered_multiset。
- 提供类型萃取、节点句柄 traits、merge/contains/extract/insert/erase_if 等兼容性和扩展实现。
- 支持多种构造、赋值、插入、删除、查找、合并等操作，接口丰富，类型安全。
- 通过类型萃取、SFINAE 等高级 C++ 技术，保证灵活性和可扩展性。
- 命名空间组织合理，便于与其他模块集成和扩展。
- 支持范围操作（如 boost::size）函数，便于与 STL/Boost 生态集成。

## 用法说明

- 适用于需要无序集合（哈希集合）功能的场景，支持自定义哈希、比较器、分配器等。
- 直接包含本头文件，并使用 `yggr::container::unordered_set` 或 `yggr::container::unordered_multiset` 即可。
- 支持与 Boost.Unordered 和标准库 unordered_set 互操作，便于与第三方库集成。

## 设计说明

- 通过模板参数和类型萃取机制，极大增强了 unordered_set/unordered_multiset 的灵活性和可扩展性。
- 兼容多版本 Boost 和多种 C++ 标准，适合跨平台和长期维护项目。
- 采用现代 C++ 技术，保证类型安全和接口丰富性。

---

如需详细了解各成员函数和宏的具体实现，请参考源码及相关依赖头文件。

