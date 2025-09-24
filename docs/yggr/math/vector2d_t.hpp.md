---
GitHub Copilot: vector2d_t.hpp 文档

---

# vector2d_t.hpp

## 简介

该头文件实现了通用二维向量（vector2d）模板类，支持任意数值类型和底层数组定制。提供向量的构造、赋值、基本运算、几何变换、序列化等功能，适用于图形学、物理仿真、工程计算等二维线性代数场景。

## 主要内容

### 1. vector2d 模板类

```cpp
template<
    typename Val,
    template <typename _Val, std::size_t> class Base = yggr::array
>
class vector2d : public Base<typename upper_signed<Val>::type, 3>
{
    // ...
};
```

- **Val**：元素类型（如 float、double、int 等）
- **Base**：底层一维数组类型模板，默认为 `yggr::array`

#### 主要成员
- 静态常量：维度为 2，底层数组长度为 3（齐次坐标支持）
- 类型定义：元素类型、底层数组类型
- 构造函数：支持默认、元素列表、数组、拷贝等多种方式
- 赋值、比较、交换、向量运算（加减乘除、点积、叉积、归一化、模长等）
- 成员变量：`x`、`y`、`w`（齐次坐标）

### 2. 依赖与扩展

- 支持 Boost 移动语义、类型萃取、哈希等
- 支持序列化（包含相关头文件）
- 依赖 sqrt.hpp、sign.hpp、modulus.hpp、flaw_comparer.hpp 等
- 适配泛型算法和高性能数值计算

### 3. 典型用途

- 二维仿射变换、图形学、物理仿真等
- 任意类型、任意底层实现的二维向量运算
- 泛型编程和模板元编程场景

---



