# operator_result.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了一套类型萃取工具，用于推导一元和二元运算符（如 +、-、*、/、%、&、|、^、~、<<、>> 等）在不同类型上的结果类型。其实现方式兼容 C++98/03/11，通过宏和 `typeof` 技术实现类型自动推导，适用于泛型编程、模板元编程、类型安全运算等场景。

## 3. 主要内容与实现

### 3.1 operator_result_t_getter
- 模板结构体，继承自 `traits<T>`，用于类型萃取和 declval 支持。
- 提供隐式类型转换运算符，便于在 `typeof` 表达式中模拟类型实例。

### 3.2 宏定义
- `YGGR_PP_TYPE_TRAITS_BINARY_OPERATOR_RESULT`  
  自动生成二元运算符结果类型萃取结构体，如 `plus_operator_result<L, R>::type` 表示 `L + R` 的结果类型。
- `YGGR_PP_TYPE_TRAITS_BEFORE_UNARY_OPERATOR_RESULT`  
  自动生成一元前置运算符结果类型萃取结构体，如 `negate_operator_result<T>::type` 表示 `-T` 的结果类型。
- `YGGR_PP_TYPE_TRAITS_AFTER_UNARY_OPERATOR_RESULT`  
  自动生成一元后置运算符结果类型萃取结构体（本文件未直接用到）。

### 3.3 具体运算符支持
- **数学运算符**  
  - 正号：`positive_operator_result<T>::type`（+a）
  - 负号：`negate_operator_result<T>::type`（-a）
  - 加法：`plus_operator_result<L, R>::type`（a + b）
  - 减法：`minus_operator_result<L, R>::type`（a - b）
  - 乘法：`multiplies_operator_result<L, R>::type`（a * b）
  - 除法：`divides_operator_result<L, R>::type`（a / b）
  - 取模：`modulus_operator_result<L, R>::type`（a % b）

- **位运算符**  
  - 按位与：`bitwise_and_operator_result<L, R>::type`（a & b）
  - 按位或：`bitwise_or_operator_result<L, R>::type`（a | b）
  - 按位异或：`bitwise_xor_operator_result<L, R>::type`（a ^ b）
  - 左移：`bitwise_left_shift_operator_result<L, R>::type`（a << b）
  - 右移：`bitwise_right_shift_operator_result<L, R>::type`（a >> b）
  - 按位取反：`bitwise_not_operator_result<T>::type`（~a）

### 3.4 兼容性与警告处理
- 针对 MSVC 编译器，关闭了部分无关警告（如 4804、4805）。
- 采用 Boost.Preprocessor 进行宏拼接和参数展开，兼容多种 C++ 标准。

## 4. 典型用法

```cpp
#include <yggr/type_traits/operator_result.hpp>
#include <type_traits>

typedef yggr::plus_operator_result<int, double>::type result_type; // result_type = double

static_assert(std::is_same<result_type, double>::value, "Type deduction failed");

typedef yggr::bitwise_and_operator_result<unsigned, char>::type bit_type; // bit_type = unsigned
```

## 5. 注意事项

- 依赖 `typeof` 技术（如 Boost.Typeof 或 C++11 decltype），需确保相关宏和头文件已正确配置。
- 仅用于类型推导，不会实际执行运算。
- 对于自定义类型，需保证相关运算符已正确定义。

## 6. 总结

本文件为 Yggdrasil 框架提供了强大的运算符结果类型推导工具，适用于泛型算法、模板元编程、类型安全运算等场景。通过宏和类型萃取机制，用户可方便地获取任意类型组合下各种运算符的结果类型，提升代码的通用性和安全性。

---

