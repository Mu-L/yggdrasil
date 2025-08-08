---
# is_permutation.hpp 文档

该头文件实现了一个用于判断两个序列是否为排列关系的算法 `is_permutation`。如果编译器支持 C++11 及以上标准，则直接使用标准库的 `std::is_permutation`；否则，提供了自定义实现。

---

## 命名空间

- **yggr::algorithm**  
  算法实现所在命名空间。
- **yggr**  
  通过 `using` 声明将 `is_permutation` 引入 yggr 全局命名空间。

---

## 主要内容

### is_permutation 算法

#### 作用

判断两个序列是否为排列关系（即包含相同元素且每个元素出现次数相同，顺序可以不同）。

#### 模板参数

- `ForwardIterator1`：第一个序列的前向迭代器类型
- `ForwardIterator2`：第二个序列的前向迭代器类型

#### 用法示例

```cpp
#include <yggr/algorithm/is_permutation.hpp>
#include <vector>

std::vector<int> a = {1, 2, 3};
std::vector<int> b = {3, 1, 2};
bool result = yggr::is_permutation(a.begin(), a.end(), b.begin()); // result == true
```

#### 实现说明（C++11 以下）

- 首先比较两个序列的前缀是否完全相同，若完全相同则直接返回 true。
- 若不完全相同，则统计每个未重复元素在两个序列中的出现次数，若每个元素出现次数一致，则为排列关系，否则不是。
- 时间复杂度 O(N^2)（最坏情况下）。

#### C++11 及以上

- 直接使用标准库 `std::is_permutation`。

---

## 版权声明

MIT License，详见文件头部注释。

---

## 适用场景

- 判断两个区间是否为排列关系，适用于泛型容器和自定义类型。
- 可用于 C++98/03 环境下的兼容性开发。

---

如需进一步了解具体用法，请参考相关的 Yggdrasil 框架文档或示例代码。

