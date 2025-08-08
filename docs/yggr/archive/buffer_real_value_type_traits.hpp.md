---
# 文件：buffer_real_value_type_traits.hpp

## 简介

该头文件为 Yggdrasil 框架归档系统提供了缓冲区实际存储值类型的类型萃取工具。通过模板和宏，可以为不同的源类型指定实际用于缓冲区存储的类型，便于归档系统在多字符集和多平台环境下实现类型安全的数据处理。

---

## 主要内容

### 1. 类型萃取模板

```cpp
template<typename T>
struct buffer_real_value
{
    typedef T type;
};
```

- **用途**：默认情况下，`buffer_real_value<T>::type` 就是 `T` 本身。
- **扩展**：可通过特化为某些类型指定不同的实际存储类型。

---

### 2. 类型特化宏

```cpp
#define YGGR_ARCHIVE_BUFFER_REAL_VALUE_DEF(__src__, __dst__) \
    namespace yggr{ namespace archive { \
        template<> struct buffer_real_value< __src__ > { \
             typedef __dst__ type; }; } }
```

- **用途**：为指定的源类型 `__src__` 定义实际缓冲区存储类型为 `__dst__`。
- **典型用法**：
    ```cpp
    YGGR_ARCHIVE_BUFFER_REAL_VALUE_DEF(char, yggr::u8)
    ```
    这将使 `buffer_real_value<char>::type` 为 `yggr::u8`，而不是 `char`。

---

## 命名空间

- 所有内容位于 `yggr::archive` 命名空间下。

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为归档缓冲区的实际值类型提供了模板化、可扩展的类型萃取机制，便于在不同字符集和平台下安全、灵活地处理归档数据的存储类型。

