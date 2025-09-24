
# 文件:geo_plane.hpp


## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry` 命名空间下。

### 主要类

#### `geo_plane<Val, Base>`

- **模板参数**：
  - `Val`：平面系数类型（如 float、double 等）
  - `Base`：底层数组类型（默认为 `yggr::array`）

- **主要成员**：
  - `a, b, c, d`：平面方程 $ax + by + cz + d = 0$ 的系数
  - 类型别名：`val_type`、`base_type` 等

- **构造与赋值**：
  - 支持默认、法向量+点、三点式、拷贝/移动、不同类型平面等多种构造方式
  - 支持多种赋值和 swap 操作

- **主要方法**（部分，未全部展开）：
  - 支持通过点和法向量、三点确定平面
  - 支持与点、直线、平面等的关系判断与计算
  - 支持序列化

### 依赖

- vector3d.hpp（三维向量）
- array.hpp、utility、type_traits 等
- Boost Range、Move、MPL 等库

### 适用场景

- 三维空间平面的建模、交互、几何运算
- 图形学、CAD、空间分析等领域





