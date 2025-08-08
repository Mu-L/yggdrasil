---
# knuth_morris_pratt.hpp 文档

该头文件实现了通用的 Knuth-Morris-Pratt（KMP）字符串搜索算法模板类及相关辅助函数。KMP 算法是一种高效的字符串查找算法，适用于在大文本或数据流中查找子串，具有线性时间复杂度。

---

## 命名空间

- **yggr::algorithm**  
  KMP 算法的主要实现。
- **yggr::algorithm::swap_support**  
  提供 swap 支持。
- **std / boost**  
  通过 using 声明支持 swap。

---

## 主要类

### `knuth_morris_pratt`

#### 模板参数

- `PatIter`：模式串迭代器类型
- `PatTraits`：模式串特征（traits），默认 `detail::kmp_traits<PatIter>`
- `PatPred`：模式串比较谓词，默认 `std::equal_to`

#### 主要成员

- **构造函数**：支持不同初始化方式（带/不带谓词）。
- **拷贝/移动构造与赋值**：支持对象的拷贝和移动。
- **operator()**：对目标序列进行搜索，返回匹配区间的迭代器对。
- **reinit**：重新初始化模式串及相关参数。
- **swap**：交换两个对象内容。
- **pat_comp**：获取当前的比较谓词。
- **skip_table**（仅 Debug）：获取内部的跳跃表（失配表）。

#### 内部实现

- 使用失配表（skip table）加速搜索过程。
- `init_skip_table` 用于初始化失配表。
- `do_search` 为核心搜索实现，采用失配表优化。

---

## 主要函数

### `knuth_morris_pratt_search`

一组重载的全局函数，便于直接对区间进行 KMP 搜索，支持自定义谓词等。

#### 典型用法

```cpp
auto result = yggr::knuth_morris_pratt_search(
    corpus_begin, corpus_end, pattern_begin, pattern_end);
```

---

## 其他说明

- 提供了 swap 的泛型支持，可用于标准库和 Boost。
- 头文件依赖于 Yggdrasil 框架的基础设施（如 `kmp_traits`、`vector` 等）。
- 该实现为模板，适用于任意可迭代区间。
- 需要保证传入的迭代器类型和谓词等参数的正确性。
- 依赖于 Yggdrasil 框架的其他头文件和 Boost 库。

---

## 版权声明

MIT License，详见文件头部注释。

---

## 适用场景

- 高效地在大文本或数据流中查找子串或子序列。
- 需要自定义比较方式的场景。

---

如需进一步了解具体用法，请参考相关的 Yggdrasil 框架文档或示例代码。

