---
GitHub Copilot:  iterator_category_check.hpp 文档

---

# 文件：iterator_category_check.hpp

## 简介
该头文件定义了一组类型萃取工具，用于在编译期判断某类型是否为特定类别的迭代器。支持判断随机访问、双向、前向、输出、输入等标准迭代器类型。

## 主要内容

- **命名空间**：`yggr::iterator_ex`
- **核心结构体**：
  - `is_random_access_iterator<T>`：判断类型 `T` 是否为随机访问迭代器。
  - `is_bidirectional_iterator<T>`：判断类型 `T` 是否为双向迭代器。
  - `is_forward_iterator<T>`：判断类型 `T` 是否为前向迭代器。
  - `is_output_iterator<T>`：判断类型 `T` 是否为输出迭代器。
  - `is_input_iterator<T>`：判断类型 `T` 是否为输入迭代器。
  - `iterator_category_check_result`：统一 true/false 类型定义及常量。

## 判断逻辑

- 通过 `iterator_category_ex<T>::type` 获取类型 `T` 的迭代器类别标签。
- 利用 `boost::is_base_of` 判断该标签是否继承自对应的标准迭代器标签（如 `std::random_access_iterator_tag` 等）。

## 用法示例

```cpp
#include <yggr/iterator_ex/iterator_category_check.hpp>
#include <vector>
#include <iostream>

int main() {
    std::cout << yggr::is_random_access_iterator<std::vector<int>::iterator>::value << std::endl; // 输出1
    std::cout << yggr::is_input_iterator<std::vector<int>::iterator>::value << std::endl; // 输出1
}
```

## 依赖
- Boost
- yggr 基础类型、iterator_traits 工具
- 标准库 `<iterator>`

## 版权声明
版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可协议。

---



