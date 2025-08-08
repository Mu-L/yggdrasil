---
# 文件：xml_wiarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的宽字符 XML 输入归档类 `xml_wiarchive` 及其实现，支持从宽字符 XML 文本流（如 `std::wistream`）中反序列化（读取）C++ 对象。该类基于 Boost.Serialization 的归档机制，扩展了多字符集和多种字符串类型的支持，并对 Boost 的序列化器做了补丁处理，适用于宽字符 XML 格式数据的高效反序列化。

---

## 主要内容

### 1. 依赖

- Boost.Serialization 相关头文件（如 xml_wiarchive.hpp）
- Yggdrasil 的归档实现与工具（如 `basic_text_iprimitive.hpp`、`basic_xml_iarchive.hpp`、`archive_serializer_map.hpp`、`xml_wiarchive_impl.hpp` 等）
- 字符串和集合大小类型支持
- 字符集转换工具
- Boost 类型工具与特性检测

---

### 2. 归档实现模板

#### `xml_wiarchive_impl`

```cpp
template<typename Archive>
class xml_wiarchive_impl : public boost::archive::xml_wiarchive_impl<Archive>
{
    // 主要成员与方法见下文
};
```

- **用途**：为宽字符 XML 输入归档提供底层实现，支持多种字符串类型和字符集的反序列化。
- **load 重载**：
  - 支持 `std::basic_string<char>`、`boost::container::basic_string<char>` 的反序列化（自动进行宽字符到多字节字符集转换）。
  - 支持 `std::wstring`、`std::basic_string<wchar_t>`、`boost::container::basic_string<wchar_t>` 的直接反序列化。
  - 支持其它字符类型（如 `c8`、`c16`、`c32`）及其字符串的反序列化，自动进行字符集转换。
  - 支持 `boost::serialization::collection_size_type` 和 `yggr::serialization::collection_size_type`。
- **内部辅助函数**：
  - `pro_load_char_string`：处理宽字符到多字节字符串的读取与转换。
  - `pro_load_wchar_t_stl_string`、`pro_load_wchar_t_string`：处理宽字符字符串的读取。
- **字符集转换**：对于不同字符集的字符串，自动使用 `charset_converter` 进行转换，确保类型安全和数据正确性。
- **特殊字符类型支持**：支持 `c8`、`c16`、`c32` 类型的读取和转换。

---

### 3. 归档类型定义

#### `naked_xml_wiarchive`

```cpp
class naked_xml_wiarchive 
    : public yggr::archive::xml_wiarchive_impl<yggr::archive::naked_xml_wiarchive>
{
public:
    naked_xml_wiarchive(std::wistream & is, unsigned int flags = 0);
    ~naked_xml_wiarchive();
};
```

- **用途**：标准宽字符 XML 输入归档，不包含 shared_ptr 辅助功能。
- **构造**：支持通过宽字符输入流构造。

#### `xml_wiarchive`

```cpp
class xml_wiarchive
    : public yggr::archive::xml_wiarchive_impl<yggr::archive::xml_wiarchive>
#if BOOST_VERSION < 105600
    , public boost::archive::detail::shared_ptr_helper
#endif
{
public:
    xml_wiarchive(std::wistream & is, unsigned int flags = 0);
    ~xml_wiarchive();
};
```

- **用途**：标准宽字符 XML 输入归档，兼容 Boost 1.56.0 之前版本时自动包含 shared_ptr 辅助功能。
- **构造**：支持通过宽字符输入流构造。

---

### 4. 类型注册与序列化补丁

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::xml_wiarchive)`  
  注册归档类型，便于 Boost.Serialization 导出机制识别。
- 包含 `iserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过宏自动应用到本归档类型及裸归档类型。

---

### 5. 兼容性

- 针对 Boost 1.56.0 之前版本，自动继承 `shared_ptr_helper`，以支持 shared_ptr 的特殊序列化需求。
- 支持多字符集（如 char8_t、char16_t、char32_t）和多种字符串类型。
- 针对 MSVC 编译器做了警告抑制处理。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的宽字符 XML 输入归档提供了标准实现，兼容 Boost.Serialization，支持多字符集、多字符串类型、类型注册和序列化补丁，适用于高效的宽字符 XML 数据反序列化场景。

