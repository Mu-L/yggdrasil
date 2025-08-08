---
# empty.hpp 文档

## 概述

`empty.hpp` 是 yggdrasil 项目中用于统一容器判空操作的适配头文件。该文件通过引入 boost 的 `empty` 函数，为各种容器类型（包括标准容器、boost 容器、自定义容器等）提供统一的判空接口，便于泛型编程和容器操作的统一调用。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含基础定义头文件 `<yggr/base/yggrdef.h>`。
- 引入 `<boost/range/empty.hpp>`，使用 boost 的 `empty` 实现。
- 在 `yggr::container` 命名空间下直接使用 `boost::empty`。
- 将 `container::empty` 提升到 yggr 命名空间，便于全局统一调用。

## 适用场景

- 需要对不同类型容器统一进行判空操作时。
- 泛型算法、模板编程中对 empty 操作的统一适配需求。

## 使用示例

```cpp
#include <yggr/container/empty.hpp>

std::vector<int> v;
if (yggr::empty(v)) {
    // 容器为空
}
```

---

本文件为 yggdrasil 容器适配体系的基础判空适配组件，无需直接实现判空逻辑，仅需包含并调用 `yggr::empty` 即可自动适配各种容器类型。

