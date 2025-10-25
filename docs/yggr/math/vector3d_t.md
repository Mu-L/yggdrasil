# `vector3d_t.hpp` 文档

## 概述

`yggr/math/vector3d_t.hpp` 定义了一个三维向量模板类 `yggr::math::vector3d<Val, Base>`，用于表示 3D 向量（外加一个齐次坐标位 `w`），并提供常用的矢量运算、算术运算符重载、序列化与哈希支持。

该类是模板化的：可以指定元素类型 `Val`（内部使用 `upper_signed<Val>::type` 作为实际存储类型）以及底层容器模板 `Base`（默认为 `yggr::array`）。

文档档目标读者：使用或维护 `vector3d` 的开发者，需要知道构造/赋值语义、常用方法和注意事项。

## 文件位置

- 源文件：`yggr/math/vector3d_t.hpp`
- 本文档：`docs/vector3d_t.md`

## 设计要点（简要）

- 表示 3D 向量，但内部以长度为 4 的数组存储（前三个元素为 x,y,z，第四个元素为 w，通常用于齐次坐标）。
- 采用模板化设计，支持任意数值类型（`int`, `float`, `double` 等）以及可替换的底层静态数组类型。
- 提供丰富的成员函数和非成员操作符，包括：加/减/乘/除（标量与分量）、点积、叉积、长度、归一化、比较、哈希、序列化。
- 支持移动语义与拷贝语义（含针对 `Base` 的移动/拷贝构造与赋值重载）。

## 类型与常量

- 模板参数：
  - `Val`：元素类型。
  - `Base`：元素容器模板，形式为 `template <typename _Val, std::size_t> class Base`，默认 `yggr::array`。

- 别名与静态常量：
  - `typedef typename upper_signed<Val>::type value_type`：实际存储的元素类型（向上转换为带符号类型）。
  - `YGGR_STATIC_CONSTANT(std::size_t, E_LENGTH = 3)`：逻辑长度 3（x,y,z）。
  - `YGGR_STATIC_CONSTANT(std::size_t, E_ARRAY_LENGTH = E_LENGTH + 1)`：数组长度 4（含 w）。
  - `typedef Base<val_type, E_ARRAY_LENGTH> base_type`：底层数组类型。

- 成员引用（按名字访问数组元素）：
  - `val_type& x, &y, &z, &w`：分别绑定到 `base_type::operator[](0..3)`。

## 构造与析构

支持多种构造：

- 默认构造 `vector3d()`：将 `x=0, y=0, z=0, w=1`（源码中默认将 w 设为 1）。
- 三元素构造 `vector3d(const OVal1& v1, const OVal2& v2, const OVal3& v3)`：x,y,z 被设置，w 设为 1。
- 四元素构造（含 w） `vector3d(const OVal1&, const OVal2&, const OVal3&, const OVal4&)`。
- 从 `base_type` 的移动/拷贝构造。
- 从另一个 `vector3d<OVal, OBase>` 的转换构造（含可传入新的 w）。
- 移动构造/拷贝构造均被显式实现。

析构器为默认析构（无额外资源）。

## 赋值与 swap

- 支持对 `base_type` 的移动/拷贝赋值。
- 支持 `vector3d` 与其他 `vector3d`（不同模板参数）的赋值（会进行静态转换）。
- 提供 `swap` 重载（接受 `base_type` 和 `vector3d` 的多种组合），并在命名空间 `yggr::math::swap_support` 中导出以便 ADL 使用。

## 访问与常用方法

- `static size_type size()`：返回 3。
- `static size_type array_size()`：返回 4。
- `void clear()`：将前三个元素置 0，w 置 1。
- `bool is_zero()`：使用 `flaw_comparer` 做近似零比较，检查 x,y,z 是否都为零。
- `bool is_zero_w()`：同时检查 w。
- `size_type zero_count()` / `zero_count_w()`：统计为零的分量数量（近似比较）。

- `const this_type& positive()`：返回自身（按正向操作）。
- `negate()`：返回按相反值的新 `vector3d`。

- 算术功能（成员形式）
  - `plus/minus/multiplies/divides/modulus`：按分量返回新的 `vector3d`，使用 `operator_result` trait 决定结果类型（并自动选择合适的 `Base`）。
  - `*_set` 版本：原地更新（如 `plus_set`、`multiplies_set` 等）。

- `normalize()`：返回归一化后的向量（返回浮点类型的 `vector3d`）。内部调用私有 `prv_normalize()`。
  - `prv_normalize()`：使用长度平方 `length_sq()`，对于每个分量使用 sign 和 sqrt((v*v)/len_sq) 来重建分量（在长度为 0 时直接返回）。
  - 注意：`normalize()` 返回的是 `vector3d<typename upper_float<val_type>::type>`（浮点版本）。

