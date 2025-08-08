---
# default_allocator.hpp 文档

## 概述

`default_allocator.hpp` 是 yggdrasil 项目中用于统一容器默认分配器选择的配置头文件。该文件通过宏定义机制，根据编译环境和 Boost 版本，自动选择合适的分配器类型（如 `std::allocator` 或 `boost::container::new_allocator`），为容器适配提供一致的分配器接口。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含基础定义头文件 `<yggr/base/yggrdef.h>` 和容器选择头文件 `<yggr/container/container_selector.hpp>`。
- 根据 Boost 版本，包含 `<boost/container/new_allocator.hpp>`。
- 包含 `<memory>`，以支持 `std::allocator`。
- 通过宏 `YGGR_CONTAINER_DEFAULT_ALLOCATOR()`，根据以下规则选择默认分配器类型：
  - 如果使用 Boost 容器且 Boost 版本 >= 1.58.0，则使用 `boost::container::new_allocator`
  - 如果使用 Boost 容器但 Boost 版本 < 1.58.0，则使用 `std::allocator`
  - 如果使用标准库容器，则始终使用 `std::allocator`
  - 未知情况则报错

## 适用场景

- 需要在不同平台、不同 Boost 版本下统一容器分配器类型的场景。
- 作为 yggdrasil 容器库的基础分配器配置文件，供容器适配头文件和泛型容器代码引用。

## 使用说明

- 通过 `YGGR_CONTAINER_DEFAULT_ALLOCATOR()` 宏获取当前环境下的默认分配器类型。例如：
  ```cpp
  YGGR_CONTAINER_DEFAULT_ALLOCATOR()(int) alloc;
  ```
- 用户无需关心底层分配器实现，统一通过该宏适配即可。

---

本文件为 yggdrasil 容器适配体系的基础分配器配置组件，无需直接调用，仅需在项目中包含并使用宏即可自动生效。

