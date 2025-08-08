---
# 文件：net_oarchive_impl.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的网络二进制输出归档实现模板类 `net_oarchive_impl`，用于将各种类型的数据（包括多种字符串类型和基础类型）以网络字节序高效地序列化（写入）到网络流（如 socket、网络缓冲区）中。该类集成并扩展了 Boost.Serialization 的二进制归档机制，适配多字符集、多平台和网络通信场景。

---

## 主要内容

### 1. 类模板 `net_oarchive_impl`

```cpp
template<typename Archive, typename Elem, typename Tr>
class net_oarchive_impl :
    public boost::archive::basic_binary_oprimitive<Archive, Elem, Tr>,
    public boost::archive::basic_binary_oarchive<Archive>
{
    // 主要成员与方法见下文
};
```

#### 主要类型定义

- 继承自 Boost 的二进制输出原语和归档基类，支持流缓冲区和输出流构造。
- 通过 `init(flags)` 初始化归档状态，支持无头模式。

#### 主要成员函数

- **save_override**  
  模板重载，支持对任意类型的序列化，委托给基类处理。

- **save**  
  针对多种类型的专门序列化实现，包括：
  - 集合大小类型（`boost::serialization::collection_size_type`、`yggr::serialization::collection_size_type`）
  - Boost 归档内部类型（如 `tracking_type`、`library_version_type`、`version_type`、`class_id_type`、`object_id_type`）
  - 字符串类型（`char*`、`wchar_t*`、`c8*`、`c16*`、`c32*` 及其 `std::basic_string` 和 `boost::container::basic_string` 变体）
  - 基本类型（`bool`、`s8`、`u8`、`s16`、`u16`、`s32`、`u32`、`s64`、`u64`、`f32`、`f64` 等）

- **网络字节序处理**  
  对多字节类型（如 `wchar_t`、`c16`、`c32`、`s16`、`u16`、`s32`、`u32`、`s64`、`u64`、`f32`、`f64` 等）自动进行主机到网络字节序（hton）转换，保证跨平台数据一致性。

- **字符串处理**  
  - 对于单字节字符串，直接写入长度和内容。
  - 对于多字节字符串，写入前逐元素进行字节序转换。
  - 自动处理字符串结尾的空字符。

- **use_array_optimization**  
  嵌套结构体，指示对单字节类型启用数组优化，提高序列化性能。

---

## 特性与适配

- 支持多种字符集（char、wchar_t、char8_t、char16_t、char32_t）
- 支持标准库和 Boost.Container 的字符串类型
- 针对不同平台和编译器做了兼容性处理
- 适配 Boost.Serialization 的归档机制，支持集合大小类型的序列化
- 自动处理网络字节序，适合网络通信场景

---

## 命名空间

- 所有内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的网络二进制输出归档提供了高效、类型安全的序列化实现，兼容 Boost.Serialization，适用于多字符集、多平台和网络通信的二进制数据写入场景。

