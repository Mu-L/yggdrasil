---
GitHub Copilot: matrix2d.hpp 文档

---

# matrix2d.hpp

## 简介

该头文件为 3x3 二维矩阵与二维向量的乘法运算提供了泛型重载，支持不同类型、不同底层实现的矩阵与向量混合运算。适用于图形学、仿射变换、工程计算等二维线性代数场景。

## 主要内容

### 1. 主要包含内容

- 包含 `vector2d_t.hpp` 和 matrix2d_t.hpp，提供向量和矩阵的基础定义。

### 2. 运算符重载

#### 向量 × 矩阵

```cpp
template<typename ValL, typename ValR, ...>
vector2d<...> operator*(const vector2d<ValL, BaseL>& l, const matrix2d<ValR, Array, BaseR>& r);
```
- **功能**：实现列向量与矩阵的乘法，返回新向量。

#### 矩阵 × 向量

```cpp
template<typename ValL, typename ValR, ...>
vector2d<...> operator*(const matrix2d<ValL, Array, BaseL>& l, const vector2d<ValR, BaseR>& r);
```
- **功能**：实现矩阵与列向量的乘法，返回新向量。

#### 向量 *= 矩阵

```cpp
template<typename ValL, typename ValR, ...>
vector2d<ValL, BaseL>& operator*=(vector2d<ValL, BaseL>& l, const matrix2d<ValR, Array, BaseR>& r);
```
- **功能**：实现向量自乘矩阵，结果赋值回自身。

### 3. 依赖关系

- 依赖 vector2d_t.hpp、matrix2d_t.hpp。
- 支持泛型类型和底层实现的灵活组合。

## 典型用途

- 二维仿射变换、图形学、物理仿真等
- 任意类型、任意底层实现的 3x3 矩阵与二维向量运算

---



