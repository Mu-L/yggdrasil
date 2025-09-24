
# 文件:decasteljau.hpp


## 文件简介


- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry::detail` 命名空间下。

### 主要功能

#### 1. De Casteljau 算法实现

- **支持一元与二元参数**（如贝塞尔曲线与贝塞尔曲面）
- **支持任意阶数**，自动选择栈或堆实现以优化性能（`decasteljau_stack_limit` 控制阈值）

#### 2. 主要接口

- `decasteljau_of_stack` / `decasteljau_of_heap`
  - 通过迭代器区间，计算贝塞尔曲线/曲面在参数 $t$ 或 $(t_1, t_2)$ 下的值
  - 阶数较小时用栈数组，高阶时用堆数组

- `decasteljau`
  - 统一接口，自动选择栈/堆实现
  - 支持通过迭代器或容器直接调用

#### 3. 类型与断言

- 使用 `boost` 类型萃取与启用机制，支持泛型编程
- 多处断言保证参数合法性与类型安全

### 依赖

- array.hpp
- vector.hpp
- upper_types.hpp
- is_iterator.hpp
- is_container.hpp
- range_iterator_ex.hpp
- range_value_ex.hpp
- flaw_comparer.hpp
- `boost` 相关类型工具

### 适用场景

- 任意阶贝塞尔曲线/曲面的数值计算
- 图形学、CAD、动画等领域的曲线插值与建模



