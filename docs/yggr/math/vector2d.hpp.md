---
GitHub Copilot: vector2d.hpp 文档

---

# vector2d.hpp

## 简介

该头文件为二维向量（vector2d）提供了点积（dot）和叉积（cross）操作的泛型重载，支持不同类型、不同底层实现的向量混合运算。适用于图形学、物理仿真、工程计算等二维线性代数场景。

## 主要内容

### 1. 主要包含内容

- 包含 vector2d_t.hpp（向量定义）、operator_dot.hpp（点积适配器）、operator_cross.hpp（叉积适配器）。

### 2. 运算符重载

#### 点积（dot product）

- 支持以下形式的点积运算：
  - `vector2d * doter<vector2d>`
  - `doter<vector2d> * vector2d`
  - `doter<vector2d> * doter<vector2d>`
- 实现方式：调用向量的 `dot` 成员函数。

#### 叉积（cross product）

- 支持以下形式的叉积运算：
  - `vector2d * crosser<vector2d>`
  - `crosser<vector2d> * vector2d`
  - `crosser<vector2d> * crosser<vector2d>`
- 实现方式：调用向量的 `cross` 成员函数。

### 3. 依赖关系

- 依赖 vector2d_t.hpp、operator_dot.hpp、operator_cross.hpp。
- 支持泛型类型和底层实现的灵活组合。

## 典型用途

- 二维仿射变换、图形学、物理仿真等
- 任意类型、任意底层实现的二维向量点积与叉积运算

---

