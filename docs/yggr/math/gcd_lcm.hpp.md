---
GitHub Copilot: gcd_lcm.hpp 文档

---

# gcd_lcm.hpp

## 简介

该头文件实现了最大公约数（GCD）和最小公倍数（LCM）的运行时和编译时计算，支持泛型整数类型和模板元编程。适用于数论、分数约简、算法竞赛等需要 GCD/LCM 运算的场景。

## 主要内容

### 1. 运行时 GCD/LCM 计算

```cpp
template<typename T>
typename boost::enable_if<boost::is_class<T>, T>::type
    gcd(const T& num1, const T& num2);

template<typename T>
typename boost::disable_if<boost::is_class<T>, T>::type
    gcd(T num1, T num2);

template<typename T>
typename boost::enable_if<boost::is_class<T>, T>::type
    lcm(const T& num1, const T& num2);

template<typename T>
typename boost::disable_if<boost::is_class<T>, T>::type
    lcm(T num1, T num2);
```

- **功能**：计算两个数的最大公约数和最小公倍数。
- **实现**：GCD 使用辗转相除法，LCM 通过 $lcm(a, b) = a \times b / gcd(a, b)$ 计算。
- **类型安全**：仅限整数类型，编译期断言。

### 2. 编译时 GCD/LCM 计算（模板元编程）

```cpp
template<int dividend, int divisor>
struct gcd_t : public boost::mpl::int_<...> {};

template<int dividend, int divisor>
struct lcm_t : public boost::mpl::int_<...> {};
```

- **功能**：在编译期递归计算 GCD 和 LCM，适用于模板元编程场景。
- **实现**：递归继承 `boost::mpl::int_`，支持 $divisor=0$ 的特化。

### 3. 依赖关系

- 依赖 native_t.hpp、foo_input_arg_t.hpp、Boost MPL 等。

## 典型用途

- 适用于分数约简、数论算法、数学建模等场景。
- 支持运行时和编译时两种方式，便于泛型和模板元编程。

---



