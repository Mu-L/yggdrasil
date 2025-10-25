# revert_to_vector.hpp

文件路径: `yggr/mplex/revert_to_vector.hpp`

## 概述

此头文件提供了一个编译期元编程工具 `yggr::mplex::revert_to_vector<T>`，用于将任意 Boost.MPL 风格的类型序列（或可通过索引访问的类型序列）转换为一个 `boost::mpl::vector<...>`。

主要用途是把任意 MPL 序列（长度已知并且能通过 `boost::mpl::at_c<T, I>::type` 取得元素）“展开”成具体的 `boost::mpl::vector`，从而在需要 `mpl::vector` 的上下文中使用这些类型序列（例如作为模板参数包或在只能接受 `mpl::vector` 的旧代码中复用新型序列）。

该实现对两类环境提供了不同分支：
- 在支持 C++11 可变参数模板与整数序列（`index_sequence` / `make_index_sequence`）时，使用 `index_sequence` 展开元素。
- 在不支持可变参数模板（旧编译器）时，使用 Boost.Preprocessor 生成一组 `detail_revert_to_vector<T, N>` 的特化实现。

## 头文件依赖

- `yggr/base/yggrdef.h`（项目定义）
- 在有 C++11 可变模板支持时：`yggr/type_traits/integer_sequence.hpp`（定义 `index_sequence` / `make_index_sequence`）
- 在无可变模板支持时：`yggr/ppex/typedef.hpp`（宏 / 模板参数长度宏）
- Boost.MPL：`boost::mpl::vector.hpp`、`boost::mpl::size.hpp`、`boost::mpl/at.hpp`

## 提供的类型/接口

- 模板结构体 `yggr::mplex::revert_to_vector<T>`
  - 功能：继承自 `detail::detail_revert_to_vector<T, N>`，其中 `N` 为 `boost::mpl::size<T>::value`。
  - `::type`（隐含）：作为 MPL 容器，等价于 `boost::mpl::vector< typename boost::mpl::at_c<T, 0>::type, ..., typename boost::mpl::at_c<T, N-1>::type >`（若 `N == 0`，则为 `boost::mpl::vector<>`）。

内部实现（重要符号）：

- `namespace yggr::mplex::detail` 中：
  - `template<typename T, std::size_t N> struct detail_revert_to_vector;`（主模板声明）
  - 当支持 C++11 时：
    - `revert_to_vector_conv<T, index_sequence<I...>>` 继承自 `boost::mpl::vector< typename boost::mpl::at_c<T,I>::type... >`。
    - `detail_revert_to_vector<T, N>` 通过 `make_index_sequence<N>` 调用上述模板。 
  - 当不支持 C++11 时：
    - 使用预处理器（`BOOST_PP_LOCAL_ITERATE`）生成 `detail_revert_to_vector<T, 1> ... detail_revert_to_vector<T, MAX>` 的特化，特化体继承自 `boost::mpl::vector< typename boost::mpl::at_c<T,0>::type, ... >`。
  - 特化：`detail_revert_to_vector<T, 0>` 继承自 `boost::mpl::vector<>`。

## 使用示例

假设有一个 MPL 序列 `SomeSeq`，且序列满足 `boost::mpl::at_c<SomeSeq, I>::type` 可用并且 `boost::mpl::size<SomeSeq>::value == N`，可这样使用：

```cpp
using vec = yggr::mplex::revert_to_vector<SomeSeq>::type;
// vec is a boost::mpl::vector< ... > containing the elements of SomeSeq in order
```

简单示例：

```cpp
#include <boost/mpl/vector.hpp>
#include <yggr/mplex/revert_to_vector.hpp>

using seq = boost::mpl::vector<int, char, double>;
using vec = yggr::mplex::revert_to_vector<seq>::type; // 等价于 boost::mpl::vector<int, char, double>
```

在不直接使用 `boost::mpl::vector` 的自定义序列上也能工作，只要 `boost::mpl::size<T>::value` 与 `boost::mpl::at_c<T,I>::type` 可用。

## 实现细节与注意事项

1. 索引访问契约
   - `revert_to_vector` 依赖 `boost::mpl::size<T>::value` 返回序列长度 N，并且对每个 `0 <= I < N` 必须能通过 `boost::mpl::at_c<T, I>::type` 访问到元素类型。
   - 如果某个序列不满足这些契约（例如不是 Random-Access 风格的 MPL 序列），编译时会报错。

2. C++11 与非 C++11 分支
   - 支持 C++11 时，代码更简洁，使用 `index_sequence`/`make_index_sequence` 做参数包展开。
   - 不支持时，使用预处理器生成固定上限长度的特化（由 `YGGR_PP_TEMPLATE_PARAMS_LEN()` 或相似宏控制）。因此在非 C++11 分支下，能处理的最大序列长度受项目宏设置限制。

3. 空序列
   - 已提供 `detail_revert_to_vector<T, 0>` 对应 `boost::mpl::vector<>`。

4. 复杂度与编译负担
   - 本质上只是类型展开，编译器需要实例化 N 个 `boost::mpl::at_c`，对非常长的序列（>几十或上百）可能导致编译速度变慢或模板深度问题（取决于编译器）。

## 建议的测试 / 验证用例

- 基本功能
  - `boost::mpl::vector<>` --> `revert_to_vector` 结果应为 `boost::mpl::vector<>`。
  - `boost::mpl::vector<int>`、`boost::mpl::vector<int,char,...>` 等常规序列测试。

- 兼容性
  - 在 C++11（有 `make_index_sequence`）与非 C++11 模式下分别测试，以确保预处理器分支生成足够的特化数量。

- 错误情况
  - 对非随机访问的 MPL 序列（如果存在）尝试使用，确认编译错误是明确的。

示例静态断言（伪代码）：

```cpp
static_assert(boost::is_same<yggr::mplex::revert_to_vector<boost::mpl::vector<int>>::type,
                              boost::mpl::vector<int>>::value, "convert failed");
```

## 可改进点与扩展

- 自动适配其他 MPL 容器：目前实现假定 `boost::mpl::at_c` 与 `boost::mpl::size` 可用。如果需要支持更通用的序列概念，可考虑引入一个 traits 层，优先使用 `mpl::at_c`，若不可用尝试其他访问方式（例如 `mpl::at<...>` 配合 integral_c 索引）。

- 非 C++11 分支的上限问题：预处理器特化数量依赖项目宏（如 `YGGR_PP_TEMPLATE_PARAMS_LEN()`）。若目标是支持很长的序列，可增大该宏或提供一个配置检查（static_assert / 编译期告警）提示用户当前限制。

- 文档示例：建议在仓库中添加一个小的单元测试文件（例如 `test/revert_to_vector_test.cpp`），包含数个 `static_assert` 来保证在不同编译器与编译选项下行为一致。

## 结论

`revert_to_vector` 是一个简单而实用的元编程适配工具，主要用于把任意可通过 `at_c` 索引访问的 MPL 序列转为 `boost::mpl::vector<>`。实现同时兼顾现代 C++（variadic）和旧编译器（预处理器展开），在使用时注意序列索引契约和非 C++11 分支的最大支持长度即可。


---

文档生成器: 自动生成（根据 `revert_to_vector.hpp` 源码分析）

