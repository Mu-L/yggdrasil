
# 文件:bresenham_disperse.hpp



## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry::detail` 命名空间下。

### 主要函数

#### 1. `bresenham_disperse_2d`

- **模板参数**：
  - `Container`：用于存储离散点的容器类型
  - `T1, T2, T3, T4`：整数类型，表示起点和终点的 x/y 坐标
- **功能**：实现二维 Bresenham 算法，将两点间的所有整数点坐标存入容器。
- **断言与类型检查**：保证所有类型为整数，容器可写，坐标不越界。

#### 2. `bresenham_disperse_3d`

- **模板参数**：
  - `Container`：用于存储离散点的容器类型
  - `T1`~`T6`：整数类型，表示起点和终点的 x/y/z 坐标
- **功能**：实现三维 Bresenham 算法，将两点间的所有整数点坐标存入容器。
- **断言与类型检查**：同上，支持三维空间。

### 依赖

- is_container.hpp
- iterator.hpp
- range_value_ex.hpp
- `boost` 类型萃取与启用机制
- `mplex::numeric_limits` 用于类型边界检查

### 适用场景

- 需要将二维或三维线段离散为整数点集的几何算法
- 适用于图形学、体素化、路径规划等领域



