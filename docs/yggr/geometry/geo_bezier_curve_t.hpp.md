
# 文件:geo_bezier_curve_t.hpp


## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry` 命名空间下。

### 主要类

#### `geo_bezier_curve<P, N, Array>`

- **模板参数**：
  - `P`：控制点类型（如 `vector2d`、`vector3d` 等）
  - `N`：曲线阶数（如二阶、三阶等）
  - `Array`：控制点数组类型（默认为 `yggr::array`）

- **主要成员**：
  - `ctrl_points`：控制点数组
  - 类型别名：`point_type`、`result_point_type`、`point_array_type` 等

- **构造与赋值**：
  - 支持默认、迭代器区间、容器、变参、拷贝/移动等多种构造方式
  - 支持多种赋值和 swap 操作

- **主要方法**：
  - `value(t)` / `operator[](t)`：计算参数 $t$ 下的曲线点
  - `derivation(t)` / `operator()(t)`：计算参数 $t$ 下的导数（切线/速度）
  - `reverse_curve()` / `reverse()` / `operator~`：反转曲线控制点顺序
  - `equal_to` / `operator==` / `operator!=`：曲线等价性判断
  - `order()` / `size()`：获取阶数和控制点数量

- **序列化**：
  - 支持 Boost.Serialization

### 依赖

- bezier_curve.hpp（贝塞尔曲线算法实现）
- `yggr/array`、utility、mplex、range_ex 等
- Boost MPL、Range、Serialization 等库

### 适用场景

- 任意阶贝塞尔曲线的建模、插值、导数计算
- 图形学、CAD、动画、路径规划等领域





