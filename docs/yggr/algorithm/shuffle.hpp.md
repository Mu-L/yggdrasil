---
# shuffle.hpp 文档

该头文件实现了泛型的序列随机打乱（shuffle）算法，兼容 C++98/03/11/17 及 Boost 环境。根据编译环境自动选择合适的打乱实现，保证在不同标准下都能安全高效地使用。

---

## 命名空间

- **yggr::algorithm**  
  算法实现主命名空间。
- **yggr**  
  通过 using 声明将 shuffle 引入全局命名空间。

---

## 主要内容

### shuffle 算法

#### 作用

对指定区间的元素进行随机打乱（洗牌），常用于随机化容器内容、实现洗牌算法等。

#### 重载与实现

- **C++17 之前（含 C++98/03/11）**  
  - 若支持 `std::random_shuffle`，则使用该函数。
  - 提供默认随机数生成器 `default_random_number_generator`，基于 `yggr::gen_random`。
  - 支持自定义随机数生成器。
- **C++17 及以上**  
  - 使用标准库 `std::shuffle`，基于现代随机数引擎（如 `std::mt19937`）。
  - 内部默认使用 `std::random_device` 和 `std::mt19937`。

#### 用法示例

```cpp
#include <yggr/algorithm/shuffle.hpp>
#include <vector>
std::vector<int> v = {1, 2, 3, 4, 5};
yggr::shuffle(v.begin(), v.end());
```

---

## 其他说明

- 自动适配不同 C++ 标准和 Boost 特性，无需手动区分环境。
- 支持自定义随机数生成器，满足高级需求。
- 依赖于 Yggdrasil 框架的随机数工具和类型定义。

---

## 版权声明

MIT License，详见文件头部注释。

---

## 适用场景

- 容器、数组等序列的随机打乱。
- 需要兼容多种 C++ 标准的项目。
- 需要自定义或高质量随机数生成器的场景。

---

如需进一步了解具体用法，请参考相关的 Yggdrasil 框架文档或示例代码。