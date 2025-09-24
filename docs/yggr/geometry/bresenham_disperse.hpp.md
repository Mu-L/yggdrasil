
# 文件:bresenham_disperse.hpp

## 文件简介

- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry` 命名空间下。

### 主要函数

1. **bresenham_disperse (2D)**
   - **模板参数**：
     - `Container`：用于存储离散点的容器类型
     - `T1, T2`：坐标类型
     - `Base1, Base2`：底层数组模板
   - **功能**：对二维空间中的两点，使用 Bresenham 算法将其间的所有离散点存入容器。
   - **参数**：
     - `cont`：容器
     - `src_pos`：起点（`math::vector2d`）
     - `dst_pos`：终点（`math::vector2d`）

2. **bresenham_disperse (3D)**
   - **模板参数**：
     - 同上，适用于三维空间
   - **功能**：对三维空间中的两点，使用 Bresenham 算法将其间的所有离散点存入容器。
   - **参数**：
     - `cont`：容器
     - `src_pos`：起点（`math::vector3d`）
     - `dst_pos`：终点（`math::vector3d`）

3. **bresenham_disperse (线段)**
   - **模板参数**：
     - `Container`：容器类型
     - `Pos`：点类型
     - `Array`、`Base`：底层模板
   - **功能**：对 `geo_line_segment` 类型的线段进行 Bresenham 离散化，结果存入容器。
   - **参数**：
     - `cont`：容器
     - `line_seg`：线段对象

### 依赖

- vector2d.hpp
- vector3d.hpp
- bresenham_disperse.hpp
- geo_line_segment.hpp
- `boost::add_reference`

### 适用场景

- 需要将二维或三维线段离散为点集的几何算法
- 适用于图形学、路径规划、体素化等领域



