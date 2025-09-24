
# 文件:geo_rectangle_t.hpp


## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry` 命名空间下。

### 主要类

#### `geo_rectangle<Position, Base>`

- **模板参数**：
  - `Position`：点类型（如 `vector2d`、`vector3d` 等）
  - `Base`：点数组类型（默认为 `yggr::array`）

- **主要成员**：
  - `min_pos`、`max_pos`：矩形的最小点和最大点（对角点）
  - 类型别名：`pos_type`、`point_type`、`pos_value_type` 等

- **构造与赋值**：
  - 支持默认、点对、容器、拷贝/移动、不同类型矩形等多种构造方式
  - 支持多种赋值和 swap 操作

- **主要方法**（部分，未全部展开）：
  - 支持通过点对或点集自动生成包围矩形
  - 支持矩形的几何关系判断、扩展、裁剪等操作
  - 支持序列化

### 依赖

- array.hpp、utility、type_traits 等
- Boost MPL、Range、Enable_if 等库

### 适用场景

- 任意维度矩形的建模、包围盒计算、几何运算
- 图形学、CAD、空间分析等领域





