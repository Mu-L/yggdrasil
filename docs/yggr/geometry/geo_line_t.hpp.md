
# 文件:geo_line_t.hpp




## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry` 命名空间下。

### 主要类

#### `geo_line<Position, Base>`

- **模板参数**：
  - `Position`：点类型（如 `vector2d`、`vector3d` 等）
  - `Base`：点数组类型（默认为 `yggr::array`）

- **主要成员**：
  - `src_pos`、`dst_pos`：直线的两个点
  - 类型别名：`pos_type`、`point_type`、`pos_value_type` 等

- **构造与赋值**：
  - 支持默认、点对、拷贝/移动、不同类型直线等多种构造方式
  - 支持多种赋值和 swap 操作

- **主要方法**：
  - `set_line()`：设置直线的两个端点
  - `clear()`：清空直线
  - `is_line()`：判断是否为有效直线（两点不重合）
  - `src_to_dst()` / `dst_to_src()`：获取方向向量
  - `cross_point()`：与另一条直线的交点
  - `equal_to()` / `not_equal_to()` / `operator==` / `operator!=`：直线等价性判断（无向）

- **序列化**：
  - 支持 Boost.Serialization

- **swap 支持**：
  - 提供 `swap` 函数，支持标准库和 Boost 的 swap 机制

### 依赖

- array.hpp、utility、sign.hpp
- Boost MPL、Range、Serialization 等库

### 适用场景

- 任意维度直线的建模、比较、几何运算
- 图形学、CAD、路径规划等领域





