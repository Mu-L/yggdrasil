---
GitHub Copilot: sqrt.hpp 文档

---

# sqrt.hpp

## 简介

该头文件实现了多种类型的平方根（sqrt）和倒平方根（rsqrt）计算，支持快速近似算法和标准库精确算法，适用于浮点数、复数及泛型类型。适用于图形学、物理仿真、数值分析等对性能和精度有不同需求的场景。

## 主要内容

### 1. 快速平方根与倒平方根

- `fast_sqrt` / `fast_rsqrt`：采用著名的快速平方根算法（Quake III Fast Inverse Square Root），支持 `f32` 和 `f64`，可选多次迭代提升精度。
- 通过宏 `YGGR_USE_FAST_MATH` 控制是否默认使用快速算法。

### 2. 标准平方根与倒平方根

- 若未定义 `YGGR_USE_FAST_MATH`，则默认使用 `std::sqrt` 及其倒数。

### 3. 泛型与复数支持

- 支持 `std::complex<T>` 类型的平方根和倒平方根。
- 支持任意类型，自动提升为更高精度的浮点类型后计算。

### 4. 依赖关系

- 依赖 `<cmath>`、`<complex>`、`yggr/type_traits/upper_types.hpp>` 等。

## 典型用途

- 图形学、物理仿真、信号处理等对性能和精度有不同需求的场景。
- 支持快速近似和高精度计算，适合泛型编程。

---



