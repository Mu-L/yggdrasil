---
GitHub Copilot:  is_iterator.hpp 文档

---

# 文件：is_iterator.hpp

## 简介
该头文件定义了类型萃取工具 `is_iterator`，用于在编译期判断某类型是否为迭代器类型。支持指针、标准迭代器和自定义实现了 `iterator_category` 的类型。

## 主要内容

- **命名空间**：`yggr::iterator_ex`
- **核心结构体**：
  - `is_iterator<T>`：继承自 `boost::mpl::bool_`，其 `value` 为 `true` 表示为迭代器类型，否则为 `false`。

## 判断逻辑

- 若类型 `T` 是指针类型，或
- 类型 `T` 拥有 `iterator_category` 成员（即为标准或自定义迭代器），
- 则 `is_iterator<T>::value` 为 `true`，否则为 `false`。

## 用法示例

```cpp
#include <yggr/iterator_ex/is_iterator.hpp>
#include <vector>
#include <iostream>

int main() {
    std::cout << yggr::is_iterator<int*>::value << std::endl; // 输出1
    std::cout << yggr::is_iterator<std::vector<int>::iterator>::value << std::endl; // 输出1
    std::cout << yggr::is_iterator<int>::value << std::endl; // 输出0
}
```

## 依赖
- Boost
- yggr 基础类型、has_iterator_category 工具
- 标准库 `<iterator>`

## 版权声明
版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可协议。

---



