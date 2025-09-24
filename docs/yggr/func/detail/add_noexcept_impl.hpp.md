---
add_noexcept_impl.hpp 文档

---

# 文件：add_noexcept_impl.hpp

## 简介
该头文件为 yggdrasil 项目中 `add_noexcept` 工具的实现细节，主要用于为函数类型添加 `noexcept` 属性。根据不同的编译环境和依赖，选择使用 Boost 的实现或自定义实现。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- Boost 1.66.0 及以上版本时，依赖 add_noexcept.hpp
- 低版本或无 Boost 时，依赖 traits.hpp

### 预处理条件
- 检查 Boost 版本、C++ 标准版本和 `noexcept` 支持情况，自动选择实现方式。
- 若条件满足，直接继承自 `boost::callable_traits::add_noexcept<T>`。
- 否则，使用自定义模板和宏实现。

### 主要结构体
```cpp
template<typename T>
struct add_noexcept_impl : public boost::callable_traits::add_noexcept<T> {};
```
或
```cpp
template<typename T>
struct add_noexcept_impl : public yggr::traits<T> {};
```

### 宏定义与特化
- 通过宏 `YGGR_PP_MAKE_ADD_NOEXCEPT_IMPL_F` 和 `YGGR_PP_MAKE_ADD_NOEXCEPT_IMPL_MF`，为不同调用约定（如 `__cdecl`、`__stdcall`、`__fastcall`）和成员函数类型生成带 `noexcept` 的特化版本。
- 支持变参函数、成员函数、const/volatile 限定等多种情况。

### 用法说明
- 该实现为 `yggr::func::add_noexcept<T>` 提供底层支持，自动为函数类型添加 `noexcept`。
- 适用于需要类型萃取和元编程的场景，兼容多种编译环境。

---



