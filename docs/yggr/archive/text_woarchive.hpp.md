---
# 文件：text_woarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的宽字符文本输出归档类 `text_woarchive` 及其实现，支持将 C++ 对象以宽字符文本格式序列化（写入）到输出流（如 `std::wostream`）中。该类基于 Boost.Serialization 的归档机制，扩展了多字符集和多种字符串类型的支持，并对 Boost 的序列化器做了补丁处理，适用于宽字符文本格式数据的高效序列化。

---

## 主要内容

### 1. 依赖

- Boost.Serialization 相关头文件（如 text_woarchive.hpp）
- Yggdrasil 的归档实现与工具（如 `basic_text_oprimitive.hpp`、`archive_data_wrap_traits.hpp` 等）
- 字符串和集合大小类型支持
- 字符集转换工具
- Boost 类型工具与特性检测

---

### 2. 归档实现模板

#### `text_woarchive_impl`

```cpp
template<typename Archive>
class text_woarchive_impl : public boost::archive::text_woarchive_impl<Archive>
{
    // 主要成员与方法见下文
};
```

- **用途**：为宽字符文本输出归档提供底层实现，支持多种字符串类型和字符集的序列化。
- **save 重载**：
  - 支持 `char*`、`std::basic_string<char>`、`boost::container::basic_string<char>` 的序列化（自动转换为宽字符写入）。
  - 支持 `wchar_t*`、`std::basic_string<wchar_t>`、`boost::container::basic_string<wchar_t>` 直接写入。
  - 支持其它字符类型（如 `c8`、`c16`、`c32`）及其字符串的序列化，自动进行字符集转换。
  - 支持 `boost::serialization::collection_size_type` 和 `yggr::serialization::collection_size_type`。
  - 内部辅助函数 `pro_save_const_wchar_t_pointer`、`pro_save_wchar_t_string` 用于处理宽字符字符串的写入。
  - 针对 `c8`、`c16`、`c32` 类型，自动转换为合适的整型进行保存。

---

### 3. 归档类型定义

#### `text_woarchive`

```cpp
class text_woarchive 
    : public yggr::archive::text_woarchive_impl<yggr::archive::text_woarchive>
{
public:
    typedef std::wostream::char_type char_type;
    typedef std::wostream::traits_type traits_type;
    text_woarchive(std::wostream & os, unsigned int flags = 0);
    ~text_woarchive();
};
```

- **用途**：标准宽字符文本输出归档，支持通过宽字符输出流构造。
- **别名**：`typedef text_woarchive naked_text_woarchive;`  
  裸归档类型，功能等同于 `text_woarchive`。

---

### 4. 类型注册与序列化补丁

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::text_woarchive)`  
  注册归档类型，便于 Boost.Serialization 导出机制识别。
- 包含 `oserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过宏自动应用到本归档类型。

---

### 5. 兼容性

- 针对 MSVC 编译器做了警告抑制处理。
- 支持多字符集（如 char8_t、char16_t、char32_t）和多种字符串类型。
- 自动进行字符集转换，确保不同字符类型的数据能正确序列化为宽字符流。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的宽字符文本输出归档提供了标准实现，兼容 Boost.Serialization，支持多字符集、多字符串类型、类型注册和序列化补丁，适用于高效的宽字符文本数据序列化场景。