- `round()` / `floor()` / `ceil()`：分别对四个分量做四舍五入/向下取整/向上取整（对 w 也做相应处理）。

- `sum()` / `sum_w()`：返回 x+y+z（或包含 w）的和。源码中对 w 有断言检查（见注意项）。

- `length()`：返回长度（浮点类型），会调用 `length_sq()` 并取 sqrt。
- `length_sq()`：返回 x*x + y*y + z*z（对 w 有断言检查）。

- `dot(const vector3d& right)`：返回标量点积（x*x + y*y + z*z），会对 `w` 做断言检查（确保 w 的某种值，见注意项）。
- `cross(const vector3d& right)`：返回叉积向量，结果的 `w` 被置成默认值（`result_val_type()`）。

- `type_cast`：支持把向量转换为不同元素类型或通过 handler 转换为任意结果。

- `hash()`：使用 `boost::hash_combine` 将文字 "vector3d" 与底层 `base_type` 结合产生哈希值。

## 非成员重载（总结）

- 一元运算：`operator+(v)`（返回引用），`operator-(v)`（取负）。
- 二元运算（向量-向量）：`operator+`, `operator-`, `operator*`（分量乘）、`operator/`, `operator%` 等。运算类型基于 traits（`plus_operator_result` 等）选择返回类型。
- 标量与向量混合运算：支持 `scalar * vector`, `vector * scalar`, `vector / scalar`, `vector % scalar`。
- 复合赋值：`+=`, `-=`, `*=`, `/=`, `%=` 都有实现（就地更新）。
- 比较：`operator==`, `operator!=` 使用 `equal_to`（近似比较 via `flaw_comparer`）。
- 输出：`operator<<` 将所有数组元素按顺序输出为 `[ x y z w ]` 风格（模板化支持任意 ostream char traits）。
- Hash 支持：`yggr::math::hash_support::hash_value`（ADL）和 `std::hash` 的特化（当定义 `YGGR_HAS_CXX11_STD_HASH` 时）。
- ADL 导出：`std::abs`、`std::swap`、`boost::swap` 被导向到 `yggr::math` 中的实现，以利于查找。

## 序列化

- 类里声明了 `friend class yggr::serialization::access;` 并实现了 `serialize(Archive& ar, const u32 version)`：序列化的是 `boost::serialization::base_object<base_type, this_type>(*this)`（将底层数组作为 base 进行序列化）。

## 例子（最小）

```cpp
#include <yggr/math/vector3d_t.hpp>

using namespace yggr::math;

int main() {
    vector3d<float> a(1.0f, 2.0f, 3.0f);
    vector3d<float> b(2.0f, 0.0f, -1.0f);

    auto c = a + b;            // 分量相加
    float d = a.dot(b);        // 点积
    auto e = a.cross(b);       // 叉积
    auto nf = a.normalize();   // 归一化，返回浮点 vector3d
    float len = a.length();    // 长度

    a += b;                    // 就地更新

    std::cout << "a: " << a << " len=" << len << "\n";
    return 0;
}
```

## 注意事项与潜在坑

1. w 分量语义：
   - 默认构造时 `w` 被设为 `1`（表示齐次坐标）。但是在若干成员函数（如 `length()`, `sum()`，`dot()` 等）源码中存在对 `w` 的断言（`assert(cmp_type(w) == val_type());`）。这些断言表明实现期望 `w` 为某个特定值（源码中使用 `flaw_comparer` 做近似比较）。在使用前请检查具体断言行为与你的 `w` 设置是否匹配，避免断言失败。
2. 精度和类型：
   - `normalize()` 会返回浮点类型的向量（`upper_float<val_type>::type`），如果原始 `Val` 为整数类型，归一化返回浮点向量。
   - 运算结果类型通过一组 traits（如 `plus_operator_result`、`multiplies_operator_result` 等）决定，混合不同数值类型时请注意结果的类型转换规则。
3. 零长度向量归一化：
   - `prv_normalize()` 在长度平方为 0 时直接返回（不会修改向量），调用方需自行处理零向量的语义。
4. 近似比较：
   - 相等比较使用 `flaw_comparer`（一个近似比较器），因此对浮点数的相等比较是近似的而非逐位精确比较。
5. 线程安全：
   - 该类没有内部同步；只在单线程或外部同步下安全使用。

## 建议的测试用例

- 构造/拷贝/移动：默认构造、三/四元构造、`base_type` 的移动/拷贝构造。
- 算术运算：标量与向量混合、不同 `Val` 类型混合运算。
- 归一化/长度：标准向量、零向量、极大或极小值。
- 叉积：已知向量的叉积结果（例如单位基向量之间的叉积）。
- 相等性与哈希：近似相等的浮点向量是否被认为相等以及哈希一致性。
- 序列化：`serialize` 与反序列化正确恢复 `base_type` 内容（包括 w）。

