---
# random.h 文档

## 文件简介

random.h 提供了一个静态随机数生成工具类 `yggr::random`，支持生成整数和浮点数的随机值，并可指定随机数的范围。该实现基于 Boost.Random 库，适用于多种类型的随机数需求。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`
- `<yggr/mplex/limits.hpp>`
- `<yggr/type_traits/upper_types.hpp>`
- `<yggr/nonable/noncreateable.hpp>`
- `<boost/random/linear_congruential.hpp>`
- `<boost/random/uniform_int.hpp>`
- `<boost/random/uniform_real.hpp>`
- `<boost/random/variate_generator.hpp>`
- `<boost/type_traits/is_floating_point.hpp>`

---

## 命名空间

- yggr
- `yggr::detail`

---

## 主要类与函数

### yggr::random

- **说明**：静态工具类，禁止实例化（继承自 `nonable::noncreateable`）。
- **主要类型**：
  - `base_generator_type`：底层随机数生成器，使用 `boost::minstd_rand`。
- **主要静态方法**：
  - `static void init(void);`  
    初始化随机数生成器（实现未在头文件中给出）。
  - `template<typename T> static T gen_random(void);`  
    生成类型为 T 的随机数，范围为类型的最小值到最大值。
  - `template<typename T> static T gen_random(const T& s_range, const T& e_range);`  
    生成类型为 T 的随机数，范围为 `[s_range, e_range)`。

### 全局函数

- `template<typename T> T gen_random(void);`  
  等价于 `random::gen_random<T>()`。
- `template<typename T> T gen_random(const T& s_range, const T& e_range);`  
  等价于 `random::gen_random(s_range, e_range)`。

---

## 内部实现

### yggr::detail::genner

- 模板类 `genner<T, is_float>` 根据类型 T 是否为浮点数选择不同的随机数分布。
  - 对于浮点数类型，使用 `boost::uniform_real`。
  - 对于整数类型，使用 `boost::uniform_int`。
- 支持无参和带范围的随机数生成。

---

## 用法示例

````cpp
#include <yggr/base/random.h>

// 生成一个 int 类型的随机数
int r1 = yggr::gen_random<int>();

// 生成一个 [10, 100) 范围内的 int 随机数
int r2 = yggr::gen_random<int>(10, 100);

// 生成一个 double 类型的随机数
double r3 = yggr::gen_random<double>();

// 生成一个 [0.5, 2.5) 范围内的 double 随机数
double r4 = yggr::gen_random<double>(0.5, 2.5);
````

---

## 注意事项

- 随机数生成器为静态成员，线程安全性需根据实际使用场景评估。
- 整数范围的随机数生成要求 `s_range < e_range`，且范围在类型允许的最小最大值之间。
- 浮点数范围的随机数生成为左闭右开区间 `[s_range, e_range)`。

---

 

