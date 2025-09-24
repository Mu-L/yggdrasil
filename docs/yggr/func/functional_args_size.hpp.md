---
functional_args_size.hpp 文档

---

# 文件：functional_args_size.hpp

## 简介
该头文件为 yggdrasil 项目中函数对象参数数量萃取工具，主要用于在编译期判断类型 T 是否为一元或二元函数对象，并据此获得其参数个数（1、2 或 0）。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- is_functional.hpp
- Boost MPL 相关头文件（`mpl/size_t.hpp`、`mpl/if_.hpp`）

### 主要模板
#### 1. `functional_args_size<T>`
- 用于判断类型 T 的参数个数。
- 若 T 继承自 `std::unary_function`，则值为 1。
- 若 T 继承自 `std::binary_function`，则值为 2。
- 否则，值为 0。

### 用法说明
- 该工具适用于泛型编程、类型萃取、函数对象适配等场景，可用于静态断言、类型选择等元编程需求。
- 通过 `functional_args_size<T>::type::value` 获取参数个数。

---



