---
# 文件：text_oarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的文本输出归档类 `text_oarchive` 及其实现，支持将 C++ 对象以文本格式序列化（写入）到输出流（如 `std::ostream`）中。该类基于 Boost.Serialization 的归档机制，扩展了多字符集和多种字符串类型的支持，并对 Boost 的序列化器做了补丁处理，适用于文本格式数据的高效序列化。

---

## 主要内容

### 1. 依赖

- Boost.Serialization 相关头文件（如 text_oarchive.hpp）
- Yggdrasil 的归档实现与工具（如 `basic_text_oprimitive.hpp`、`archive_data_wrap_traits.hpp` 等）
- 字符串和集合大小类型支持
- Boost 类型工具与特性检测

---

### 2. 归档实现模板

#### `text_oarchive_impl`

```cpp
template<typename Archive>
class text_oarchive_impl
    : public boost::archive::text_oarchive_impl<Archive>
{
    // 主要成员与方法见下文
};
```

- **用途**：为文本输出归档提供底层实现，支持多种字符串类型和字符集的序列化。
- **save 重载**：
  - 支持 `char*`、`std::basic_string<char>`、`boost::container::basic_string<char>` 的序列化。
  - 支持 `wchar_t*`、`c8*`、`c16*`、`c32*` 及其 `std::basic_string` 和 `boost::container::basic_string` 变体的序列化（自动处理长度和字节宽度）。
  - 支持 `boost::serialization::collection_size_type` 和 `yggr::serialization::collection_size_type`。
  - 内部辅助函数 `pro_save_const_char_pointer_1n` 用于处理多字符集字符串的写入。
  - 针对 `c8`、`c16`、`c32` 类型，自动转换为合适的整型进行保存。

---

### 3. 归档类型定义

#### `text_oarchive`

```cpp
class text_oarchive
    : public yggr::archive::text_oarchive_impl<yggr::archive::text_oarchive>
{
public:
    text_oarchive(std::ostream & os_, unsigned int flags = 0);
    ~text_oarchive();
};
```

- **用途**：标准文本输出归档，支持通过输出流构造。
- **别名**：`typedef text_oarchive naked_text_oarchive;`  
  裸归档类型，功能等同于 `text_oarchive`。

---

### 4. 类型注册与序列化补丁

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::text_oarchive)`  
  注册归档类型，便于 Boost.Serialization 导出机制识别。
- 包含 `oserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过宏自动应用到本归档类型。

---

### 5. 兼容性

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

本文件为 Yggdrasil 框架下的文本输出归档提供了标准实现，兼容 Boost.Serialization，支持多字符集、多字符串类型、类型注册和序列化补丁，适用于高效的文本数据序列化场景。

