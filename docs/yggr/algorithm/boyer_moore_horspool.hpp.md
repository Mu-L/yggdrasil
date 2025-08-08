---
# boyer_moore_horspool.hpp 文档

该头文件实现了 Boyer-Moore-Horspool 字符串搜索算法的泛型模板类和相关辅助函数。Boyer-Moore-Horspool 算法是一种高效的字符串查找算法，适用于大文本中查找子串。

---

## 主要内容

### 命名空间

- `yggr::algorithm`  
  主要算法实现。
- `yggr::algorithm::swap_support`  
  提供 swap 支持。
- `std` 和 `boost`  
  通过 using 声明支持 swap。

---

## 主要类

### `boyer_moore_horspool`

#### 模板参数

- `PatIter`：模式串迭代器类型
- `PatTraits`：模式串特征（traits），默认使用 `detail::bm_traits<PatIter>`
- `Key_Extractor`：键提取器，默认使用 `container::identity`
- `PatPred`：模式串比较谓词，默认使用 `std::equal_to`

#### 主要成员

- 构造函数支持不同的初始化方式（带/不带谓词、键提取器等）。
- 支持拷贝、移动构造与赋值。
- `operator()`：对目标序列进行搜索，返回匹配区间的迭代器对。
- `reinit`：重新初始化模式串及相关参数。
- `swap`：交换两个对象内容。
- `key_extor`、`pat_comp`：获取当前的键提取器和比较谓词。

#### 内部实现

- 使用 `bm_skip_table` 构建跳跃表以加速搜索。
- `do_search` 为核心搜索实现，采用逆序比较和跳跃表优化。
- `build_skip_table` 用于初始化跳跃表。

---

## 主要函数

### `boyer_moore_horspool_search`

一组重载的全局函数，便于直接对区间进行 Boyer-Moore-Horspool 搜索，支持自定义谓词、键提取器等。

#### 典型用法

```cpp
auto result = yggr::boyer_moore_horspool_search(
    corpus_begin, corpus_end, pattern_begin, pattern_end);
```

---

## 其他

- 提供了 `swap` 的泛型支持，可用于标准库和 Boost。
- 头文件依赖于 Yggdrasil 框架的基础设施（如 `bm_skip_table`、`bm_traits`、`identity` 等）。

---

## 注意事项

- 该实现为模板，适用于任意可迭代区间。
- 需要保证传入的迭代器类型和谓词等参数的正确性。
- 依赖于 Yggdrasil 框架的其他头文件和 Boost 库。

---

## 版权声明

MIT License，详见文件头部注释。

---

## 适用场景

- 高效地在大文本或数据流中查找子串或子序列。
- 需要自定义比较方式或键提取方式的场景。

---

如需进一步了解具体用法，请参考相关的 Yggdrasil 框架文档或示例代码。

