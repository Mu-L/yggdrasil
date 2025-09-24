---
# 文件：container_category_check.hpp

## 简介

`container_category_check.hpp` 是 yggdrasil 项目中用于容器类型迭代器类别检测的元编程工具头文件。它通过类型萃取和模板继承，自动判断任意类型 T 是否为容器，并进一步判断其迭代器类别（如随机访问、双向、前向），为泛型算法和容器适配提供类型支持。

## 主要内容

- **命名空间**：所有内容位于 `yggr::container_ex` 命名空间下。
- **依赖**：
  - `<yggr/container_ex/is_container.hpp>`：判断类型是否为容器。
  - `<yggr/iterator_ex/iterator_category_check.hpp>`：迭代器类别检测基础。
  - Boost MPL、类型萃取相关。
- **核心结构体与功能**：
  1. **container_category_ex_detail<T, is_container>**
     - 若 T 不是容器，继承自 `mplex::null_type`。
     - 若 T 是容器，继承自 `boost::iterator_category`，自动获取其迭代器类别。
  2. **container_category_ex<T>**
     - 对外统一接口，继承自 `container_category_ex_detail<T>`，自动判断并提取容器的迭代器类别。
  3. **containter_category_check_result**
     - 继承自 `iterator_category_check_result`，用于类型检测结果的统一封装。
  4. **is_random_access_container<T>**
     - 判断 T 是否为随机访问容器（如 `std::vector`），结果为 `boost::mpl::bool_`。
  5. **is_bidirectional_container<T>**
     - 判断 T 是否为双向容器（如 `std::list`），结果为 `boost::mpl::bool_`。
  6. **is_forward_container<T>**
     - 判断 T 是否为前向容器，结果为 `boost::mpl::bool_`。
- **别名**：
  - 通过 `using` 语句将上述类型提升到 yggr 命名空间，便于直接使用。

## 用法示例

```cpp
#include <yggr/container_ex/container_category_check.hpp>
#include <vector>

static_assert(yggr::is_random_access_container<std::vector<int>>::value, "vector 应为随机访问容器");
static_assert(!yggr::is_bidirectional_container<std::vector<int>>::value, "vector 不是双向容器");
```

## 适用场景

- 泛型算法中需要根据容器类型自动适配不同的迭代器操作。
- 需要在编译期判断容器的迭代器类别，实现类型安全的容器适配和优化。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---



