---
GitHub Copilot: iterator.hpp 文档

---

# 文件：iterator.hpp

## 简介
该头文件定义了多种迭代器通用操作工具，包括前进（advance）、距离计算（distance）、获取下一个/上一个迭代器（next/prev）等。接口风格与 C++11 标准库一致，并支持自定义实现以适配不同平台和类型。

## 主要内容

- **命名空间**：`yggr::iterator_ex`
- **核心函数**：
  - `advance`：将迭代器前进指定步数。
  - `advance_copy`：返回前进指定步数后的新迭代器，不修改原迭代器。
  - `distance`：计算两个迭代器之间的距离。
  - `next`：获取下一个迭代器（支持步数参数）。
  - `prev`：获取上一个迭代器（支持步数参数）。
- **实现说明**：
  - `advance`、`advance_copy`、`distance` 由 `detail` 命名空间实现，支持自定义扩展。
  - `next` 和 `prev` 提供与标准库一致的接口，支持常量表达式和内联优化。

## 用法示例

```cpp
#include <yggr/iterator_ex/iterator.hpp>
#include <vector>
#include <iostream>

int main() {
    std::vector<int> v = {1, 2, 3, 4};
    auto it = v.begin();
    yggr::advance(it, 2); // it 指向 3
    auto it2 = yggr::next(v.begin(), 3); // it2 指向 4
    auto it3 = yggr::prev(v.end(), 2); // it3 指向 3
    std::cout << *it << " " << *it2 << " " << *it3 << std::endl;
}
```

## 依赖
- advance.hpp
- distance.hpp

## 版权声明
版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可协议。

---



