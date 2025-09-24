---
GitHub Copilot: modulus.hpp 文档

---

# modulus.hpp

## 简介

该头文件实现了整数和浮点数的统一取模（模运算）工具，支持泛型类型和自动类型推导。适用于数值计算、循环结构、信号处理等需要模运算的场景。

## 主要内容

### 1. modulus_handler 模板结构体

- **功能**：根据类型是否为浮点数，自动选择合适的模运算实现。
- **实现**：
  - 对于整数类型，使用 `%` 运算符。
  - 对于浮点类型，使用 `std::fmod`。

### 2. modulus / modulus_set 函数模板

```cpp
template<typename L, typename R>
auto modulus(const L& l, const R& r) -> ...;

template<typename L, typename R>
L& modulus_set(L& l, const R& r);
```

- **功能**：
  - `modulus`：返回 $l$ 对 $r$ 的模结果，自动适配类型。
  - `modulus_set`：将 $l$ 取模后赋值回自身，返回引用。
- **类型推导**：通过 `modulus_operator_result` 自动推导返回类型。

### 3. 依赖关系

- 依赖 operator_result.hpp、Boost 类型萃取、`<cmath>`。

## 典型用途

- 适用于整数和浮点数的统一模运算需求。
- 泛型算法、模板元编程中的数值取模。

---



