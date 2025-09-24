---
GitHub Copilot:  insert_iterator.hpp 文档

---

# 文件：insert_iterator.hpp

## 简介
该头文件定义了 `yggr::iterator_ex::insert_iterator` 及其辅助工具，用于为自定义容器或特殊容器提供插入迭代器功能。其行为与标准库的 `std::insert_iterator` 类似，但支持自定义类型和移动语义。

## 主要内容

- **命名空间**：`yggr::iterator_ex`
- **核心类与函数**：
  - `insert_iterator<Container>`：插入迭代器，支持移动和拷贝插入，适用于泛型算法。
  - `inserter(Container&, Iterator)`：工厂函数，生成 `insert_iterator` 实例。
  - 内部辅助结构体 `container_insert_helper`，根据容器类型（类/非类）选择插入方式。
- **特性**：
  - 支持移动语义（C++11及以上）。
  - 兼容自定义容器和标准容器。
  - 仅在 C++14 及以下自定义实现，C++14 以上直接使用标准库实现。

## 用法示例

```cpp
#include <yggr/iterator_ex/insert_iterator.hpp>
#include <vector>
#include <algorithm>

std::vector<int> v1 = {1, 2, 3};
std::vector<int> v2 = {4, 5, 6};
auto it = yggr::inserter(v1, v1.begin());
std::copy(v2.begin(), v2.end(), it);
// v1 现在为 {4, 5, 6, 1, 2, 3}
```

## 依赖
- Boost
- yggr 基础类型、range_ex 工具
- 标准库 `<iterator>`

## 版权声明
版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可协议。

---



