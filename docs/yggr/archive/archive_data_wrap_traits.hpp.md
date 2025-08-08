---
# 文件：archive_data_wrap_traits.hpp

## 简介

该头文件定义了用于归档（archive）数据包装类型特性的模板结构体和相关宏，主要用于确定某种类型在特定归档类型下是否需要特殊的二进制数据包装。此机制便于在序列化/反序列化时对不同类型采用不同的处理方式。

---

## 主要内容

### 1. `binary_data_wrap_traits` 模板结构体

```cpp
template<typename Archive, typename T>
struct binary_data_wrap_traits : public boost::mpl::false_ {
    typedef T wrap_type;
};
```

- **用途**：用于判断类型 `T` 在归档类型 `Archive` 下是否需要二进制包装。
- **默认行为**：继承自 `boost::mpl::false_`，即默认不需要特殊包装。
- **成员类型**：`wrap_type`，默认为 `T` 本身。

---

### 2. 宏定义

#### (1) `YGGR_PP_ARCHIVE_BINARY_DATA_WRAP_TRAITS_DEF`

```cpp
#define YGGR_PP_ARCHIVE_BINARY_DATA_WRAP_TRAITS_DEF( __archive__, __val__, __wrap__ ) \
    namespace yggr { namespace archive { \
    template<> struct binary_data_wrap_traits< __archive__, __val__ > \
        : public boost::mpl::true_ { typedef __wrap__ type; }; }}
```

- **用途**：为特定的归档类型和数据类型定义需要二进制包装，并指定包装类型。
- **参数**：
  - `__archive__`：归档类型
  - `__val__`：原始类型
  - `__wrap__`：包装类型

#### (2) 其它辅助宏

- `YGGR_PP_ARCHIVE_BINARY_DATA_WRAP_TRAITS(__archive__, __val__)`  
  获取指定归档和类型的 traits 类型。

- `YGGR_PP_ARCHIVE_BINARY_DATA_WRAP_TRAITS_WRAP(__archive__, __val__)`  
  获取包装类型（wrap_type）。

- `YGGR_PP_ARCHIVE_NEED_BINARY_DATA_WRAP_TRAITS_T(__archive__, __val__)`  
  获取包装类型（type）。

- `YGGR_PP_ARCHIVE_NEED_BINARY_DATA_WRAP_TRAITS_V(__archive__, __val__)`  
  获取是否需要包装的布尔值（value）。

---

## 命名空间

- `yggr::archive`  
  所有类型和宏均定义在该命名空间下。

---

## 典型用法

1. **自定义类型包装特化：**

```cpp
YGGR_PP_ARCHIVE_BINARY_DATA_WRAP_TRAITS_DEF(MyArchive, MyType, MyTypeWrap)
```
此宏会为 `MyArchive` 和 `MyType` 生成特化版本，表明 `MyType` 需要包装为 `MyTypeWrap`。

2. **判断是否需要包装：**

```cpp
bool need_wrap = YGGR_PP_ARCHIVE_NEED_BINARY_DATA_WRAP_TRAITS_V(MyArchive, MyType);
```

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

如需进一步了解用法，请参考相关归档和序列化实现。

