---
# 文件：queue.hpp

## 简介

`queue.hpp` 是 yggdrasil 项目中用于实现队列（queue）和优先队列（priority_queue）容器的头文件。该文件在标准库和 Boost.Container 的基础上，提供了更灵活的泛型队列实现，支持自定义底层容器、分配器、比较器等，并扩展了 emplace、swap、范围操作等功能。

## 主要内容

### 1. 头文件保护

- 宏定义：`__YGGR_CONTAINER_QUEUE_HPP__`

### 2. 依赖包含

- 依赖yggdrasil项目自身的基础设施、Boost、标准库 `<queue>`，以及容器相关的辅助头文件。

### 3. emplace 扩展

- 针对 `std::queue` 和 `std::priority_queue`，提供了 emplace 的 SFINAE 版本和宏展开版本，兼容不同 C++ 标准和编译器特性。

### 4. queue 容器

- `yggr::container::queue` 模板类，支持自定义底层容器（默认使用 `yggr::container::deque`）。
- 提供多种构造、赋值、swap、emplace、push、pop、front、back、empty、size 等接口。
- 支持与 `std::queue` 互转，支持容器内容的比较操作符重载。
- 支持 allocator 获取和底层容器访问。

### 5. priority_queue 容器

- `yggr::container::priority_queue` 模板类，支持自定义底层容器（默认使用 `yggr::container::vector`）和比较器（默认 `std::less`）。
- 提供多种构造、赋值、swap、emplace、push、pop、top、empty、size 等接口。
- 支持与 `std::priority_queue` 互转，支持 allocator 获取和底层容器、比较器访问。

### 6. swap 与范围操作支持

- 提供 `swap` 支持，导出到 `std`、`boost` 命名空间，便于标准库和 Boost 兼容。
- 支持 boost::size 等范围操作宏，便于与 STL/Boost 生态集成。

## 用法说明

- 适用于需要自定义底层容器、分配器或比较器的队列/优先队列场景。
- 直接包含本头文件，并使用 `yggr::container::queue` 或 `yggr::container::priority_queue` 即可。
- 支持与标准库队列互操作，便于与第三方库集成。

## 设计说明

- 通过模板参数和类型萃取机制，极大增强了 queue/priority_queue 的灵活性和可扩展性。
- 兼容多版本 Boost 和多种 C++ 标准，适合跨平台和长期维护项目。
- 采用现代 C++ 技术，保证类型安全和接口丰富性。

---

如需详细了解各成员函数和宏的具体实现，请参考源码及相关依赖头文件。

