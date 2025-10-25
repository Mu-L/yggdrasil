# 文件：cast_to_t_container.hpp 文档

路径：`yggr/mplex/cast_to_t_container.hpp`

## 概要
`cast_to_t_container.hpp`（文件头注释处名为 `bind_list_to_vector.hpp`，但实际包含 `cast_to_*` 模板）提供了一组元编程适配器，用于将任意模板容器类型映射或“转换”为对应的 Boost.MPL 容器类型（如 `boost::mpl::vector`, `boost::mpl::list`, `boost::mpl::deque`, `boost::mpl::set` 等）。

主要用途：在元编程代码中需要把外部或 STL 风格的模板容器（例如 `std::vector<int>`、`std::list<Ts...>` 或自定义模板 `OtherCont<Ts...>`）转换为 Boost.MPL 的序列，以便使用 Boost.MPL 提供的元编程算法与工具链。

文件同时考虑了两种编译器能力：
- 如果支持 C++11 的可变模板参数（variadic templates），则通过一个简洁的模板偏特化映射任意参数包 `T...`。
- 在不支持可变模板参数的旧编译器下，使用一系列 Boost.Preprocessor 宏和本项目的预处理宏（例如 `YGGR_PP_TEMPLATE_PARAMS_TYPES`、`YGGR_PP_TEMPLATE_PARAMS_LEN` 等）生成固定参数数量的特化以覆盖常见的参数数目。


## 依赖
- `yggr/base/yggrdef.h`（项目基础定义）
- `yggr/ppex/typedef.hpp`（项目的预处理辅助宏定义）
- Boost.MPL 容器头：`boost/mpl/vector.hpp`、`boost/mpl/list.hpp`、`boost/mpl/deque.hpp`、`boost/mpl/set.hpp`、`boost/mpl/map.hpp`（map 头被包含，但源文件未显式提供 `cast_to_map` 的实现——可能为占位或未来扩展）
- （若编译器无 variadic support）Boost.Preprocessor 相关（通过 `BOOST_PP_LOCAL_ITERATE` 等宏自动扩展）


## 命名空间
定义在 `yggr::mplex` 命名空间中。


## 提供的适配器（API）

模板形式（基础单类型版本）：

- template<typename T = void> struct cast_to_vector : public boost::mpl::vector<T> {};
- template<> struct cast_to_vector<void> : public boost::mpl::vector<> {};

- template<typename T = void> struct cast_to_list : public boost::mpl::list<T> {};
- template<> struct cast_to_list<void> : public boost::mpl::list<> {};

- template<typename T = void> struct cast_to_deque : public boost::mpl::deque<T> {};
- template<> struct cast_to_deque<void> : public boost::mpl::deque<> {};

- template<typename T = void> struct cast_to_set : public boost::mpl::set<T> {};
- template<> struct cast_to_set<void> : public boost::mpl::set<> {};

这些模板为单一类型或空模板参数提供了直接的 MPL 容器类型（方便把单一类型包装为 MPL 序列）。

当支持 C++11 可变模板参数时，文件还定义了偏特化以映射任意模板模板类：

- 当 `Other_Cont<T...>` 为一个模板类实例时：
  - `cast_to_vector< Other_Cont<T...> >` 继承 `boost::mpl::vector<T...>`。
  - `cast_to_list< Other_Cont<T...> >` 继承 `boost::mpl::list<T...>`。
  - `cast_to_deque< Other_Cont<T...> >` 继承 `boost::mpl::deque<T...>`。
  - `cast_to_set< Other_Cont<T...> >` 继承 `boost::mpl::set<T...>`。

在不支持 variadic templates 时，文件使用预处理循环（通过 `BOOST_PP_LOCAL_ITERATE`）生成固定参数数量（由 `YGGR_PP_TEMPLATE_PARAMS_LEN()` 限定）的偏特化，原则与上面相同：把 `Other_Cont<T1, T2, ...>` 映射到对应的 `boost::mpl::...<T1, T2, ...>`。


