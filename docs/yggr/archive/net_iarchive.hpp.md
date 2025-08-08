---
# 文件：net_iarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的网络二进制输入归档类 `net_iarchive` 及其裸归档版本 `naked_net_iarchive`，用于从网络流（如 socket、网络缓冲区）中反序列化（读取）C++ 对象。该类基于 Boost.Serialization 的归档机制，支持类型注册、数组优化、shared_ptr 辅助和序列化补丁，适用于网络通信场景下的高效二进制反序列化。

---

## 主要内容

### 1. 依赖

- `net_iarchive_impl.hpp`：网络输入归档实现模板
- `archive_data_wrap_traits.hpp`：归档数据包装特性
- Boost.Serialization 相关头文件
- `iserializer_patch.hpp`：Boost 非指针类型序列化补丁

---

### 2. 类定义

#### `naked_net_iarchive`

```cpp
class naked_net_iarchive 
    : public net_iarchive_impl<
            yggr::archive::naked_net_iarchive, 
            std::istream::char_type, 
            std::istream::traits_type
        >
{
public:
    naked_net_iarchive(std::istream & is, unsigned int flags = 0);
    naked_net_iarchive(std::streambuf & bsb, unsigned int flags = 0);
};
```

- **用途**：标准网络输入归档，不包含 shared_ptr 辅助功能。
- **构造**：支持通过输入流或流缓冲区构造。

#### `net_iarchive`

```cpp
class net_iarchive
    : public net_iarchive_impl<
            yggr::archive::net_iarchive, 
            std::istream::char_type, 
            std::istream::traits_type
        >
#if BOOST_VERSION < 105600
    , public boost::archive::detail::shared_ptr_helper
#endif
{
public:
    net_iarchive(std::istream & is, unsigned int flags = 0);
    net_iarchive(std::streambuf & bsb, unsigned int flags = 0);
};
```

- **用途**：标准网络输入归档，兼容 Boost 1.56.0 之前版本时自动包含 shared_ptr 辅助功能。
- **构造**：支持通过输入流或流缓冲区构造。

---

### 3. 类型注册与序列化优化

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::net_iarchive)`  
  注册归档类型，便于 Boost.Serialization 导出机制识别。
- `BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(yggr::archive::net_iarchive)`  
  启用数组序列化优化，提高性能。

---

### 4. 兼容性与补丁

- 针对 Boost 1.56.0 之前版本，自动继承 `shared_ptr_helper`，以支持 shared_ptr 的特殊序列化需求。
- 包含 `iserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过宏自动应用到本归档类型。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下
- 类型注册相关内容位于 `boost` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的网络二进制输入归档提供了标准实现，兼容 Boost.Serialization，支持类型注册、数组优化、shared_ptr 特性和序列化补丁，适用于高效的网络数据反序列化场景。

