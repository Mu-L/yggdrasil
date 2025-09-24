---
GitHub Copilot: const_var.hpp 文档

---

# const_var.hpp

## 简介

该头文件定义了常用数学常数（如 $\pi$、$e$、对数、根号等）的常量和静态获取方法，支持多种浮点类型。便于在数学、科学计算等场景中安全、便捷地获取高精度常数。

## 主要内容

### 1. 宏定义

- 定义了常用数学常数的宏，如：
  - $\pi$ (`YGGR_PP_MATH_PI`)
  - $\pi/2$、$\pi/4$、$1/\pi$、$2/\pi$
  - $e$、$\log_2 e$、$\log_{10} e$、$\ln 2$、$\ln 10$
  - $\sqrt{2}$、$\sqrt{1/2}$

### 2. const_var 结构体

```cpp
struct const_var
{
    // pi
    static f64 pi();
    template<typename T> static T pi();

    static f64 pi_div_2();
    template<typename T> static T pi_div_2();

    static f64 pi_div_4();
    template<typename T> static T pi_div_4();

    static f64 eins_div_pi();
    template<typename T> static T eins_div_pi();

    static f64 zwei_div_pi();
    template<typename T> static T zwei_div_pi();

    // e
    static f64 e();
    template<typename T> static T e();

    static f64 log2e();
    template<typename T> static T log2e();

    static f64 log10e();
    template<typename T> static T log10e();

    static f64 ln2();
    template<typename T> static T ln2();

    static f64 ln10();
    template<typename T> static T ln10();

    // sqrt(2)
    static f64 sqrt2();
    template<typename T> static T sqrt2();

    static f64 sqrt_1_div_2();
    template<typename T> static T sqrt_1_div_2();
};
```

- **功能**：以静态成员函数形式提供常用数学常数，支持 `f64`（double）和任意浮点类型（如 `float`、`long double`）。
- **类型安全**：模板方法通过 `BOOST_MPL_ASSERT` 保证类型为浮点型。

### 3. 依赖关系

- 依赖 yggrdef.h、static_assert.hpp 和 Boost 类型萃取。
- 头文件末尾取消了相关宏定义，避免污染全局命名空间。

## 典型用途

- 适用于需要高精度数学常数的科学计算、工程计算、图形学等领域。
- 支持多种浮点类型，便于泛型编程。

---



