# `vector3d.hpp` 文档

## 概述

`yggr/math/vector3d.hpp` 是对 `vector3d_t.hpp` 的补充：它引入了基于封装器（wrapper）类型的非成员 `operator*` 重载，用以支持更直观的点积（dot）和叉积（cross）表达式。

- 源文件：`yggr/math/vector3d.hpp`
- 依赖：`yggr/math/vector3d_t.hpp`、`yggr/math/operator_dot.hpp`、`yggr/math/operator_cross.hpp`

此文件没有定义新的数据结构，而是提供一组模板化的运算符重载，使得可以使用 `doter<...>` 和 `crosser<...>` 之类的包装器与 `vector3d` 进行 `*` 运算以获得点积或叉积。

## 在文件中定义的重载（摘要）

点积相关（使用 `doter<T>` 封装器）：

- operator*(const vector3d<ValL, BaseL>& l, const doter<vector3d<ValR, BaseR> >& r)
  - 实现：返回 `l.dot(r.get())`。

- operator*(const doter<vector3d<ValL, BaseL> >& l, const vector3d<ValR, BaseR>& r)
  - 实现：返回 `l.get().dot(r)`。

- operator*(const doter<vector3d<ValL, BaseL> >& l, const doter<vector3d<ValR, BaseR> >& r)
  - 实现：返回 `l.get().dot(r.get())`。

叉积相关（使用 `crosser<T>` 封装器）：

- operator*(const vector3d<ValL, BaseL>& l, const crosser<vector3d<ValR, BaseR> >& r)
  - 实现：返回 `l.cross(r.get())`。

- operator*(const crosser<vector3d<ValL, BaseL> >& l, const vector3d<ValR, BaseR>& r)
  - 实现：返回 `l.get().cross(r)`。

- operator*(const crosser<vector3d<ValL, BaseL> >& l, const crosser<vector3d<ValR, BaseR> >& r)
  - 实现：返回 `l.get().cross(r.get())`。

这些运算符模板同时使用了 `multiplies_operator_result` trait（见 `vector3d_t.hpp`）来决定返回值的数值类型，并在必要时选择合适的 `Base` 模板以匹配结果类型。

## 语义与用途

- 目的：提供便捷语法来写点积与叉积，而不用显式调用成员函数 `a.dot(b)` 或 `a.cross(b)`。例如可以让表达式类似于 `a * doter(b)` 或 `doter(a) * b` 等。
- 依赖 wrapper：这些重载依赖类型 `doter<T>` 与 `crosser<T>`（通常在 `operator_dot.hpp` 与 `operator_cross.hpp` 中定义）。`doter`/`crosser` 应当能包装目标向量并提供 `get()` 以访问被包装的向量。
- 返回类型：点积返回标量（由 `multiplies_operator_result<ValL, ValR>::type` 决定）；叉积返回 `vector3d`（结果元素类型由相同 trait 决定）。

## 示例（伪代码）

下面的示例展示了如何利用这些重载（假设 `doter` 与 `crosser` 的构造函数接受 `vector3d`）：

```cpp
#include <yggr/math/vector3d.hpp>
#include <yggr/math/operator_dot.hpp>
#include <yggr/math/operator_cross.hpp>

using namespace yggr::math;

int main() {
    vector3d<float> a(1.0f, 2.0f, 3.0f);
    vector3d<float> b(2.0f, 0.0f, -1.0f);

    // 假设 doter/vector_wrapper 的构造方式如下（具体请参见 operator_dot.hpp）
    doter< vector3d<float> > db(b);
    float dot1 = a * db;                // 调用 operator*(vector3d, doter) -> 返回 a.dot(b)

    float dot2 = doter<vector3d<float>>(a) * b; // 调用 operator*(doter, vector3d)

    float dot3 = doter<vector3d<float>>(a) * doter<vector3d<float>>(b); // doter * doter

    // cross
    crosser< vector3d<float> > cb(b);
    auto c = a * cb;                    // 调用 operator*(vector3d, crosser) -> 返回 a.cross(b)

    auto c2 = crosser<vector3d<float>>(a) * b; // crosser * vector3d

    return 0;
}
```

注意：上例中 `doter`/`crosser` 的具体构造函数或辅助函数（如可能存在的 `dot(b)` / `cross(b)` 快捷函数）需参考 `operator_dot.hpp` / `operator_cross.hpp` 的实现。

## 注意事项

- 引入头文件：要使用这些重载，必须包含 `operator_dot.hpp` 与 `operator_cross.hpp`，因为它们定义了 `doter`/`crosser` 类型。
- 不要与已有的 `operator*` 产生二义性：这些模板重载设计为在 `doter`/`crosser` 被显式使用时生效；避免在项目中出现其他与之冲突的 `operator*` 重载。
- 类型推断：返回类型遵循 `multiplies_operator_result` trait，混合不同数值类型时请留意精度与转换。
- 可读性：虽然 `a * doter(b)` 看起来简洁，但在团队协作中应统一约定是否采用这种语法，避免影响可读性。

## 关联文件

- `yggr/math/vector3d_t.hpp`：向量主体实现（成员函数、算术、序列化等）。
- `yggr/math/operator_dot.hpp`：应定义 `doter<T>`（及可能的辅助函数），用于点积包装器。
- `yggr/math/operator_cross.hpp`：应定义 `crosser<T>`（及可能的辅助函数），用于叉积包装器。

## 建议测试用例

- 验证 `a * doter(b)`、`doter(a) * b` 与 `doter(a) * doter(b)` 三种表达式与 `a.dot(b)` 的结果一致。
- 验证 `a * crosser(b)`、`crosser(a) * b` 与 `crosser(a) * crosser(b)` 三种表达式与 `a.cross(b)` 的结果一致。
- 测试不同元素类型混合（例如 `vector3d<int>` 与 `vector3d<double>`）时返回值类型与精度是否符合预期。

## 结语

`vector3d.hpp` 是一个轻量的适配层，目的是把点/叉积的成员函数调用以更灵活的运算符表达式暴露给用户。