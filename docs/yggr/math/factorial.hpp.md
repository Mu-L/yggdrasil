---
GitHub Copilot: factorial.hpp 文档

---

# factorial.hpp

## 简介

该头文件实现了阶乘（factorial）的运行时和编译时计算，支持任意整数类型和自定义类型。适用于组合数学、概率统计、算法竞赛等需要阶乘运算的场景。

## 主要内容

### 1. 阶乘运行时计算

```cpp
template<typename T>
typename boost::enable_if<boost::is_class<T>, T>::type
    factorial(const T& val);

template<typename T>
typename boost::disable_if<boost::is_class<T>, T>::type
    factorial(T val);
```

- **功能**：计算 $n!$（n 的阶乘）。
- **实现**：通过 `factorial_detail<T>` 结构体实现，支持类型安全检查和泛型编程。
- **断言**：保证输入为非负整数。

### 2. 阶乘编译时计算（模板元编程）

```cpp
template<std::size_t N>
struct factorial_t : public detail::factorial_t_detail<N> {};
```

- **功能**：在编译期递归计算 $N!$，适用于模板元编程场景。
- **实现**：递归继承 `boost::mpl::size_t`，支持 $N=0$ 和 $N=1$ 的特化。

### 3. 依赖关系

- 依赖 native_t.hpp、upper_types.hpp、flaw_comparer.hpp 等类型萃取和比较工具。
- 使用 Boost 的类型萃取和 MPL 元编程库。

## 典型用途

- 适用于组合数、排列数、概率统计等数学运算。
- 支持运行时和编译时两种方式，便于泛型和模板元编程。

---



