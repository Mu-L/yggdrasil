# swap.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了通用的 swap 工具函数，支持：
- 不同类型对象的交换（T1 与 T2 可不同）
- 右值引用与左值引用混合交换（兼容 C++11/Boost.Move）
- 兼容 std、boost、yggr 命名空间下的 swap
- 解决 MSVC、GCC 等不同编译器下的 ADL、重载歧义等问题

## 3. 主要内容与实现

### 3.1 std 命名空间扩展
- 为 std 命名空间扩展了支持不同类型（T1, T2）的 swap 重载。
- 支持右值引用与左值引用混合的 swap。
- 内部实现采用 Boost.Move 进行高效移动交换，避免不必要的拷贝。

### 3.2 boost 命名空间扩展
- 为 boost 命名空间扩展了右值引用相关的 swap 重载（GCC/MSVC 差异处理）。
- 保证在 Boost 容器、Boost 类型下也能高效安全地使用 swap。

### 3.3 yggr 命名空间扩展
- 提供 yggr::swap，自动调用 std::swap，实现统一接口。
- 兼容 C++98/03/11/20，不同编译器下均可安全使用。
- 针对老版本 C++ 和非 GCC，提供单类型 swap 重载。

### 3.4 设计细节与注意事项
- 通过 reinterpret_cast 和 boost::addressof 避免自交换和未定义行为。
- 通过 boost::disable_if 和 boost::is_same 控制模板重载选择，避免类型冲突。
- 详细注释了 MSVC 下的重载歧义问题及解决方案。
- 兼容 Boost.Move 和标准右值引用。

## 4. 典型用法

```cpp
#include <yggr/utility/swap.hpp>

int a = 1, b = 2;
yggr::swap(a, b); // 交换 a 和 b

std::string s1 = "hello", s2 = "world";
yggr::swap(s1, s2); // 交换字符串

std::vector<int> v1, v2;
yggr::swap(v1, v2); // 交换容器

// 支持不同类型的交换（如自定义类型 T1, T2）
```

## 5. 注意事项

- 若需支持自定义类型的 swap，需确保类型间的赋值和移动操作是安全的。
- MSVC 下如遇到 swap 重载歧义，请检查模板参数和重载定义。
- 不建议对同一对象自交换（已做地址判断优化）。

## 6. 总结

本文件为 Yggdrasil 框架提供了高效、通用、类型安全的 swap 工具，兼容多种编译器和 C++ 标准，适合在泛型编程、容器操作、算法实现等多种场景下安全交换任意类型对象。

---

