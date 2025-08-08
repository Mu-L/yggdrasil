---
# begin.hpp 文档

## 概述

`begin.hpp` 是 yggdrasil 项目中用于统一容器遍历起始迭代器获取的适配头文件。该文件通过引入 boost 的 `begin`，并提供 `cbegin`（常量容器起始迭代器）适配器，方便在泛型编程中统一获取各种容器的起始迭代器，兼容标准库和 boost 容器。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含 range_iterator_ex.hpp 和 `boost/range/begin.hpp`，用于增强迭代器类型推导和兼容性。
- `using boost::begin;`：直接引入 boost 的 `begin`，支持标准和 boost 容器。
- `cbegin` 模板函数：返回常量容器的起始迭代器，类型安全且兼容 boost/标准容器。
- 将 `container::begin` 和 `container::cbegin` 提升到 yggr 命名空间，便于全局统一调用。

## 适用场景

- 需要统一获取各种容器（包括标准容器和 boost 容器）起始迭代器的场景。
- 泛型算法、模板编程中对 begin/cbegin 的统一适配需求。

## 使用示例

```cpp
#include <yggr/container/begin.hpp>

std::vector<int> v = {1, 2, 3};
auto it = yggr::begin(v);      // 获取起始迭代器
auto cit = yggr::cbegin(v);    // 获取常量起始迭代器
```

---

如需进一步了解迭代器适配细节，可查阅 range_iterator_ex.hpp 及 boost 文档。

