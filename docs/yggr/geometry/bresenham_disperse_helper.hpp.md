
# 文件: bresenham_disperse_helper.hpp


## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 类 `algorithm_helper`

- 该类为工具类，禁止实例化（继承自 `nonable::noncreateable`）。
- 所有方法均为 `static`，用于辅助几何相关算法。

#### 主要方法

1. **bresenham_disperse**
   - **模板参数**：
     - `Val`：数值类型
     - `Array`：数组模板
     - `Container`：容器模板
   - **功能**：实现 Bresenham 算法，将两点间的离散点存入容器。
   - **参数**：
     - `src`：起点（`math::vector2d`）
     - `dst`：终点（`math::vector2d`）
     - `container`：用于存储离散点的容器

2. **bresenham_disperse（重载）**
   - **模板参数**：
     - `Val`、`Array`、`Line`、`Container`
   - **功能**：对 `geo_line_segment` 类型的线段进行 Bresenham 离散化，结果存入容器。
   - **参数**：
     - `line_seg`：线段对象
     - `container`：用于存储离散点的容器

## 依赖

- yggrdef.h
- upper_types.hpp
- noncreateable.hpp
- flaw_comparer.hpp
- vector2d.hpp
- geo_line_segment.hpp
- `<memory>`

## 适用场景

- 需要将二维线段离散为点集的几何算法
- 适用于图形学、路径规划等领域


