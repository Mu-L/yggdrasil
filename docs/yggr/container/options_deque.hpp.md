---
# 文件：options_deque.hpp

## 简介

`options_deque.hpp` 是 yggdrasil 项目中用于实现带有可选参数的双端队列（deque）容器的头文件。该文件基于 Boost.Container 的 `deque`，通过模板参数扩展了分配器和选项类型，并提供了丰富的构造、赋值、交换、插入、删除等接口，兼容多种 Boost 版本和 C++ 标准。


## 主要内容

### 1. 头文件保护

- 宏定义：`__YGGR_CONTAINER_OPTIONS_DEQUE_HPP__`

### 2. 依赖包含

- 依赖 Boost.Container、Boost.Utility、Boost.MPL、yggr 自身的 mplex、iterator_ex、container/detail 等模块。
- 针对不同 Boost 版本做了兼容处理。

### 3. 主体类模板

#### `options_deque<T, A, O>`

- 继承自 `boost::container::deque`，支持自定义分配器（A）和选项（O）。
- 兼容不同 Boost 版本，自动适配参数。
- 提供了多种构造函数，支持默认构造、分配器构造、区间构造、拷贝/移动构造、initializer_list 构造等。
- 支持多种赋值操作符，兼容不同类型的 deque 及自身类型。
- 提供 swap、emplace、erase、erase_if 等扩展操作。
- 通过 SFINAE 技术和类型萃取，支持类型安全的容器间操作。
- 兼容 C++03/11/14/17 及 Boost 1.57~1.71+。

### 4. 辅助函数与宏

- `shrink_to_fit`、`emplace`、`emplace_front`、`emplace_back`、`erase`、`erase_if` 等通用操作。
- 多种宏定义用于生成兼容性代码和类型萃取。
- 支持容器间的 isomeric same（同质异构）比较与交换。

### 5. 命名空间与导出

- 主体位于 `yggr::container` 命名空间。
- 交换函数（swap）导出到 `std`、`boost` 命名空间，便于标准库和 Boost 兼容。
- 通过 `using` 导出 `options_deque` 到yggdrasil命名空间。

## 用法说明

- 适用于需要自定义分配器或特殊选项的双端队列场景。
- 直接包含本头文件，并使用 `yggr::container::options_deque` 或 `yggr::options_deque` 即可。
- 支持与 Boost.Container 的 deque 互操作，便于与第三方库集成。

## 设计说明

- 通过模板参数和类型萃取机制，极大增强了 deque 的灵活性和可扩展性。
- 兼容多版本 Boost 和多种 C++ 标准，适合跨平台和长期维护项目。
- 采用 SFINAE、enable_if/disable_if 等高级 C++ 技术，保证类型安全和接口丰富性。

---

如需详细了解各成员函数和宏的具体实现，请参考源码及相关依赖头文件。

