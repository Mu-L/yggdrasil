---
GitHub Copilot: determinant.hpp 文档

---

# determinant.hpp

## 简介

该头文件实现了通用的行列式（Determinant）模板类，支持任意类型、任意行列数的矩阵行列式运算。支持拷贝、移动、赋值、比较、交换等操作，并可与自定义数组类型协作。适用于线性代数、数值计算、工程计算等领域。

## 主要内容

### 1. determinant 模板类

```cpp
template<typename Val, std::size_t ROW, std::size_t COL,
         template<typename _Val, std::size_t> class Base = yggr::array>
class determinant : public Base< Base<typename upper_signed<Val>::type, COL>, ROW>
{
    // ...成员类型定义...
    determinant();
    determinant(const base_type& right);
    determinant(BOOST_RV_REF(base_type) right);
    determinant(const this_type& right);
    determinant(BOOST_RV_REF(this_type) right);
    template<typename OVal, template<typename, std::size_t> class OBase>
    determinant(const OBase<OVal, E_ROW_LENGTH * E_COL_LENGTH>& right);
    // ...赋值、比较、交换等成员函数...
};
```

- **Val**：元素类型（如 float、double、int 等）
- **ROW**、**COL**：行数、列数
- **Base**：底层数组类型模板，默认为 `yggr::array`

#### 主要成员函数
- 构造函数、拷贝/移动构造、赋值运算符
- `swap`：交换内容
- `equal_to`/`not_equal_to`：矩阵内容比较
- `row_size`/`col_size`：获取行列数
- 其它成员（如零化、赋值、访问等，详见源码）

### 2. 依赖与扩展

- 支持 Boost 移动语义、类型萃取、哈希等
- 支持自定义容器类型
- 依赖 array_indexes_permutation_parity.hpp、flaw_comparer.hpp 等用于数学运算和精度比较
- 支持序列化（包含相关头文件）

### 3. 典型用途

- 任意类型、任意维度的矩阵行列式运算
- 线性代数、工程计算、科学计算等领域
- 支持泛型编程和高性能数值计算

---



