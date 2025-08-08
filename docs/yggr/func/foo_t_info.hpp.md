# foo_t_info.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 头文件包含
- 引入了 Yggdrasil 框架的基础定义、类型萃取、类型特征、元编程工具等。
- 支持 Boost.TypeTraits、Boost.FunctionTypes、Boost.Function、Boost.Bind 等库。
- 包含大量 MPL 元编程相关头文件。

## 3. 命名空间结构
- 所有内容均在 `yggr::func` 命名空间下，部分细节实现位于 `yggr::func::detail`。

## 4. 主要功能与类型

### 4.1 tag_va_list 与 tag_object_reference
- `tag_va_list`：用于标记变参类型。
- `tag_object_reference<T>`：用于标记对象引用类型，提供指针和引用类型别名。
- `is_tag_object_reference<T>`：用于判断类型是否为 `tag_object_reference`。

### 4.2 类型萃取工具
- `tag_object_reference_to_pointer<T>`：如果是 `tag_object_reference`，萃取其指针类型，否则为 null_type。
- `tag_object_reference_to_reference<T>`：如果是 `tag_object_reference`，萃取其引用类型，否则为 null_type。

### 4.3 Boost.Bind 参数相关工具
- `is_boost_arg<T>`：判断类型是否为 `boost::arg<N>`。
- `boost_arg_N<T>`：获取 `boost::arg<N>` 的 N 值。
- `boost_arg_less<L, R>`：用于参数排序。
- `conv_to_arg`：用于将参数持有者类型映射到实际参数类型。

### 4.4 可调用对象类型信息萃取
- `non_foo_t_info<T>`：非可调用对象的默认实现，所有特征均为 false/null_type。
- `native_foo_t_info<T>`：原生函数类型的特征萃取，包括返回值、参数列表、是否 const/volatile/noexcept 等。
- `native_member_foo_t_info<T>`：原生成员函数指针类型的特征萃取。
- `callable_foo_t_info<T>`：可调用对象（如重载 operator() 的类/仿函数）的特征萃取。
- `functional_foo_t_info<T>`：兼容 std::unary_function、std::binary_function 的特征萃取（C++17 前）。
- `foo_t_info_detail<T>`：主萃取实现，自动分派到上述不同实现。
- 针对 Boost.Function、Boost.Bind、Boost.Bind MF 及其变体，使用宏和特化进行支持。

### 4.5 foo_t_info<T>
- 对外主接口，封装了 `foo_t_info_detail<T>`，提供如下类型和静态常量：
  - 类型特征：is_callable、is_native_foo、is_member_foo、has_va_list、is_const、is_volatile、is_noexcept
  - 类型信息：result_type、class_type、arg_list_type、arg_holder_list_type、foo_type、foo_pointer_type、foo_reference_type、native_foo_type 等
  - 参数个数：arg_list_size、arg_holder_list_size
  - 参数类型访问：arg<N>、arg_holder<N>

### 4.6 输出运算符重载
- 重载了 `operator<<`，可将 `foo_t_info<T>` 的类型信息输出到流，便于调试和类型分析。

---

## 5. 主要用途

- **类型萃取**：统一获取各种可调用对象的返回值类型、参数类型、参数个数、是否为成员函数、是否为 const/noexcept 等特征。
- **模板元编程**：为泛型编程和类型安全调用提供基础。
- **Boost 兼容**：支持 Boost.Function、Boost.Bind 及其成员函数适配器。
- **调试与分析**：通过流输出接口，方便输出类型信息。

---

## 6. 典型用法

```cpp
using namespace yggr::func;

// 获取函数指针类型信息
typedef void(*foo_ptr)(int, double);
foo_t_info<foo_ptr> info;

// 获取成员函数指针类型信息
struct Bar { int func(float) const; };
foo_t_info<decltype(&Bar::func)> info2;

// 获取仿函数类型信息
struct Functor { void operator()(int) const; };
foo_t_info<Functor> info3;

// 输出类型信息
std::cout << info;
```

---

## 7. 总结

本文件为 Yggdrasil 框架提供了强大的可调用对象类型分析和萃取能力，支持 C++ 标准和 Boost 生态下的各种函数、成员函数、仿函数、绑定对象等，极大方便了泛型编程和类型安全调用的实现。

