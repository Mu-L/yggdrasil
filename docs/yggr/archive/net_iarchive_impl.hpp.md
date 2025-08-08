---
# 文件：net_iarchive_impl.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的网络二进制输入归档实现模板类 `net_iarchive_impl`，用于从网络流（如 socket、网络缓冲区）中反序列化（读取）各种类型的数据。该类集成并扩展了 Boost.Serialization 的二进制归档机制，适配多字符集、多平台和网络字节序，支持高效的网络数据反序列化。

---

## 主要内容

### 1. 类模板 `net_iarchive_impl`

```cpp
template<typename Archive, typename Elem, typename Tr>
class net_iarchive_impl :
    public boost::archive::basic_binary_iprimitive<Archive, Elem, Tr>,
    public boost::archive::basic_binary_iarchive<Archive>
{
    // 主要成员与方法见下文
};
```

#### 主要类型定义

- 继承自 Boost 的二进制输入原语和归档基类，支持流缓冲区和输入流构造。
- 通过 `init(flags)` 初始化归档状态，支持无头模式。

#### 主要成员函数

- **load_override**  
  模板重载，支持对任意类型的反序列化，委托给基类处理。

- **load**  
  针对多种类型的专门反序列化实现，包括：
  - 集合大小类型（`boost::serialization::collection_size_type`、`yggr::serialization::collection_size_type`）
  - Boost 归档内部类型（如 `tracking_type`、`library_version_type`、`version_type`、`class_id_type`、`object_id_type`）
  - 字符串类型（`char*`、`wchar_t*`、`c8*`、`c16*`、`c32*` 及其 `std::basic_string` 和 `boost::container::basic_string` 变体）
  - 基本类型（`bool`、`s8`、`u8`、`s16`、`u16`、`s32`、`u32`、`s64`、`u64`、`f32`、`f64` 等）

- **网络字节序处理**  
  对多字节类型（如 `wchar_t`、`c16`、`c32`、`s16`、`u16`、`s32`、`u32`、`s64`、`u64`、`f32`、`f64` 等）自动进行网络字节序（ntoh）转换，保证跨平台数据一致性。

- **字符串处理**  
  - 对于单字节字符串，直接读取长度和内容。
  - 对于多字节字符串，读取后逐元素进行字节序转换。
  - 自动处理字符串结尾的空字符。

- **use_array_optimization**  
  嵌套结构体，指示对单字节类型启用数组优化，提高序列化性能。

---

## 特性与适配

- 支持多种字符集（char、wchar_t、char8_t、char16_t、char32_t）
- 支持标准库和 Boost.Container 的字符串类型
- 针对不同平台和编译器做了兼容性处理
- 适配 Boost.Serialization 的归档机制，支持集合大小类型的反序列化
- 自动处理网络字节序，适合网络通信场景

---

## 命名空间

- 所有内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的网络二进制输入归档提供了高效、类型安全的反序列化实现，兼容 Boost.Serialization，适用于多字符集、多平台和网络通信的二进制数据读取场景。

