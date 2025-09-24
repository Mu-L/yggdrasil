---
# 文件：options_map.hpp

## 简介

options_map.hpp 是 yggdrasil 项目中用于实现带有可选参数的 map/multimap 容器的头文件。该文件基于 Boost.Container 的 `map` 和 `multimap`，通过模板参数扩展了比较器、分配器和选项类型，支持灵活的容器定制，兼容多种 Boost 版本。


## 主要内容

### 1. 头文件保护

- 宏定义：`__YGGR_CONTAINER_OPTIONS_MAP_HPP__`

### 2. 依赖包含

- 依赖 Boost.Container、Boost.Utility、yggr 自身的 mplex、iterator_ex、container/options 等模块。
- 针对不同 Boost 版本做了兼容处理。

### 3. 主体类模板

#### `options_map<K, T, C, A, O>`

- 继承自 `boost::container::map`，支持自定义键类型（K）、值类型（T）、比较器（C）、分配器（A）、选项（O）。
- 兼容不同 Boost 版本，自动适配参数。
- 提供了多种构造函数、赋值操作符、插入、删除、查找等接口。
- 支持类型安全的容器间操作和多种扩展功能。

#### `options_multimap<K, T, C, A, O>`

- 类似于 `options_map`，但允许键重复，继承自 `boost::container::multimap`。

### 4. 设计说明

- 通过模板参数和类型萃取机制，极大增强了 map/multimap 的灵活性和可扩展性。
- 兼容多版本 Boost 和多种 C++ 标准，适合跨平台和长期维护项目。
- 采用 SFINAE、enable_if/disable_if 等高级 C++ 技术，保证类型安全和接口丰富性。

### 5. 命名空间与导出

- 主体位于 `yggr::container` 命名空间。
- 通过 `using` 导出 `options_map` 和 `options_multimap` 到yggdrasil命名空间。

## 用法说明

- 适用于需要自定义比较器、分配器或特殊选项的 map/multimap 场景。
- 直接包含本头文件，并使用 `yggr::container::options_map` 或 `yggr::options_map` 即可。
- 支持与 Boost.Container 的 map/multimap 互操作，便于与第三方库集成。

---

如需详细了解各成员函数和宏的具体实现，请参考源码及相关依赖头文件。

