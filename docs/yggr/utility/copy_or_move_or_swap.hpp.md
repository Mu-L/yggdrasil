# copy_or_move_or_swap.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了 `copy_or_move_or_swap` 工具函数。该函数根据类型是否支持 swap 成员函数、是否支持移动语义，自动选择 swap、move 或 copy 的最佳方式进行对象赋值，提升泛型代码的效率和安全性。

## 3. 主要实现原理

### 3.1 类型特性检测
- 通过模板元编程，检测类型 L 和 R 是否拥有 swap 成员函数（支持 L.swap(R) 或 R.swap(L)）。
- 使用 SFINAE 技术和 sizeof 检测 swap 存在性，生成类型特征。

### 3.2 copy_or_move_or_swap_helper
- 针对不同的 swap 检测结果，提供三种特化实现：
  - **2**：L 有成员函数 swap(R)，优先调用 `l.swap(r)`
  - **1**：R 有成员函数 swap(L)，优先调用 `r.swap(l)`
  - **0**：都没有 swap，则尝试移动赋值（C++11）或拷贝赋值（C++03）

### 3.3 copy_or_move_or_swap 函数重载
- 对于右值引用（C++11），优先尝试 move 或 swap。
- 对于左值引用（C++03），优先尝试 swap 或 copy。
- 对于 const 引用，始终使用拷贝赋值。

## 4. 典型用法

```cpp
#include <yggr/utility/copy_or_move_or_swap.hpp>

struct Foo {
    void swap(Foo& other); // 推荐实现
    // ...
};

Foo a, b;
yggr::copy_or_move_or_swap(a, b); // 自动选择 swap、move 或 copy

std::vector<int> v1, v2;
yggr::copy_or_move_or_swap(v1, v2); // 优先使用 swap 或 move
```

## 5. 设计要点

- **自动选择**：无需手动判断类型特性，自动选择最优赋值方式。
- **高效安全**：优先使用 swap（高效且异常安全），其次 move，最后 copy。
- **兼容性强**：支持 C++03 和 C++11，自动适配右值引用和 Boost.Move。
- **泛型友好**：适用于任意类型，尤其适合模板和容器操作。

## 6. 注意事项

- 若类型未实现 swap，且不支持移动语义，则会退化为拷贝赋值。
- 对于 const 引用，只能进行拷贝赋值。
- 建议为自定义类型实现 swap 成员函数以获得最佳性能。

## 7. 总结

本文件为 Yggdrasil 框架提供了高效、智能的对象赋值工具，适合泛型编程、容器操作、资源管理等多种场景。通过自动检测类型特性，最大化利用 swap 和 move 的优势，提升代码性能和安全性。

---

