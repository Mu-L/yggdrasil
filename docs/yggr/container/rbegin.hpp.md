---
# 文件：rbegin.hpp

## 简介

`rbegin.hpp` 是 yggdrasil 项目中用于统一获取容器反向迭代器（reverse_iterator）的头文件。该文件通过 SFINAE 技术自动判断容器是否有成员 `rbegin()`，并在没有时回退到 Boost.Range 的 `rbegin`，从而为各种容器（包括标准容器和自定义容器）提供一致的反向迭代器获取接口。


## 主要内容

- 头文件保护宏，防止重复包含。
- 依赖 range_reverse_iterator_ex.hpp、has_rbegin.hpp、Boost.Range、Boost.Utility。
- 提供 `rbegin` 和 `crbegin` 两组重载函数，分别支持非常量和常量容器。
- 对于有成员 `rbegin()` 的容器，直接调用成员函数；否则使用 Boost.Range 的 `rbegin`。
- 通过 `enable_if` 和 `disable_if` 实现 SFINAE 分发，保证类型安全和接口统一。
- 导出 `rbegin` 和 `crbegin` 到yggdrasil命名空间，便于全局调用。

## 用法说明

- 适用于需要统一获取各种容器反向迭代器的场景，支持标准容器、自定义容器和第三方容器。
- 直接包含本头文件，并使用 `yggr::rbegin` 或 `yggr::crbegin` 即可，无需关心容器类型细节。

## 设计说明

- 通过 SFINAE 技术和类型萃取机制，自动适配不同容器类型，提升代码通用性和可维护性。
- 兼容 C++98/03/11/14/17 及 Boost 生态，适合跨平台和长期维护项目。

---

如需详细了解各重载函数的具体实现，请参考源码及相关依赖头文件。

