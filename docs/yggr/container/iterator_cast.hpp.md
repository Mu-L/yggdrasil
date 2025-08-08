---
# iterator_cast.hpp 文档

## 概述

`iterator_cast.hpp` 是 yggdrasil 项目中用于容器迭代器类型转换的辅助头文件。该文件提供了将 const_iterator 转换为 iterator 以及对 iterator 的引用进行类型适配的工具函数，便于在泛型编程和容器操作中安全、统一地进行迭代器类型转换。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含基础定义头文件 `<yggr/base/yggrdef.h>` 和 `<iterator>`。
- 在 `yggr::container` 命名空间下定义：
  - `cast_to_iterator(Container&, const Container::iterator&)`：返回 iterator 的常量引用。
  - `cast_to_iterator(Container&, Container::iterator&)`：返回 iterator 的非常量引用。
  - `cast_to_iterator(Container&, const Container::const_iterator&)`：将 const_iterator 转换为 iterator，通过 begin() 和 std::advance/std::distance 实现位置同步。

## 适用场景

- 需要在泛型算法或容器操作中，将 const_iterator 转换为 iterator 的场景。
- 需要对 iterator 引用进行类型适配，保证接口统一的场景。

## 使用示例

```cpp
#include <yggr/container/iterator_cast.hpp>

std::vector<int> v = {1, 2, 3};
auto cit = v.cbegin();
auto it = yggr::container::cast_to_iterator(v, cit); // 转为 iterator
```

---

本文件为 yggdrasil 容器适配体系的迭代器类型转换辅助组件，便于在模板库和泛型容器开发中统一处理迭代器类型转换。

