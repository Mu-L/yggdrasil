
# 文件:geo_line_segment_t.hpp


## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry` 命名空间下。

### 主要类

#### `geo_line_segment<Position, Array, Base>`

- **模板参数**：
  - `Position`：点类型（如 `vector2d`、`vector3d` 等）
  - `Array`：点数组类型（默认为 `yggr::array`）
  - `Base`：线段基类（默认为 `geo_line`）

- **主要成员**：
  - `src_pos`、`dst_pos`：起点和终点（继承自 `geo_line`）
  - 类型别名：`pos_type`、`point_type`、`pos_value_type` 等

- **构造与赋值**：
  - 支持默认、点对、拷贝/移动、不同类型线段等多种构造方式
  - 支持多种赋值和 swap 操作

- **主要方法**：
  - `center_pos()`：获取线段中点
  - `length()` / `length_sq()`：获取线段长度/平方
  - `cross_point()`：与另一线或线段的交点
  - `is_in_it()`：判断点或线段是否在本线段上
  - `is_superposition_line_segment()`：判断是否为重叠线段
  - `get_superposition_line_segment()`：获取重叠部分线段
  - `equal_to()` / `not_equal_to()` / `operator==` / `operator!=`：线段等价性判断（无向）

- **序列化**：
  - 支持 Boost.Serialization

- **swap 支持**：
  - 提供 `swap` 函数，支持标准库和 Boost 的 swap 机制

### 依赖

- geo_line.hpp（线类基类）
- array.hpp、utility、move、sqrt.hpp
- Boost MPL、Range、Serialization 等库

### 适用场景

- 任意维度线段的建模、比较、几何运算
- 图形学、CAD、路径规划等领域





