---
# 文件：binary_wiarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的宽字符二进制输入归档类 `binary_wiarchive` 及其裸归档版本 `naked_binary_wiarchive`，用于从宽字符二进制流（如 `std::wistream`）中反序列化（读取）C++ 对象。该类基于 Boost.Serialization 的归档机制，支持类型注册、宽字符流兼容和序列化补丁，适用于宽字符环境下的高效二进制反序列化。

---

## 主要内容

### 1. 依赖

- `binary_iarchive_impl.hpp`：二进制输入归档实现模板
- `archive_data_wrap_traits.hpp`：归档数据包装特性
- `impl/codecvt_null.hpp`、`impl/utf8_codecvt_facet.hpp`：字符集转换支持
- Boost.Serialization 相关头文件

---

### 2. 类定义

#### `naked_binary_wiarchive`

```cpp
class naked_binary_wiarchive 
    : public binary_iarchive_impl<
            yggr::archive::naked_binary_wiarchive, 
            std::wistream::char_type, 
            std::wistream::traits_type
        >
{
public:
    naked_binary_wiarchive(std::wistream & is, unsigned int flags = 0);
    naked_binary_wiarchive(std::wstreambuf & bsb, unsigned int flags = 0);
};
```

- **用途**：标准宽字符二进制输入归档，不包含 shared_ptr 辅助功能。
- **构造**：支持通过宽字符输入流或流缓冲区构造。

#### `binary_wiarchive`

```cpp
class binary_wiarchive 
    : public binary_iarchive_impl<
            yggr::archive::binary_wiarchive,
            std::wistream::char_type, 
            std::wistream::traits_type
        >
{
public:
    binary_wiarchive(std::wistream & is, unsigned int flags = 0);
    binary_wiarchive(std::wstreambuf & bsb, unsigned int flags = 0);
};
```

- **用途**：标准宽字符二进制输入归档，支持通过宽字符输入流或流缓冲区构造。

---

### 3. 类型注册与序列化补丁

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::binary_wiarchive)`  
  注册归档类型，便于 Boost.Serialization 导出机制识别。
- 包含 `iserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过宏自动应用到本归档类型及裸归档类型。

---

### 4. 兼容性

- 若平台不支持宽字符流（`BOOST_NO_STD_WSTREAMBUF`），则编译时报错。
- 针对 Boost 1.56.0 之前版本，自动包含 `shared_ptr_helper`，以支持 shared_ptr 的特殊序列化需求。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的宽字符二进制输入归档提供了标准实现，兼容 Boost.Serialization，支持类型注册、宽字符流和序列化补丁，适用于宽字符环境下的高效二进制反序列化场景。

