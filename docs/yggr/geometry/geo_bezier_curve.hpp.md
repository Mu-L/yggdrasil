
# 文件:geo_bezier_curve.hpp


## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry` 命名空间下。

### 主要功能

#### 1. 贝塞尔曲线数值计算与导数

- **geo_bezier_curve_value**
  - 支持通过迭代器、容器、`geo_bezier_curve` 对象，计算任意阶贝塞尔曲线在参数 $t$ 或 $(t_1, t_2)$ 下的值。

- **geo_bezier_curve_derivation**
  - 支持通过迭代器、容器、`geo_bezier_curve` 对象，计算任意阶贝塞尔曲线在参数 $t$ 或 $(t_1, t_2)$ 下的导数（切线/速度）。

#### 2. 贝塞尔曲线与矩阵变换

- 支持贝塞尔曲线与 2D/3D 矩阵的乘法（左乘、右乘、复合赋值），可用于仿射变换、旋转、缩放等操作。
- 针对不同维度（2D/3D/4D）自动选择合适的矩阵类型。

#### 3. 类型与泛型支持

- 支持任意阶、任意点类型、任意数组类型的贝塞尔曲线
- 依赖 Boost MPL、Range、Enable_if 等泛型与类型萃取机制

### 依赖

- geo_bezier_curve_t.hpp（贝塞尔曲线泛型类实现）
- matrix2d.hpp、matrix3d.hpp
- range_iterator_ex.hpp
- Boost MPL、Range、Enable_if 等库

### 适用场景

- 任意阶贝塞尔曲线的数值计算、导数、变换
- 图形学、CAD、动画、路径规划等领域





