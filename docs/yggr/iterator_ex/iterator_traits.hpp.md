---
GitHub Copilot:  iterator_traits.hpp 文档

---

# 文件：iterator_traits.hpp

## 简介
该头文件定义了多种迭代器 traits 工具，兼容 Boost 和标准库，支持自定义迭代器类型的 value、reference、pointer、difference、category 等类型萃取。对 Boost 1.56.0 及以上版本做了特殊适配。

## 主要内容

- **命名空间**：`yggr::iterator_ex`
- **核心结构体**：
  - `iterator_value_ex<Iter>`：获取迭代器的 value_type。
  - `iterator_reference_ex<Iter>`：获取迭代器的 reference 类型，支持 const 迭代器自动推断。
  - `iterator_pointer_ex<Iter>`：获取迭代器的 pointer 类型。
  - `iterator_difference_ex<Iter>`：获取迭代器的 difference_type。
  - `iterator_category_ex<Iter>`：获取迭代器的 category 类型。
- **兼容性**：
  - 针对 Boost 1.56.0 及以上版本，reference 类型支持 const 推断。
  - 依赖 `detail::iterator_traits_impl` 做底层实现。

## 用法示例

```cpp
#include <yggr/iterator_ex/iterator_traits.hpp>
#include <vector>
#include <type_traits>

static_assert(std::is_same<
    yggr::iterator_ex::iterator_value_ex<std::vector<int>::iterator>::type,
    int
>::value, "value_type should be int");
```

## 依赖
- Boost
- yggr 基础类型、is_const_iterator 工具、detail::iterator_traits_impl
- 标准库 `<iterator>`

## 版权声明
版权所有 (c) 2010-2024 yggdrasil。遵循 MIT 许可协议。

---



