---
GitHub Copilot: math.hpp 文档

---

# math.hpp

## 简介

该头文件为 yggr 数学模块的总入口，统一包含了常用数学常量、基础算法、数值工具、向量与矩阵等相关头文件。便于用户一次性引入全部数学功能，提升开发效率和代码可维护性。

## 主要内容

### 1. 统一包含的模块

- **常量与基础工具**：const_var.hpp, `range_value.hpp`, `modulus.hpp`, `sign.hpp`, `sqrt.hpp`
- **数值算法**：gcd_lcm.hpp（最大公约数/最小公倍数）、factorial.hpp（阶乘）、division_ex.hpp（扩展除法）、`odd_even_number.hpp`（奇偶性判断）
- **组合数学**：`pascals_triangle.hpp`, arrangement.hpp, combination.hpp
- **概率与统计**：elo_rating.hpp（Elo 评分）、`odds.hpp`（赔率）、`moving_avg_accumulator.hpp`（滑动平均）
- **数值比较**：flaw_comparer.hpp（容差比较器）
- **泛型工具**：make_zero_value.hpp（零值生成器）
- **线性代数**：`vector2d.hpp`, `vector3d.hpp`, `matrix2d.hpp`, `matrix3d.hpp`
- **排列相关**：array_indexes_permutation_parity.hpp
- **复数支持**：`<complex>`

### 2. 用法

只需包含本头文件，即可获得 yggr 数学模块的全部功能，无需单独包含各子模块。

```cpp
#include <yggr/math/math.hpp>
```

### 3. 典型用途

- 科学计算、工程计算、算法竞赛、数据分析等需要丰富数学工具的场景。
- 便于统一管理和升级数学相关代码。

---

如需生成 Doxygen 风格注释或更详细的模块说明，请告知！

