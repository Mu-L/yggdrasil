---
GitHub Copilot:  unwrap_reverse_iterator.hpp 文档

---

# 文件：unwrap_reverse_iterator.hpp

## 简介
该头文件定义了类型萃取工具 `unwrap_reverse_iterator`，用于在编译期获取反向迭代器（如 `std::reverse_iterator` 或 `boost::reverse_iterator`）所包装的原始迭代器类型。对于非反向迭代器类型，返回 `mplex::null_type`。

## 主要内容

- **命名空间**：`yggr::iterator_ex`
- **核心结构体**：
  - `unwrap_reverse_iterator<T>`：主接口，继承自内部实现，自动判断并提取反向迭代器的底层类型。
  - 内部实现 `_unwrap_reverse_iterator_t<T>`：对标准库、Boost 及模板反向迭代器类型做特化处理。
- **特性**：
  - 支持 `std::reverse_iterator`、`boost::reverse_iterator` 及自定义模板反向迭代器类型。
  - 若类型不是反向迭代器，则返回 `mplex::null_type`。

## 用法示例

```cpp
#include <yggr/iterator_ex/unwrap_reverse_iterator.hpp>
#include <vector>
#include <iterator>
#include <type_traits>

static_assert(std::is_same<
    yggr::unwrap_reverse_iterator<std::vector<int>::reverse_iterator>::type,
    std::vector<int>::iterator
>::value, "type should be std::vector<int>::iterator");
```

## 依赖
- Boost
- yggr 基础类型、is_reverse_iterator 工具
- 标准库 `<iterator>`

## 版权声明
版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可协议。

---

