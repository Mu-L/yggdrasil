---
add_noexcept.hpp 文档

---

# 文件：add_noexcept.hpp

## 简介
该头文件定义了模板结构体 `add_noexcept`，用于为类型 T 添加 `noexcept` 属性。其实现细节委托给 `detail::add_noexcept_impl<T>`，属于 yggdrasil 项目中的函数工具组件。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- add_noexcept_impl.hpp

### 命名空间
- `yggr::func`

### 主要结构体
```cpp
template<typename T>
struct add_noexcept : public detail::add_noexcept_impl<T> {};
```
- 作用：为类型 T 添加 `noexcept`，具体实现由 `add_noexcept_impl` 提供。

### 用法示例
假设 `add_noexcept_impl` 针对函数类型进行了特化，可以通过 `add_noexcept<SomeFuncType>::type` 获得带有 `noexcept` 的函数类型。

---

