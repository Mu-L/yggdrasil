---
GitHub Copilot: combination.hpp 文档

---

# combination.hpp

## 简介

该头文件实现了组合数（combination）的计算函数和模板，支持运行时和编译时的组合数计算。组合数 $C(n, m)$ 表示从 $n$ 个不同元素中取出 $m$ 个元素的方式数，是组合数学中的基础运算。

## 主要内容

### 1. combination 函数模板

```cpp
template<typename T>
typename boost::enable_if<boost::is_class<T>, T>::type
    combination(const T& n, const T& m);

template<typename T>
typename boost::disable_if<boost::is_class<T>, T>::type
    combination(T n, T m);
```

- **功能**：计算组合数 $C(n, m)$。
- **实现**：内部调用 `detail::pascals_triangle_detail<T>`，利用杨辉三角递推公式进行组合数计算。
- **重载**：分别支持类类型和非类类型参数。

### 2. combination_t 编译时组合数模板

```cpp
template<std::size_t N, std::size_t M>
struct combination_t : public detail::pascals_triangle_t<N, M> {};
```

- **功能**：在编译期计算组合数 $C(N, M)$，适用于模板元编程场景。
- **依赖**：`detail::pascals_triangle_t`，用于组合数的编译期计算。

### 3. 依赖关系

- 依赖于 pascals_triangle.hpp，用于组合数的递推实现。
- 使用了 Boost 的类型萃取工具。

## 典型用途

- 适用于需要组合数计算的数学、算法、统计等领域。
- 支持运行时和编译时两种方式，便于泛型编程和模板元编程。

---



