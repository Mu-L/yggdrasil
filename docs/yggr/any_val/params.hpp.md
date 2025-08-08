---
# 文件：params.hpp

## 简介

params.hpp 是 yggdrasil 项目中用于实现通用参数集合容器的头文件。该容器以键值对形式存储任意类型的参数值（基于 `any`），并支持通过操作符管理器进行批量算术、逻辑、位运算等操作。它适用于需要动态参数管理、批量运算和类型安全访问的复杂场景。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改、分发和商业用途，但需保留原作者版权声明和许可信息。

 <!-- ## 作者 -->

 <!-- - xu yang -->

## 主要内容

- 头文件保护宏，防止重复包含。
- 包含类型定义、异常处理、序列化、容器、操作符管理等相关依赖。
- 定义了模板类 `yggr::any_val::params`，支持自定义键类型、操作符管理器、比较器、分配器和底层映射容器类型。
- 提供了丰富的成员函数和操作符重载，支持参数的增删查改、批量运算、序列化、类型安全访问等功能。
- 支持与标准库和 Boost 的 `swap` 机制集成。

## 主要模板类

### yggr::any_val::params

#### 模板参数

- `Key`：参数键类型。
- `Op_Mgr`：操作符管理器类型，默认为 `any_operator_mgr<>`。
- `Cmp`：键比较器类型，默认为底层 map 的比较器。
- `Alloc`：分配器类型，默认为底层 map 的分配器。
- `Map`：底层映射容器模板，默认为 `yggr::container::map`。

#### 主要成员类型

- `base_type`：底层 map 类型。
- `key_type`、`value_type`、`size_type` 等：常用类型别名。
- `op_mgr_type`：操作符管理器类型。
- `op_mgr_ptr_type`：操作符管理器指针类型。

#### 主要成员函数

- 构造、拷贝、移动、赋值、swap 等基本操作。
- `clear()`、`erase()`、`empty()`、`size()`：容器管理。
- `get_val_ptr<T>(key)`、`get_value<T>(key)`：类型安全地获取参数值指针或引用。
- `safe_get_val_ptr<T>(key)`、`unsafe_get_val_ptr<T>(key)`：安全/非安全获取值指针。
- `operator[]`：访问或插入参数。
- `copy_from`、`merge_datas_from`、`swap_datas`：批量数据操作。
- `val_export`、`val_import`：自定义导入导出接口。
- `type(key)`、`type_name(key)`：查询参数类型信息。
- 支持一元、二元操作符（如 `+`, `-`, `*`, `/`, `&`, `|`, `^`, `<<`, `>>` 及其复合赋值），通过操作符管理器批量作用于所有参数。
- `equal_to`：判断两个参数集合是否相等。

#### 错误处理

- 内置错误码和错误消息，支持参数不存在、操作符缺失、序列化不支持等异常场景。

#### 序列化支持

- 支持基于 `yggr::any` 的序列化。
- 对 `boost::any` 类型参数，序列化时抛出异常。

## 非成员操作符重载

- 支持参数集合的加减乘除、位运算、比较等操作符的全局重载，便于直接使用 `+`, `-`, `*`, `/`, `==`, `!=` 等操作。

## swap 支持

- 提供 `swap` 支持，可与标准库和 Boost 的 `swap` 机制无缝集成。

## 用法示例

```cpp
#include <yggr/any_val/params.hpp>

yggr::any_val::params<std::string> p1, p2;
p1["a"] = 10;
p2["a"] = 20;

auto p3 = p1 + p2; // 对相同 key 的值执行加法
int val = p3.get_value<int>("a"); // val == 30
```

## 依赖

- any_operator_mgr.hpp
- any_set.hpp
- map.hpp
- exception_sort.hpp
- error_make.hpp
- access.hpp
- 以及 Boost、yggdrasil 项目相关基础设施

---

如需详细功能和实现细节，请参考本文件实现及相关依赖头文件。