---
is_noexcept.hpp 文档

---

# 文件：is_noexcept.hpp

## 简介
该头文件为 yggdrasil 项目中 noexcept 类型检测工具的统一入口，主要用于在编译期判断类型 T 是否为带有 `noexcept` 的函数类型，便于类型萃取和泛型编程。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- is_noexcept_impl.hpp

### 主要模板
#### 1. `is_noexcept<T>`
- 用于判断类型 T 是否为 `noexcept` 函数类型。
- 继承自 `detail::is_noexcept_impl<T>::type`，根据实现细节自动适配不同编译环境和类型特性。

### 用法说明
- 该工具适用于类型萃取、SFINAE、静态断言等元编程场景。
- 通过 `is_noexcept<T>::value` 获取检测结果。

---



