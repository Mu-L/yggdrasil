---
# 文件：unwrap_container.hpp

## 简介

`unwrap_container.hpp` 是 yggdrasil 项目中用于获取（解包）标准和自定义容器适配器（如 stack、queue、priority_queue）底层实际容器的头文件。该文件通过模板特化和辅助类机制，为各种容器适配器提供统一的底层容器访问接口，便于直接操作底层数据结构。

## 主要内容

- 头文件保护宏，防止重复包含。
- 依赖 stack.hpp、queue.hpp 及标准库适配器。
- `detail::stl_unwrap_container_helper` 辅助类：通过继承标准容器适配器，暴露其底层容器成员 `c` 的访问接口。
- `unwrap_container` 主模板及多种特化：
  - 通用模板：对普通容器直接返回自身引用。
  - 针对 `std::stack`、`std::queue`、`std::priority_queue` 及yggdrasil自定义适配器的特化，均可通过 `operator()` 获取底层容器的引用或常量引用。
- 支持标准库和yggdrasil自定义的 stack、queue、priority_queue 适配器。

## 用法说明

- 适用于需要直接访问 stack、queue、priority_queue 等容器适配器底层容器的场景。
- 直接包含本头文件，并使用 `yggr::container::unwrap_container<Container>()(container)` 即可获取底层容器的引用。
- 支持标准库和yggdrasil自定义容器适配器，接口统一。

## 设计说明

- 通过模板特化和辅助类，安全地访问标准容器适配器的底层容器成员，避免直接访问私有成员带来的兼容性问题。
- 兼容 C++98/03/11/14/17 及 Boost 生态，适合跨平台和长期维护项目。

---

如需详细了解辅助类和适配机制的具体实现，请参考源码及相关依赖头文件。

