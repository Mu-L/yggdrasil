
# 文件:bezier_curve.hpp



## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry::detail` 命名空间下。

### 主要功能

#### 1. 贝塞尔曲线取值

- **bezier_curve_value**
  - 支持通过迭代器区间或容器，计算任意阶贝塞尔曲线在参数 $t$ 或 $(t_1, t_2)$ 下的值。
  - 内部调用 De Casteljau 算法（`decasteljau`）。

#### 2. 贝塞尔曲线导数

- **bezier_curve_derivation_init**
  - 初始化导数计算所需的差分数组。

- **bezier_curve_derivation_cal_of_stack / bezier_curve_derivation_cal_of_heap**
  - 针对不同阶数，分别用栈或堆数组高效计算贝塞尔曲线的导数。

- **bezier_curve_derivation**
  - 统一接口，自动选择栈或堆实现，支持一元和二元参数。
  - 支持通过迭代器区间或容器直接计算。

### 依赖

- decasteljau.hpp（De Casteljau 算法实现）
- vector.hpp、array.hpp
- copy_or_move_or_swap.hpp
- `boost` 类型萃取与启用机制

### 适用场景

- 任意阶贝塞尔曲线的数值计算
- 贝塞尔曲线的导数（切线/速度）计算
- 支持一元和二元参数（如曲面）





