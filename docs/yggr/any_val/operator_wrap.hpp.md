---
# 文件：operator_wrap.hpp

## 简介

operator_wrap.hpp 是 yggdrasil 项目中用于封装各种基础操作符的工具头文件。该文件通过 `yggr::any_val::operator_wrap` 结构体，提供了丰富的静态模板方法，统一封装了常见的算术、逻辑、位运算、赋值、自增自减等操作符的实现，便于在泛型编程和 `any` 类型操作符管理器中复用和扩展。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改、分发和商业用途，但需保留原作者版权声明和许可信息。

 <!-- ## 作者 -->

 <!-- - xu yang -->

## 主要内容

- 头文件保护宏，防止重复包含。
- 包含类型特征、元编程、数学运算、指针工具等相关依赖。
- 定义了 `yggr::any_val::operator_wrap` 结构体，封装了大量静态模板操作符方法。

## 主要结构体

### yggr::any_val::operator_wrap

#### 功能

- 封装了常见的操作符，包括：
  - 一元操作符：正号、负号、取反、逻辑非、解引用、取地址、自增自减等
  - 二元操作符：加、减、乘、除、模、位与、位或、位异或、左移、右移、比较等
  - 赋值操作符：=、+=、-=、*=、/=、%=、&=、|=、^=、<<=、>>=
  - 逻辑操作符：&&、||、!
  - 支持自定义返回类型的 custom 版本，便于特殊场景下的类型适配
- 支持指针类型的安全解引用和只读解引用
- 支持 move 语义的赋值

#### 典型方法

- `static L& self(L& l);`
- `static typename positive_operator_result<L>::type positive(const L& l);`
- `static typename negate_operator_result<L>::type negate(const L& l);`
- `static typename mplex::pointer_to_reference_t<L>::type dereference(L& l);`
- `static typename boost::add_pointer<L>::type addressof(L& l);`
- `static L& head_increment(L& l);`
- `static L tail_increment(L& l);`
- `static L& set(L& l, const R& r);`
- `static L& set_move(L& l, R& r);`
- `static typename plus_operator_result<L, R>::type plus(const L& l, const R& r);`
- `static bool equal_to(const L& l, const R& r);`
- `static bool less(const L& l, const R& r);`
- 以及所有常见的算术、逻辑、位运算和比较操作符

#### 自定义返回类型方法

- 提供 `*_custom` 方法，允许指定返回类型，便于特殊类型或包装类型的操作。

## 用法示例

```cpp
#include <yggr/any_val/operator_wrap.hpp>

int a = 5, b = 3;
int sum = yggr::any_val::operator_wrap::plus(a, b); // sum == 8

bool eq = yggr::any_val::operator_wrap::equal_to(a, b); // eq == false

int* p = &a;
int v = yggr::any_val::operator_wrap::dereference(p); // v == 5
```

## 适用场景

- 泛型编程中需要统一操作符调用接口时
- `any` 类型操作符管理器的底层实现
- 需要自定义返回类型或特殊类型操作时

## 依赖

- yggrdef.h
- move.hpp
- modulus.hpp
- operator_result.hpp
- native_t.hpp
- pointer_to_reference_t.hpp
- Boost.TypeTraits

---

如需详细功能和实现细节，请参考本文件实现及相关依赖头文件。

