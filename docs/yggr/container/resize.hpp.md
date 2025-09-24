---
# 文件：resize.hpp

## 简介

`resize.hpp` 是 yggdrasil 项目中用于为容器统一实现 resize 操作的头文件。该文件通过类型萃取和辅助类机制，为支持 `resize` 操作的容器提供统一的扩容/缩容接口，提升代码的通用性和可维护性。

## 主要内容

- 头文件保护宏，防止重复包含。
- 依赖 resize_helper.hpp，以及 Boost 的类型萃取和 SFINAE 工具。
- 提供两组 `resize` 模板函数：
  - `resize(C& c, size_type size)`：调整容器大小。
  - `resize(C& c, size_type size, const T& t)`：调整容器大小并用指定值填充新元素。
- 内部通过 `container::detail::resize_helper` 辅助类实现具体的扩容/缩容逻辑，自动适配不同容器类型。
- 仅对非常量容器对象有效，const 容器将被 SFINAE 排除。
- 导出 `resize` 到yggdrasil命名空间，便于全局调用。

## 用法说明

- 适用于需要统一扩容/缩容各种容器的场景，支持标准容器、自定义容器等。
- 直接包含本头文件，并使用 `yggr::resize(c, size)` 或 `yggr::resize(c, size, value)` 即可，无需关心容器类型细节。

## 设计说明

- 通过 SFINAE 和类型萃取机制，自动适配不同容器类型，提升代码通用性和安全性。
- 兼容 C++98/03/11/14/17 及 Boost 生态，适合跨平台和长期维护项目。

---

如需详细了解辅助类和适配机制的具体实现，请参考源码及相关依赖头文件。

