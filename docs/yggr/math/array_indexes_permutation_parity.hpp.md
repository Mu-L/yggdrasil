---
GitHub Copilot: array_indexes_permutation_parity.hpp 文档

---

# array_indexes_permutation_parity.hpp

## 简介

该头文件实现了数组索引排列的奇偶性（permutation parity）和符号（sign）计算的模板元编程工具。主要用于在编译期确定给定索引排列的奇偶性（即排列是偶排列还是奇排列），常用于行列式、置换群等数学和算法场景。

## 主要内容

### 1. sign_array_indexes 模板

```cpp
template<s_size_type I_IDX, s_size_type IDX_SIZE, bool ASC_OR_DESC = true>
struct sign_array_indexes
{
    static const s_size_type value = (0 == array_indexes_permutation_parity<I_IDX, IDX_SIZE, ASC_OR_DESC>::value % 2) ? 1 : -1;
};
```
- **功能**：根据排列的奇偶性，返回 $+1$（偶排列）或 $-1$（奇排列）。
- **参数**：
  - `I_IDX`：当前索引
  - `IDX_SIZE`：索引总数
  - `ASC_OR_DESC`：排列方向，`true` 为升序，`false` 为降序

### 2. array_indexes_permutation_parity 模板

```cpp
template<s_size_type I_IDX, s_size_type IDX_SIZE, bool ASC_OR_DESC = true>
struct array_indexes_permutation_parity
{
    static const s_size_type value = ...;
};
```
- **功能**：计算给定索引排列的逆序数（即排列的奇偶性）。
- **特化**：对 `IDX_SIZE` 为 0、1、2 的情况做了特化处理，提升编译期效率。

### 3. detail::indexes_loop 递归模板

- **功能**：递归计算逆序数，支持不同排列方向和边界条件。
- **实现**：通过模板递归和静态常量实现编译期计算。

### 4. 依赖关系

- 依赖 yggrdef.h 和 static_constant.hpp，用于类型定义和静态常量声明。

## 典型用途

- 适用于需要在编译期判断排列奇偶性的场景，如行列式符号、置换群、组合数学等。
- 通过模板元编程实现零运行时开销的数学属性判定。

---



