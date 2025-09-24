---
# 文件：unordered_map.hpp

## 简介

unordered_map.hpp 是 yggdrasil 项目中用于无序映射容器（unordered_map/unordered_multimap）实现的头文件。该文件基于 Boost.Unordered 或标准库的 `unordered_map`，并结合 yggdrasil 项目的类型萃取、节点句柄、兼容性适配等机制，提供了灵活、可扩展的无序映射容器实现，兼容多种 C++ 标准和第三方库。


## 主要内容

- 头文件保护宏，防止重复包含。
- 依赖 Boost.Unordered、标准库 `<unordered_map>` 及yggdrasil自身的相关模块。
- 通过宏和条件编译，自动选择使用 Boost 还是 STL 的 unordered_map/unordered_multimap。
- 提供类型萃取、节点句柄 traits、merge/contains/try_emplace/insert_or_assign 等兼容性和扩展实现。
- 支持多种构造、赋值、插入、删除、查找、合并等操作，接口丰富，类型安全。
- 通过类型萃取、SFINAE 等高级 C++ 技术，保证灵活性和可扩展性。
- 命名空间组织合理，便于与其他模块集成和扩展。

## 用法说明

- 适用于需要无序映射（哈希表）功能的场景，支持自定义哈希、比较器、分配器等。
- 直接包含本头文件，并使用 `yggr::container::unordered_map` 或 `yggr::container::unordered_multimap` 即可。
- 支持与 Boost.Unordered 和标准库 unordered_map 互操作，便于与第三方库集成。

## 设计说明

- 通过模板参数和类型萃取机制，极大增强了 unordered_map/unordered_multimap 的灵活性和可扩展性。
- 兼容多版本 Boost 和多种 C++ 标准，适合跨平台和长期维护项目。
- 采用现代 C++ 技术，保证类型安全和接口丰富性。

---

如需详细了解各成员函数和宏的具体实现，请参考源码及相关依赖头文件。

