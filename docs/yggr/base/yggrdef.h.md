---
# yggrdef.h 文档

## 文件简介

yggrdef.h 是 Yggdrasil 工程的基础类型定义头文件，统一定义了常用的整数、浮点数、字符类型别名，以及与平台相关的指针、序列化等类型。该文件为整个工程提供了类型基础，便于跨平台开发和类型一致性维护。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggr_config.h>`
- `<yggr/base/pragma_message.hpp>`
- `<yggr/base/third_party_issues_config.hpp>`
- `<yggr/base/new.hpp>`
- `<boost/cstdint.hpp>`
- `<cstddef>`

---

## 主要内容

### 1. DLL 导出/导入宏定义（仅 MSVC）

- 处理 `BOOST_SYMBOL_EXPORT` 和 `BOOST_SYMBOL_IMPORT`，用于处理MSVC包含BOOST头文件后EXE输出LIB文件的问题。。

### 2. 基础类型别名

在 `namespace yggr` 内定义了如下类型别名：

- **整数类型**
  - `s8`  ：有符号 8 位整数（`boost::int8_t`）
  - `u8`  ：无符号 8 位整数（`boost::uint8_t`）
  - `s16` ：有符号 16 位整数（`boost::int16_t`）
  - `u16` ：无符号 16 位整数（`boost::uint16_t`）
  - `s32` ：有符号 32 位整数（`boost::int32_t`）
  - `u32` ：无符号 32 位整数（`boost::uint32_t`）
  - `s64` ：有符号 64 位整数（`boost::int64_t`）
  - `u64` ：无符号 64 位整数（`boost::uint64_t`）
  - `sint`：有符号 int
  - `uint`：无符号 int

- **浮点类型**
  - `f32` ：32 位浮点数（`float`）
  - `f64` ：64 位浮点数（`double`）

- **字符类型**
  - `c8`  ：8 位字符（`char8_t`，如未禁用）
  - `c16` ：16 位字符（`char16_t`，如未禁用）
  - `c32` ：32 位字符（`char32_t`，如未禁用）

- **指针与序列化相关类型**
  - `size_type`    ：平台相关的无符号整数（32/64 位）
  - `s_size_type`  ：平台相关的有符号整数（32/64 位）
  - `ptr_num_type` ：指针数值类型（32/64 位）
  - `ser_size_type`：序列化用的长度类型（可强制为 32 位）

### 3. 枚举值类型 enum_value_t

- 通过模板 `enum_value_t_maker` 根据枚举类型大小自动选择合适的无符号整数类型（u8/u16/u32/u64）。
- `enum_value_t` 用于统一工程内枚举值的底层类型。

---

## 用法示例

````cpp
#include <yggr/base/yggrdef.h>

yggr::u32 a = 100;
yggr::f64 b = 3.14;
yggr::size_type sz = 1024;
yggr::enum_value_t ev = 1;
````

---

## 注意事项

- 本文件应在所有 Yggdrasil 工程源码的最前面包含。
- 类型定义依赖于 Boost 的定长整数类型，确保跨平台一致性。
- 指针和序列化相关类型会根据平台自动适配 32 位或 64 位。
- 若需自定义类型宽度或禁用某些类型，可通过相关宏控制（如 `YGGR_NO_CHAR8_T`）。

---

 

