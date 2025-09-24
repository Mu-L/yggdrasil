---
has_functional_member_t.hpp 文档

---

# 文件：has_functional_member_t.hpp

## 简介
该头文件为 yggdrasil 项目中函数对象成员类型萃取工具，主要用于在编译期检测类型 F 是否拥有标准函数对象成员类型（如 `argument_type`、`first_argument_type`、`second_argument_type`、`result_type`），便于泛型编程和类型适配。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。

## 主要内容

### 头文件依赖
- yggrdef.h
- native_t.hpp
- Boost MPL 相关头文件
- `<functional>`

### 主要模板
#### 1. `has_argument_t<F>`
- 检查类型 F 是否拥有 `argument_type` 成员类型。

#### 2. `has_first_argument_t<F>`
- 检查类型 F 是否拥有 `first_argument_type` 成员类型。

#### 3. `has_second_argument_t<F>`
- 检查类型 F 是否拥有 `second_argument_type` 成员类型。

#### 4. `has_result_t<F>`
- 检查类型 F 是否拥有 `result_type` 成员类型。

### 实现原理
- 采用 SFINAE 技术，通过重载和 `sizeof` 判断成员类型是否存在，返回 `boost::mpl::bool_<true/false>`。
- 内部使用 `native_t` 处理引用类型，保证类型检测的兼容性。

### 用法说明
- 该工具适用于泛型编程、类型萃取、接口适配等场景，可用于静态断言、类型选择等元编程需求。
- 通过 `has_argument_t<F>::value` 等方式获取检测结果。

---



