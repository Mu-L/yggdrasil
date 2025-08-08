---
# 文件：text_iarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的文本输入归档类 `text_iarchive` 及其实现，支持从文本流（如 `std::istream`）中反序列化（读取）C++ 对象。该类基于 Boost.Serialization 的归档机制，扩展了多字符集和多种字符串类型的支持，并对 Boost 的序列化器做了补丁处理，适用于文本格式数据的高效反序列化。

---

## 主要内容

### 1. 依赖

- Boost.Serialization 相关头文件（如 text_iarchive.hpp）
- Yggdrasil 的归档实现与工具（如 `basic_text_iprimitive.hpp`、`archive_data_wrap_traits.hpp` 等）
- 字符串和集合大小类型支持
- Boost 类型工具与特性检测

---

### 2. 归档实现模板

#### `text_iarchive_impl`

```cpp
template<class Archive>
class text_iarchive_impl
    : public boost::archive::text_iarchive_impl<Archive>
{
    // 主要成员与方法见下文
};
```

- **用途**：为文本输入归档提供底层实现，支持多种字符串类型和字符集的反序列化。
- **load 重载**：支持 `char*`、`wchar_t*`、`c8*`、`c16*`、`c32*` 及其 `std::basic_string` 和 `boost::container::basic_string` 变体的反序列化。
- **集合大小类型支持**：支持 `boost::serialization::collection_size_type` 和 `yggr::serialization::collection_size_type`。
- **内部辅助函数**：`pro_load_const_char_pointer_1n` 用于处理多字符集字符串的读取。

---

### 3. 归档类型定义

#### `naked_text_iarchive`

```cpp
class naked_text_iarchive 
    : public yggr::archive::text_iarchive_impl<yggr::archive::naked_text_iarchive>
{
public:
    naked_text_iarchive(std::istream & is_, unsigned int flags = 0);
    ~naked_text_iarchive();
};
```

- **用途**：标准文本输入归档，不包含 shared_ptr 辅助功能。
- **构造**：支持通过输入流构造。

#### `text_iarchive`

```cpp
class text_iarchive 
    : public yggr::archive::text_iarchive_impl<yggr::archive::text_iarchive>
#if BOOST_VERSION < 105600
    , public boost::archive::detail::shared_ptr_helper
#endif
{
public:
    text_iarchive(std::istream & is_, unsigned int flags = 0);
    ~text_iarchive();
};
```

- **用途**：标准文本输入归档，兼容 Boost 1.56.0 之前版本时自动包含 shared_ptr 辅助功能。
- **构造**：支持通过输入流构造。

---

### 4. 类型注册与序列化补丁

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::text_iarchive)`  
  注册归档类型，便于 Boost.Serialization 导出机制识别。
- 包含 `iserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过宏自动应用到本归档类型及裸归档类型。

---

### 5. 兼容性

- 针对 Boost 1.56.0 之前版本，自动继承 `shared_ptr_helper`，以支持 shared_ptr 的特殊序列化需求。
- 支持多字符集（如 char8_t、char16_t、char32_t）和多种字符串类型。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的文本输入归档提供了标准实现，兼容 Boost.Serialization，支持多字符集、多字符串类型、类型注册和序列化补丁，适用于高效的文本数据反序列化场景。

