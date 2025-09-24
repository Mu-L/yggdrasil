---
# 文件：node_handle_traits.hpp

## 简介

`node_handle_traits.hpp` 是 yggdrasil 项目中用于节点句柄特性的头文件。该文件主要用于对外暴露 `node_handle_traits` 类型定义，便于容器相关模块统一使用节点句柄特性。

## 主要内容

- 头文件保护宏：`__YGGR_CONTAINER_NODE_HANDLE_TRAITS_HPP__`
- 包含内部实现头文件：`<yggr/container/detail/node_handle_traits.hpp>`
- 命名空间：`yggr::container`
- 类型导入：`using detail::node_handle_traits;`
  - 该类型定义实际位于 `yggr::container::detail` 命名空间下，通过 `using` 声明暴露到 `yggr::container` 命名空间，方便外部直接使用。

## 用法说明

在需要使用节点句柄特性的容器或相关模块中，直接包含本头文件即可获得 `yggr::container::node_handle_traits` 类型定义，无需关心其内部实现细节。

## 设计说明

- 该文件仅作为类型转发和接口暴露，实际实现细节隐藏在 `detail` 子命名空间中，符合 C++ 头文件分层设计原则。
- 便于后续维护和实现替换，提升代码可读性和可维护性。

---

如需详细了解 `node_handle_traits` 的具体实现，请参考 node_handle_traits.hpp 文件。

