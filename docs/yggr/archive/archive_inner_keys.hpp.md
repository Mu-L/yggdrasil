---
# 文件：archive_inner_keys.hpp

## 简介

该头文件用于定义归档（archive）内部关键字的类型安全访问方式。通过一系列宏和模板，提供了跨多种字符类型（如 char、wchar_t、char8_t、char16_t、char32_t）和字符串类型的关键字常量表达，并支持类型安全的转换和获取。这些关键字主要用于序列化/反序列化过程中标识 Boost Archive 相关的内部字段。

---

## 主要内容

### 1. 关键字类型转换宏

根据编译环境支持的字符类型，定义了将关键字转换为不同指针类型的操作符重载宏：

- `YGGR_ARCHIVE_INNER_KEYS_OPERATOR_POINTER_WCHAR_T()`
- `YGGR_ARCHIVE_INNER_KEYS_OPERATOR_POINTER_CHAR8()`
- `YGGR_ARCHIVE_INNER_KEYS_OPERATOR_POINTER_CHAR16()`
- `YGGR_ARCHIVE_INNER_KEYS_OPERATOR_POINTER_CHAR32()`

这些宏分别为关键字结构体添加了向 `wchar_t*`、`char8_t*`、`char16_t*`、`char32_t*` 的类型转换操作符。

---

### 2. 关键字定义宏

#### `YGGR_ARCHIVE_INNER_KEYS_DEF(__key__)`

该宏会自动生成一个结构体和一个获取函数，用于类型安全地访问关键字常量。结构体支持多种字符类型和字符串类型的转换。

- **结构体**：`archive_inner_keys_<__key__>`
  - 支持向 `char*` 及多种字符串类型的隐式转换。
- **获取函数**：`inner_key_<__key__>()`
  - 根据模板参数类型，返回 const 指针或 const 引用，保证类型安全。

#### 典型用法

```cpp
YGGR_ARCHIVE_INNER_KEYS_DEF(boost_ar_obj_id)
```
会生成 `archive_inner_keys_boost_ar_obj_id` 结构体和 `inner_key_boost_ar_obj_id<T>()` 函数。

---

### 3. 预定义的归档内部关键字

通过宏定义，预设了以下 Boost Archive 相关关键字：

- `boost_ar_obj_id`
- `boost_ar_obj_id_ref`
- `boost_ar_ver`
- `boost_ar_library_ver`
- `boost_ar_class_id`
- `boost_ar_class_id_ref`
- `boost_ar_class_name`
- `boost_ar_tracking`

---

### 4. 辅助宏

- `YGGR_ARCHIVE_GET_INNER_KEY(__type__, __key__)`  
  获取指定类型和关键字的类型安全常量。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下。

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为归档内部关键字的类型安全访问提供了统一的接口，支持多字符集和多字符串类型，便于跨平台和多语言环境下的序列化开发。

