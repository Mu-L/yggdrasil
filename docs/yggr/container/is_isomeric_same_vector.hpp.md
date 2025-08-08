---
# is_isomeric_same_vector.hpp 文档

## 概述

`is_isomeric_same_vector.hpp` 是 yggdrasil 项目中用于判断 vector 类型在“同构异参”意义下是否相同的类型萃取工具。该文件主要解决 Boost 1.70 及以后版本中 `boost::container::vector` 模板参数变化导致的类型兼容性问题，便于泛型编程时安全判断不同 vector 类型的等价性。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 注释说明 Boost 1.70+ 版本 vector 容器模板参数兼容性问题。
- 包含类型萃取、模板展开、分配器萃取等相关头文件。
- 在 `yggr::container::detail` 命名空间下实现 `_is_isomeric_same_vector_detail` 模板结构体，递归判断两个 vector 类型的模板参数、值类型、分配器类型等是否“同构异参”。
  - 对于模板参数数量不同、类型不同等情况，返回 `false_`。
  - 对于模板参数数量为 2 的情况，判断第二模板参数（如 void）不同，值类型和分配器类型一致。
- 提供 `is_isomeric_same_vector<VtL, VtR>` 类型萃取，判断两个 vector 类型是否“同构异参”。
- 提供 `is_same_or_isomeric_same_vector<VtL, VtR>` 类型萃取，判断两个类型是否完全相同或“同构异参”。
- 将上述类型萃取提升到 yggr 命名空间，便于全局统一调用。

## 适用场景

- 需要在泛型编程中判断不同 vector 类型（如模板参数不同但本质等价）是否可以安全互操作的场景。
- 解决 Boost 1.70+ 版本 vector 容器模板参数兼容性问题，提升代码健壮性和可移植性。

## 使用示例

```cpp
#include <yggr/container/is_isomeric_same_vector.hpp>

static_assert(
    yggr::is_isomeric_same_vector<
        boost::container::vector<int, void>,
        boost::container::vector<int, std::allocator<int>>
    >::value, "类型同构异参"
);
```

---

本文件为 yggdrasil 容器适配体系的类型兼容性辅助组件，便于在模板库和泛型容器开发中统一处理 vector 类型的等价性判断。

