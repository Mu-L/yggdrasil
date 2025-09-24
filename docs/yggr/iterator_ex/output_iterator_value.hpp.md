---
GitHub Copilot: output_iterator_value.hpp 文档

---

# 文件：output_iterator_value.hpp

## 简介
该头文件定义了类型萃取工具 `output_iterator_value`，用于在编译期获取输出迭代器的值类型。支持自动识别 `value_type` 或 `char_type`，并对无效类型返回 `null_type`，便于泛型编程时类型推断和特化。

## 主要内容

- **命名空间**：`yggr::iterator_ex`
- **核心结构体**：
  - `output_iterator_value<T>`：主接口，继承自内部实现，自动判断并提取输出迭代器的值类型。
  - 内部实现 `_output_iterator_value_t<T, ...>`：根据是否为输出迭代器、是否有 `value_type` 或 `char_type`，选择合适的类型。
- **特性**：
  - 优先提取 `value_type`，若无则尝试 `char_type`。
  - 若类型为 `void` 或不存在，则返回 `mplex::null_type`。
  - 支持自定义输出迭代器类型。

## 用法示例

```cpp
#include <yggr/iterator_ex/output_iterator_value.hpp>
#include <ostream>
#include <type_traits>

static_assert(std::is_same<
    yggr::output_iterator_value<std::ostream_iterator<char>>::type,
    char
>::value, "type should be char");
```

## 依赖
- Boost
- yggr 基础类型、type_traits 工具、iterator_category_check 工具
- 标准库 `<iterator>`

## 版权声明
版权所有 (c) 2014-2022 yggdrasil。遵循 MIT 许可协议。

---



