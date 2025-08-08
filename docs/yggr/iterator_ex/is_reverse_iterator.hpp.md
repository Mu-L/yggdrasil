# is_reverse_iterator.hpp 文档

## 1. 版权声明
MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了 `is_reverse_iterator` 类型萃取工具，可在编译期判断某类型是否为反向迭代器。支持 `std::reverse_iterator`、`boost::reverse_iterator` 及自定义反向迭代器类型，适合泛型算法、容器适配、迭代器工具等场景。

## 3. 主要类型与功能

### 3.1 is_reverse_iterator

- **主模板**：`yggr::iterator_ex::is_reverse_iterator<T>`
  - 继承自 `boost::mpl::bool_`，其 `value` 为 true 表示 T 是反向迭代器，false 表示不是。
  - 自动适配标准库、Boost 及自定义类型。

### 3.2 内部实现机制

- **_is_reverse_iterator_t**
  - 针对 `std::reverse_iterator`、`boost::reverse_iterator` 做了特化，直接判定为 true。
  - 对其它类型，通过类型特征（如 `iterator_type`、`iterator_category`）和模板元编程判断。
  - 针对 libc++ 的 `__wrap_iter` 做了特化，判定为 false（防止误判）。
- **is_reverse_iterator_t_impl**
  - 默认判定为 false。
  - 支持通过宏导入自定义类型的判定结果。

### 3.3 自定义反向迭代器支持

- **宏定义**：`YGGR_IS_REVERSE_ITERATOR_IMPORT(type, value)`
  - 可为自定义类型导入反向迭代器判定结果。例如：
    ```cpp
    YGGR_IS_REVERSE_ITERATOR_IMPORT(MyReverseIter, true)
    ```
  - 这样 `is_reverse_iterator<MyReverseIter>::value` 即为 true。

### 3.4 兼容性

- 支持 C++98/03/11/14/17/20，兼容 Boost、libstdc++、libc++ 等主流实现。
- 针对 Clang/libc++ 的 `__wrap_iter` 做了特殊处理，防止误判。

---

## 4. 典型用法

```cpp
#include <yggr/iterator_ex/is_reverse_iterator.hpp>
#include <vector>
#include <algorithm>

typedef std::vector<int>::reverse_iterator rev_iter;
static_assert(yggr::is_reverse_iterator<rev_iter>::value, "Should be reverse_iterator");

typedef std::vector<int>::iterator fwd_iter;
static_assert(!yggr::is_reverse_iterator<fwd_iter>::value, "Should not be reverse_iterator");

// 支持自定义类型导入
class MyReverseIter { /* ... */ };
YGGR_IS_REVERSE_ITERATOR_IMPORT(MyReverseIter, true)
static_assert(yggr::is_reverse_iterator<MyReverseIter>::value, "Custom reverse_iterator");
```

---

## 5. 设计要点

- **类型安全**：所有判断均在编译期完成，无运行时开销。
- **高扩展性**：支持自定义类型的导入，适合复杂泛型编程。
- **兼容性强**：适配主流标准库和 Boost，兼容多平台多编译器。
- **泛型友好**：适合模板算法、容器适配、迭代器工具等场景。

---

## 6. 注意事项

- 对于自定义反向迭代器类型，需手动通过宏导入判定结果。
- 若类型未定义 `iterator_type` 或 `iterator_category`，可能无法自动判定。

---

## 7. 总结

本文件为 Yggdrasil 框架提供了高效、类型安全、可扩展的反向迭代器类型萃取工具，适合泛型算法、容器适配、迭代器工具等多种高级 C++ 场景。其设计兼顾性能、易用性和扩展性，是大型 C++ 工程中迭代器类型判断的理想选择。

---

