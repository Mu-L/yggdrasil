---
# 文件：bson_oarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的 BSON 输出归档类 `bson_oarchive` 及其实现，支持将 C++ 对象序列化（写入）为 BSON 数据缓冲区。该类基于 Boost.Serialization 归档机制，支持 NLD（No Load 无法被反序列化）模式、类型注册、二进制数据包装和序列化补丁，适用于 MongoDB BSON 格式命令的高效序列化

---

## 主要内容

### 1. 依赖

- `basic_bson_oarchive.hpp`：BSON 输出归档基础实现
- Boost.Serialization 相关头文件
- Yggdrasil 的 BSON 数据结构与辅助工具
- 归档数据包装 traits、序列化补丁等

---

### 2. 归档实现模板

#### `bson_oarchive_impl`

```cpp
template<typename Archive>
class bson_oarchive_impl : public basic_bson_oarchive<Archive>
{
    // 主要成员与方法见下文
};
```

- **用途**：为 BSON 输出归档提供底层实现，支持各种类型的序列化。
- **save 重载**：支持任意类型、集合大小类型、版本类型等的序列化，自动断言类型安全。
- **use_array_optimization**：禁用数组优化（始终为 false）。

---

### 3. 归档类型定义

#### `bson_oarchive`

```cpp
template<bool nld>
class bson_oarchive : public bson_oarchive_impl<bson_oarchive<nld>>
{
public:
    typedef yggr::nsql_database_system::c_bson buf_type;
    bson_oarchive(buf_type& buf, unsigned int flags = 0);
    ~bson_oarchive();
    static bool is_nld();
};
```

- **用途**：标准 BSON 输出归档，支持 NLD 模式。
- **nld**：模板参数，控制是否为 NLD 模式。

#### `naked_bson_oarchive`

```cpp
template<bool nld>
class naked_bson_oarchive : public bson_oarchive_impl<naked_bson_oarchive<nld>>
{
public:
    typedef yggr::nsql_database_system::c_bson buf_type;
    naked_bson_oarchive(buf_type& buf, unsigned int flags = 0);
    ~naked_bson_oarchive();
    static bool is_nld();
};
```

- **用途**：裸 BSON 输出归档，功能与 `bson_oarchive` 类似，不包含 shared_ptr 辅助功能。

---

### 4. 类型注册与序列化补丁

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::bson_oarchive<true>)`
- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::bson_oarchive<false>)`
- 针对 `bson_oarchive` 和 `naked_bson_oarchive`，通过特化 `binary_data_wrap_traits`，指定二进制数据包装类型为 `c_bson_binary_buffer_ref`。
- 包含 `oserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过特化自动应用到本归档类型。

---

### 5. 兼容性与扩展

- 支持 NLD（No Length Data）模式，适应不同业务需求。
- 通过宏防止重复定义归档类型。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下
- 类型注册和补丁相关内容位于 `boost::archive::detail` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的 BSON 输出归档提供了标准实现，兼容 Boost.Serialization，支持类型注册、二进制包装、NLD 模式和序列化补丁，适用于高效的 BSON 数据序列化场景。

