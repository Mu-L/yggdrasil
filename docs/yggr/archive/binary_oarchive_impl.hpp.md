---
# 文件：binary_oarchive_impl.hpp

## 简介

该头文件定义了 Yggdrasil 框架下二进制输出归档的实现模板类 `binary_oarchive_impl`，用于将各种类型的数据（尤其是多种字符串类型和集合大小类型）高效地序列化（写入）到二进制流中。该类集成并扩展了 Boost.Serialization 的二进制归档机制，适配多字符集和多平台环境。

---

## 主要内容

### 1. 类模板 `binary_oarchive_impl`

```cpp
template<typename Archive, typename Elem, typename Tr>
class binary_oarchive_impl
    : public boost::archive::basic_binary_oprimitive<Archive, Elem, Tr>,
      public boost::archive::basic_binary_oarchive<Archive>
{
    // 主要成员与方法见下文
};
```

#### 主要类型定义

- `base_type`：Boost 的二进制输出原语基类
- 继承自 Boost 的二进制输出归档基类

#### 构造与初始化

- 支持通过 `std::basic_streambuf` 或 `std::basic_ostream` 构造，自动初始化归档状态。
- `init` 方法根据归档标志初始化归档头部信息。

#### 主要成员函数

- `save_override`  
  模板重载，支持对任意类型的序列化，委托给基类处理。

- `save`  
  针对不同字符串类型（如 `std::basic_string`、`boost::container::basic_string`、`char*`、`wchar_t*`、`c8*`、`c16*`、`c32*` 等）和集合大小类型（如 `boost::serialization::collection_size_type`、`yggr::serialization::collection_size_type`）的专门序列化实现。  
  - 对于单字节字符类型，直接写入长度和内容。
  - 对于多字节字符类型，按字符宽度写入内容。
  - 自动处理字符串结尾的空字符。

- `pro_save_string_char_1` / `pro_save_string_char_n`  
  内部辅助函数，分别处理单字节和多字节字符的字符串序列化。

---

## 特性与适配

- 支持多种字符集（char、wchar_t、char8_t、char16_t、char32_t）
- 支持标准库和 Boost.Container 的字符串类型
- 针对不同平台和编译器做了兼容性处理
- 适配 Boost.Serialization 的归档机制，支持集合大小类型的序列化

---

## 命名空间

- 所有内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的二进制输出归档提供了高效、类型安全的序列化实现，兼容 Boost.Serialization，适用于多字符集和多平台的二进制数据写入场景。

