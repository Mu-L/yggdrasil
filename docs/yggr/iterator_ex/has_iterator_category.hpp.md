---
GitHub Copilot:  has_iterator_category.hpp 文档

---

# 文件：has_iterator_category.hpp

## 简介
该头文件定义了一个类型萃取工具 `has_iterator_category`，用于在编译期判断某类型是否定义了 `iterator_category` 类型成员。该工具常用于泛型算法和容器开发中，判断类型是否符合标准迭代器的要求。

## 主要内容

- **命名空间**：`yggr::iterator_ex`
- **核心结构体**：
  - `detail::_has_iterator_category_t<Iter>`：内部实现，利用 SFINAE 技术检测类型 `Iter` 是否有 `iterator_category` 成员。
  - `has_iterator_category<Iter>`：对外接口，继承自 `boost::mpl::bool_`，其 `value` 为 `true` 表示有该成员，否则为 `false`。

## 用法示例

```cpp
#include <yggr/iterator_ex/has_iterator_category.hpp>
#include <vector>
#include <iostream>

int main() {
    std::cout << yggr::has_iterator_category<std::vector<int>::iterator>::value << std::endl; // 输出1
    std::cout << yggr::has_iterator_category<int>::value << std::endl; // 输出0
}
```

## 依赖
- Boost MPL
- yggr 基础类型定义

## 版权声明
版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可协议。

---



