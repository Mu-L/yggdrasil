---
is_noexcept_impl.hpp 文档

---

# 文件：is_noexcept_impl.hpp

## 简介
该头文件为 yggdrasil 项目中 `is_noexcept` 类型萃取工具的实现细节，主要用于判断某个函数类型是否带有 `noexcept` 属性。根据不同的编译环境和依赖，选择使用 Boost 的实现或自定义实现。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- Boost 1.66.0 及以上版本时，依赖 `boost/callable_traits/is_noexcept.hpp`
- 低版本或无 Boost 时，使用自定义模板和宏实现
- `boost/mpl/bool.hpp`

### 主要结构体
#### 1. `is_noexcept_impl`
- 用于判断类型 T 是否为 `noexcept` 函数类型。
- 若环境支持，直接继承自 `boost::callable_traits::is_noexcept<T>` 的结果。
- 否则，默认返回 `false_`，并通过宏为各种 `noexcept` 函数类型特化为 `true_`。

#### 2. 宏特化
- 通过宏 `YGGR_PP_MAKE_IS_NOEXCEPT_IMPL_F` 和 `YGGR_PP_MAKE_IS_NOEXCEPT_IMPL_MF`，为不同调用约定（如 `__cdecl`、`__stdcall`、`__fastcall`）和成员函数类型生成带 `noexcept` 的特化版本。
- 支持变参函数、成员函数、const/volatile 修饰等多种情况。

### 用法说明
- 该实现为 `yggr::func::is_noexcept<T>` 提供底层支持，可用于类型萃取、SFINAE、静态断言等元编程场景。
- 兼容多种编译环境和函数类型。

---



