---
# basic_function_adapter.hpp 文档

## 概述

`basic_function_adapter.hpp` 是 yggdrasil 项目中的一个基础适配器头文件，主要用于统一容器的遍历接口。该文件通过包含 begin/end/rbegin/rend 等适配器头文件，为容器提供标准化的遍历入口，便于泛型算法和容器操作的统一调用。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含 yggdrasil 基础定义头文件。
- 包含 `begin.hpp`、`end.hpp`、`rbegin.hpp`、`rend.hpp`，为容器提供统一的正向和反向遍历接口适配。
- 本文件本身不直接实现函数，仅作为适配器头文件的聚合入口。

## 适用场景

- 需要对不同容器类型统一调用 `begin`、`end`、`rbegin`、`rend` 等遍历接口时。
- 作为 yggdrasil 容器库的基础适配层，便于后续扩展和维护。

## 使用示例

```cpp
#include <yggr/container/basic_function_adapter.hpp>

// 可直接使用 yggr::container::begin/ end/ rbegin/ rend 适配器
```

---

如需具体遍历适配实现，请查阅对应的 `begin.hpp`、`end.hpp`、`rbegin.hpp`、`rend.hpp` 文件。

