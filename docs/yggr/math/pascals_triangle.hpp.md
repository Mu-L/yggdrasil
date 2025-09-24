---
GitHub Copilot: pascals_triangle.hpp 文档

---

# pascals_triangle.hpp

## 简介

该头文件实现了杨辉三角（Pascal's Triangle）相关的组合数计算工具，支持运行时和编译时两种方式。适用于组合数学、概率统计、算法竞赛等需要组合数 $C(n, m)$ 运算的场景。

## 主要内容

### 1. pascals_triangle_detail 结构体

- **功能**：递归实现杨辉三角的组合数计算。
- **实现**：采用递归公式 $C(n, m) = C(n-1, m-1) + C(n-1, m)$，边界 $C(n, 0) = C(n, n) = 1$。

### 2. pascals_triangle 函数模板

```cpp
template<typename T>
T pascals_triangle(const T& n, const T& m);
```
- **功能**：运行时计算组合数 $C(n, m)$，支持类类型和基础类型。

### 3. pascals_triangle_t 模板结构体（编译时）

```cpp
template<std::size_t N, std::size_t M>
struct pascals_triangle_t : public boost::mpl::size_t<...> {};
```
- **功能**：编译期递归计算组合数 $C(N, M)$，适用于模板元编程。
- **实现**：递归继承 `boost::mpl::size_t`，边界 $C(N, 0) = C(N, N) = 1$。

### 4. 依赖关系

- 依赖 native_t.hpp、foo_input_arg_t.hpp、Boost MPL 等。

## 典型用途

- 组合数、排列数、概率统计等数学运算。
- 支持运行时和编译时两种方式，便于泛型和模板元编程。

---



