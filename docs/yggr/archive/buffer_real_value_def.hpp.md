---
# 文件：buffer_real_value_def.hpp

## 简介

该头文件为 Yggdrasil 框架下归档系统定义了缓冲区实际存储值类型的相关宏和类型别名。主要用于在归档过程中，根据不同字符类型（如 `char`、`wchar_t`）自动选择合适的实际存储类型，提升跨平台和多字符集环境下的兼容性和类型安全。

---

## 主要内容

### 1. 依赖

- `buffer_real_value_type_traits.hpp`：缓冲区实际值类型特性宏和工具
- Boost MPL：用于条件类型选择

---

### 2. 宏定义

#### `YGGR_ARCHIVE_BUFFER_REAL_VALUE_DEF`

```cpp
YGGR_ARCHIVE_BUFFER_REAL_VALUE_DEF(char, yggr::u8);
```

- **用途**：为 `char` 类型定义实际缓冲区值类型为 `yggr::u8`（通常为无符号8位整型）。

---

### 3. 宽字符类型适配

#### `wchar_value_type` 类型别名

```cpp
typedef boost::mpl::if_c<
    (sizeof(wchar_t) == 2),
    yggr::u16,
    yggr::u32
>::type wchar_value_type;
```

- **用途**：根据平台上 `wchar_t` 的字节数，自动选择实际缓冲区值类型：
  - 若 `wchar_t` 为2字节，则用 `yggr::u16`（16位无符号整型）
  - 否则用 `yggr::u32`（32位无符号整型）

#### 宏定义

```cpp
YGGR_ARCHIVE_BUFFER_REAL_VALUE_DEF(wchar_t, yggr::archive::detail::wchar_value_type)
```

- **用途**：为 `wchar_t` 类型定义实际缓冲区值类型为上面自动推导的 `wchar_value_type`。

---

## 命名空间

- 主要内容位于 `yggr::archive::detail` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为归档缓冲区的实际值类型提供了跨平台、类型安全的定义方式，确保在不同字符集和平台下归档数据的正确存储和读取。

