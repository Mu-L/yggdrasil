
# 文件:geo_polygon_t.hpp


## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry` 命名空间下。

### 主要类

#### `geo_polygon<Position, Alloc, Base>`

- **模板参数**：
  - `Position`：点类型（如 `vector2d`、`vector3d` 等）
  - `Alloc`：分配器类型（默认为 `container::vector<Position>` 的分配器）
  - `Base`：底层容器类型（默认为 `container::vector`）

- **主要成员**：
  - 继承自底层容器，存储多边形顶点
  - `_prop`：多边形的面积或相关属性
  - 类型别名：`pos_type`、`point_type`、`prop_type` 等

- **构造与赋值**：
  - 支持三点、四点、容器、拷贝/移动、不同类型多边形等多种构造方式
  - 支持多种赋值和 swap 操作

- **主要方法**（部分，未全部展开）：
  - `clear()`：清空多边形
  - `prop()`：获取多边形面积或相关属性
  - `swap()`：交换多边形内容
  - 其他如点集操作、几何关系判断等

- **序列化**：
  - 支持 Boost.Serialization

### 依赖

- vector.hpp、utility、type_traits 等
- Boost MPL、Range、Serialization 等库

### 适用场景

- 任意维度多边形的建模、面积计算、几何运算
- 图形学、CAD、空间分析等领域





