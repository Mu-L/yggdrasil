---
remove_noexcept.hpp 文档

---

# 文件：remove_noexcept.hpp

## 简介
该头文件为 yggdrasil 项目中 noexcept 属性移除工具的统一入口，主要用于在编译期移除类型 T 的 `noexcept` 属性，便于类型转换和泛型编程。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- remove_noexcept_impl.hpp

### 主要模板
#### 1. `remove_noexcept<T>`
- 用于移除类型 T 的 `noexcept` 属性。
- 继承自 `detail::remove_noexcept_impl<T>`，根据实现细节自动适配不同编译环境和类型特性。

### 用法说明
- 该工具适用于类型萃取、类型转换、泛型编程等场景。
- 通过 `remove_noexcept<T>::type` 获取去除 `noexcept` 后的类型。

---

