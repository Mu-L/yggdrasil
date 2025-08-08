# tuple.hpp 文档

## 1. 版权声明
MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了跨平台、兼容 Boost 和标准库的 tuple 支持。通过条件编译，自动适配 Boost.Tuple 或 std::tuple，并扩展了统一的 get、tuple_size、tuple_element、is_tuple_cons 等工具，便于泛型编程和元组操作。

## 3. 主要内容与功能

### 3.1 兼容性适配
- 根据编译器特性自动选择 Boost.Tuple 或 std::tuple 实现。
- 支持 MSVC、GCC、Clang 等主流编译器，兼容 C++98/03/11/14/17/20。

### 3.2 get 函数扩展
- 为 std::tuple、Boost.Tuple、yggr::tuples::cons 提供统一的 get 接口，支持下标和类型索引。
- 支持通过整数模板参数或类型模板参数（如 mpl::int_）访问元组元素。
- 兼容 const/非 const、引用/非引用等多种访问方式。
- 通过 YGGR_INDEX_T_VALUE_GET 宏支持类型索引到整数索引的自动转换。

### 3.3 元组类型萃取与工具
- **tuple_size**：获取元组长度，兼容 std::tuple、Boost.Tuple、yggr::tuples::cons。
- **tuple_element**：获取指定下标的元素类型，兼容 std::tuple、Boost.Tuple、yggr::tuples::cons。
- **is_tuple_cons**：判断类型是否为 cons 结构（Boost.Tuple/yggr::tuples 的 cons）。
- **length**：Boost.Tuple/yggr::tuples 的长度萃取，兼容 std::tuple。

### 3.4 元组构造与绑定
- 导出 `tuple`、`make_tuple`、`tie` 到 yggr 命名空间，便于统一使用。

### 3.5 兼容性细节
- 针对部分编译器（如 MSVC、Borland）做了特殊处理，保证模板特化和 using 声明的兼容性。
- 支持 workaround_holder、element_ref 等底层实现细节，保证 get 的高效与类型安全。

---

## 4. 典型用法

```cpp
#include <yggr/tuple/tuple.hpp>

// 构造元组
auto t = yggr::make_tuple(1, 3.14, std::string("hello"));

// 访问元素
int a = yggr::get<0>(t);
double b = yggr::get<1>(t);

// 支持类型索引访问
typedef boost::mpl::int_<2> idx_type;
std::string s = yggr::get<idx_type>(t);

// 获取元组长度和元素类型
size_t sz = yggr::tuple_size<decltype(t)>::value;
typedef yggr::tuple_element<1, decltype(t)>::type elem_type;
```

---

## 5. 设计要点

- **统一接口**：无论底层是 Boost.Tuple 还是 std::tuple，均可用 yggr::get、yggr::tuple_size、yggr::tuple_element 等统一接口访问。
- **类型安全**：所有 get、tuple_size、tuple_element 等均通过类型萃取和模板元编程保证类型安全。
- **泛型友好**：支持整数索引、类型索引、const/非 const、引用/非引用等多种访问方式，适合泛型编程。
- **高兼容性**：自动适配不同编译器和标准，兼容 Boost 和标准库实现。

---

## 6. 注意事项

- 若使用类型索引（如 mpl::int_），需确保 YGGR_INDEX_T_VALUE_GET 能正确获取整数值。
- get 的实现依赖于底层 tuple 实现，部分特殊用法需参考 Boost 或 std 文档。
- 兼容性宏和条件编译较多，建议不要手动修改底层实现。

---

## 7. 总结

本文件为 Yggdrasil 框架提供了功能强大、接口统一、类型安全的 tuple 支持，兼容 Boost.Tuple 和 std::tuple，适合泛型编程、元组操作、类型萃取等多种高级 C++ 场景。其设计兼顾性能、易用性和扩展性，是大型 C++ 工程中元组操作的理想选择。

---

