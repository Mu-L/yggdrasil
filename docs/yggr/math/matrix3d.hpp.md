---
GitHub Copilot: matrix3d.hpp 文档

---

# matrix3d.hpp

## 简介

该头文件为 4x4 三维矩阵与三维向量的乘法运算提供了泛型重载，支持不同类型、不同底层实现的矩阵与向量混合运算。适用于三维图形学、仿射变换、工程计算等三维线性代数场景。

## 主要内容

### 1. 主要包含内容

- 包含 `vector3d_t.hpp` 和 matrix3d_t.hpp，提供三维向量和三维矩阵的基础定义。

### 2. 运算符重载

#### 向量 × 矩阵

```cpp
template<typename ValL, typename ValR, ...>
vector3d<...> operator*(const vector3d<ValL, BaseL>& l, const matrix3d<ValR, Array, BaseR>& r);
```
- **功能**：实现列向量与 4x4 矩阵的乘法，返回新向量。

#### 矩阵 × 向量

```cpp
template<typename ValL, typename ValR, ...>
vector3d<...> operator*(const matrix3d<ValL, Array, BaseL>& l, const vector3d<ValR, BaseR>& r);
```
- **功能**：实现 4x4 矩阵与列向量的乘法，返回新向量。

#### 向量 *= 矩阵

```cpp
template<typename ValL, typename ValR, ...>
vector3d<ValL, BaseL>& operator*=(vector3d<ValL, BaseL>& l, const matrix3d<ValR, Array, BaseR>& r);
```
- **功能**：实现向量自乘矩阵，结果赋值回自身。

### 3. 依赖关系

- 依赖 vector3d_t.hpp、matrix3d_t.hpp。
- 支持泛型类型和底层实现的灵活组合。

## 典型用途

- 三维仿射变换、图形学、物理仿真等
- 任意类型、任意底层实现的 4x4 矩阵与三维向量运算

---



