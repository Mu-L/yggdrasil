---
# 文件：xml_oarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的 XML 输出归档类 `xml_oarchive` 及其实现，支持将 C++ 对象以 XML 格式序列化（写入）到输出流（如 `std::ostream`）中。该类基于 Boost.Serialization 的归档机制，扩展了多字符集和多种字符串类型的支持，并对 Boost 的序列化器做了补丁处理，适用于 XML 格式数据的高效序列化。

---

## 主要内容

### 1. 依赖

- Boost.Serialization 相关头文件（如 xml_oarchive.hpp）
- Yggdrasil 的归档实现与工具（如 `basic_text_oprimitive.hpp`、`basic_xml_oarchive.hpp`、`archive_serializer_map.hpp`、`xml_oarchive_impl.hpp` 等）
- 字符串和集合大小类型支持
- 字符集转换工具
- Boost 类型工具与特性检测

---

### 2. 归档实现模板

#### `xml_oarchive_impl`

```cpp
template<class Archive>
class xml_oarchive_impl : public boost::archive::xml_oarchive_impl<Archive>
{
    // 主要成员与方法见下文
};
```

- **用途**：为 XML 输出归档提供底层实现，支持多种字符串类型和字符集的序列化。
- **save 重载**：
  - 支持 `char*`、`std::basic_string<char>`、`boost::container::basic_string<char>` 的序列化（自动进行 XML 转义）。
  - 支持 `wchar_t*`、`std::basic_string<wchar_t>`、`boost::container::basic_string<wchar_t>` 直接写入。
  - 支持其它字符类型（如 `c8`、`c16`、`c32`）及其字符串的序列化，自动进行字符集转换。
  - 支持 `boost::serialization::collection_size_type` 和 `yggr::serialization::collection_size_type`。
  - 内部辅助函数 `pro_save_char_string`、`pro_save_wchar_t_string` 用于处理字符串的写入。
  - 针对 `c8`、`c16`、`c32` 类型，自动转换为合适的整型进行保存。

---

### 3. 归档类型定义

#### `xml_oarchive`

```cpp
class xml_oarchive 
    : public yggr::archive::xml_oarchive_impl<yggr::archive::xml_oarchive>
{
public:
    typedef std::ostream::char_type char_type;
    typedef std::ostream::traits_type traits_type;
    xml_oarchive(std::ostream & os, unsigned int flags = 0);
    ~xml_oarchive();
};
```

- **用途**：标准 XML 输出归档，支持通过输出流构造。
- **别名**：`typedef xml_oarchive naked_xml_oarchive;`  
  裸归档类型，功能等同于 `xml_oarchive`。

---

### 4. 类型注册与序列化补丁

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::xml_oarchive)`  
  注册归档类型，便于 Boost.Serialization 导出机制识别。
- 包含 `oserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过宏自动应用到本归档类型。

---

### 5. 兼容性

- 支持多字符集（如 char8_t、char16_t、char32_t）和多种字符串类型。
- 针对 MSVC 编译器做了警告抑制处理。
- 自动进行字符集转换，确保不同字符类型的数据能正确序列化为 XML。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的 XML 输出归档提供了标准实现，兼容 Boost.Serialization，支持多字符集、多字符串类型、类型注册和序列化补丁，适用于高效的 XML 数据序列化场景。

