---
# is_isomeric_same_options_set.hpp 文档

## 概述

`is_isomeric_same_options_set.hpp` 是 yggdrasil 项目中用于判断带有选项参数的 set/multiset 类型在“同构异参”意义下是否相同的类型萃取工具。该文件主要解决 Boost 1.70 及以后版本中 `boost::container::set` 模板参数和 options 参数变化导致的类型兼容性问题，便于泛型编程时安全判断不同 set 类型（含 options）的等价性。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 注释说明 Boost 1.70+ 版本 set 容器模板参数和 options 兼容性问题。
- 包含类型萃取、模板展开、分配器和比较器萃取、选项适配等相关头文件。
- 在 `yggr::container::detail` 命名空间下实现 `_is_isomeric_same_options_set_detail` 模板结构体，递归判断两个带 options 的 set 类型的模板参数、值类型、分配器类型、key 比较器类型、options 类型等是否“同构异参”。
  - 对于模板参数数量不同、类型不同等情况，返回 `false_`。
  - 对于模板参数数量为 3 的情况，复用基础 set 的同构判断。
  - 对于模板参数数量为 4 的情况，判断第二、三模板参数是否不同，值类型、分配器类型、key 比较器类型、options 类型是否一致。
- 提供 `is_isomeric_same_options_set<SetL, SetR>` 类型萃取，判断两个带 options 的 set 类型是否“同构异参”。
- 提供 `is_same_or_isomeric_same_options_set<SetL, SetR>` 类型萃取，判断两个类型是否完全相同或“同构异参”。
- 提供 `is_isomeric_same_options_multiset` 及 `is_same_or_isomeric_same_options_multiset`，用于 multiset 类型判断。
- 将上述类型萃取提升到 yggr 命名空间，便于全局统一调用。

## 适用场景

- 需要在泛型编程中判断不同带 options 的 set/multiset 类型（如模板参数不同但本质等价）是否可以安全互操作的场景。
- 解决 Boost 1.70+ 版本 set/multiset 容器模板参数和 options 兼容性问题，提升代码健壮性和可移植性。

## 使用示例

```cpp
#include <yggr/container/is_isomeric_same_options_set.hpp>

static_assert(
    yggr::is_isomeric_same_options_set<
        boost::container::set<int, void, MyOpt1>,
        boost::container::set<int, std::less<int>, std::allocator<int>, MyOpt2>
    >::value, "类型同构异参"
);
```

---

本文件为 yggdrasil 容器适配体系的类型兼容性辅助组件，便于在模板库和泛型容器开发中统一处理带 options 的 set/multiset 类型的等价性判断。