## 使用示例

下面示例展示如何把一个普通 STL 容器模板实例（或自定义模板实例）转换为 Boost.MPL 序列：

```cpp
#include <vector>
#include <list>
#include <boost/mpl/size.hpp>
#include <yggr/mplex/cast_to_t_container.hpp>

// 假设有 std::vector<int>
using mv = yggr::mplex::cast_to_vector<std::vector<int>>;
// mv 继承自 boost::mpl::vector<int>
static_assert(boost::mpl::size<mv>::value == 1, "size should be 1");

// 对于模板参数包：例如 std::tuple<int, double, char>
// 若支持 variadic 模板，能直接映射到 boost::mpl::vector<int, double, char>
using mt = yggr::mplex::cast_to_vector<std::tuple<int, double, char>>;
static_assert(boost::mpl::size<mt>::value == 3, "tuple -> mpl::vector of 3 elements");

// 可用于 boost::mpl 中的其它元算法，例如 at_c, front, push_back 等
```

注意：在某些 MPL 操作中，直接将 `cast_to_vector<...>` 当作序列类型使用是可行的，因为该适配器通过继承直接等同于一个 `boost::mpl::vector<...>` 类型。


## 设计说明与意图
- 目标是让不同风格的模板容器（STL、用户自定义的模板容器）能被统一看作 Boost.MPL 序列，从而可以在元编程上下文中复用已有算法。
- 使用偏特化而非别名模板的设计，允许在不支持 C++11 的环境下仍然通过预处理生成必要的特化版本，兼顾兼容性。
- 采用 `boost::mpl::...` 系列容器而不是直接使用 `std::tuple` 等，以利用 Boost.MPL 丰富的元编程算法。


## 注意事项与边界情况
- 仅支持被识别为模板实例（形如 `Other_Cont<T...>`）的类型：
  - 对于非模板实例（例如非模板类的普通类型），只有 `cast_to_*<T>` 的基础版本（单一类型）可用（将 `T` 当作单元素类型处理）。
- `boost/mpl/map.hpp` 虽然被包含，但文件并未提供 `cast_to_map` 的适配特化，若需要 map 支持可按已有模式添加。
- 在不支持 variadic 模板的环境下，适配器覆盖的参数个数受 `YGGR_PP_TEMPLATE_PARAMS_LEN()` 限制（该宏通常在 `yggr/ppex/typedef.hpp` 或相关预处理头中定义）。超出该长度的模板参数数量将无法被映射。
- 适配器仅将模板参数“转移”到 Boost.MPL 容器中，不会对参数类型本身做任何转换或去除修饰，调用方需保证传入的参数类型是所需的类型。


## 兼容性和宏说明
- 宏 `YGGR_NO_CXX11_VARIADIC_TEMPLATES`：
  - 如果定义了该宏，代码会选择预处理器路径来生成多个参数数目的偏特化（兼容旧编译器）。
  - 否则，使用更简洁的 variadic template 偏特化。

- 预处理器辅助宏（如 `YGGR_PP_TEMPLATE_PARAMS_TYPES`、`YGGR_PP_TEMPLATE_PARAMS_LEN`、`YGGR_PP_CONTAINER_NAME` 等）在 `yggr/ppex/typedef.hpp` 或其他预处理头中定义，用于生成多个模板参数的代码。


## 测试建议
- 在支持可变模板参数（现代编译器）的环境下测试：
  - `cast_to_vector<std::vector<int>>` -> `boost::mpl::vector<int>`
  - `cast_to_list<std::tuple<int, short>>` -> `boost::mpl::list<int, short>`（如果映射到 tuple）
  - `cast_to_deque<MyCont<A,B,C>>` -> `boost::mpl::deque<A,B,C>`
- 在不支持 variadic 的旧环境下，确认预处理生成的特化能覆盖常见参数个数（1..N），并测试边界（参数数量为 N 和 N+1）。
- 若需要 `map` 支持，添加 `cast_to_map` 的实现并为典型用例写静态断言。
