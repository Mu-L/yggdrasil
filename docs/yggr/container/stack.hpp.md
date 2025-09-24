---
# 文件：stack.hpp

## 简介

`stack.hpp` 是 yggdrasil 项目中用于实现栈（stack）容器的头文件。该文件在标准库和 Boost.Container 的基础上，提供了更灵活的泛型栈实现，支持自定义底层容器、分配器等，并扩展了 emplace、swap、范围操作等功能。


## 主要内容

- 头文件保护宏，防止重复包含。
- 依赖yggdrasil项目自身的基础设施、Boost、标准库 `<stack>`，以及容器相关的辅助头文件。
- 提供 emplace 扩展，兼容不同 C++ 标准和编译器特性。
- `yggr::container::stack` 模板类，支持自定义底层容器（默认使用 `yggr::container::deque`）。
- 提供多种构造、赋值、swap、emplace、push、pop、top、empty、size 等接口。
- 支持与 `std::stack` 互转，支持容器内容的比较操作符重载。
- 支持 allocator 获取和底层容器访问。
- 提供 swap 支持，导出到 `std`、`boost` 命名空间，便于标准库和 Boost 兼容。
- 支持 boost::size 等范围操作函数，便于与 STL/Boost 生态集成。

## 用法说明

- 适用于需要自定义底层容器、分配器的栈场景。
- 直接包含本头文件，并使用 `yggr::container::stack` 即可。
- 支持与标准库栈互操作，便于与第三方库集成。

## 设计说明

- 通过模板参数和类型萃取机制，极大增强了 stack 的灵活性和可扩展性。
- 兼容多版本 Boost 和多种 C++ 标准，适合跨平台和长期维护项目。
- 采用现代 C++ 技术，保证类型安全和接口丰富性。

---

如需详细了解各成员函数和宏的具体实现，请参考源码及相关依赖头文件。

