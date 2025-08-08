---
# container_selector.hpp 文档

## 概述

`container_selector.hpp` 是 yggdrasil 项目中用于选择容器实现方案的配置头文件。该文件通过宏定义机制，自动选择使用标准库（STL）容器还是 Boost 容器，便于在不同编译环境下灵活切换容器实现，提升代码的可移植性和兼容性。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含基础定义头文件 `<yggr/base/yggrdef.h>`。
- 检查是否已定义 `YGGR_USE_STL_CONTAINER` 或 `YGGR_USE_BOOST_CONTAINER` 宏。
- 如果两者都未定义，则默认定义 `YGGR_USE_BOOST_CONTAINER`，即优先使用 Boost 容器。

## 适用场景

- 需要在不同平台或项目配置下灵活切换容器实现（如 STL 或 Boost）。
- 作为 yggdrasil 容器库的基础配置文件，供其他容器适配头文件引用。

## 使用说明

- 在包含本头文件后，后续容器相关代码可通过 `YGGR_USE_STL_CONTAINER` 或 `YGGR_USE_BOOST_CONTAINER` 宏判断使用哪种容器实现。
- 用户可在项目编译选项或其他配置头文件中手动定义相关宏，以覆盖默认选择。

---

本文件为 yggdrasil 容器适配体系的基础配置组件，无需直接调用，仅需在项目中包含即可自动生效。

