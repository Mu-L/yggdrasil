---
GitHub Copilot:  is_const_iterator.hpp 文档

---

# 文件：is_const_iterator.hpp

## 简介
该头文件定义了类型萃取工具 `is_const_iterator`，用于在编译期判断某类型是否为常量迭代器或常量指针。常用于泛型算法、容器开发等场景下类型特性的静态判断。

## 主要内容

- **命名空间**：`yggr::iterator_ex`
- **核心结构体**：
  - `detail::_is_const_iterator_t<T, is_pointer, is_iter>`：内部实现，分别针对指针类型、迭代器类型和其他类型做特化判断。
  - `is_const_iterator<T>`：对外接口，继承自 `boost::mpl::bool_`，其 `value` 为 `true` 表示为常量迭代器或常量指针，否则为 `false`。

## 判断逻辑

- 若类型 `T` 是指针，则判断其指向类型是否为 const。
- 若类型 `T` 是迭代器（具有 `iterator_category`），则判断其 `pointer` 成员所指类型是否为 const。
- 其他情况均为 `false`。

## 用法示例

```cpp
#include <yggr/iterator_ex/is_const_iterator.hpp>
#include <vector>
#include <iostream>

int main() {
    std::cout << yggr::is_const_iterator<const int*>::value << std::endl; // 输出1
    std::cout << yggr::is_const_iterator<std::vector<int>::const_iterator>::value << std::endl; // 输出1
    std::cout << yggr::is_const_iterator<int*>::value << std::endl; // 输出0
}
```

## 依赖
- Boost
- yggr 基础类型、has_iterator_category 工具
- 标准库 `<iterator>`

## 版权声明
版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可协议。

---



