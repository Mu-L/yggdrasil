---
# 文件：bson_iarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的 BSON 输入归档类 `bson_iarchive` 及其实现，支持从 BSON 数据缓冲区反序列化（读取）C++ 对象。该类基于 Boost.Serialization 归档机制，支持自动 ID 跳过、shared_ptr 辅助、类型注册、二进制数据包装和序列化补丁，适用于 BSON 格式数据的高效反序列化。

---

## 主要内容

### 1. 依赖

- `basic_bson_iarchive.hpp`：BSON 输入归档基础实现
- Boost.Serialization 相关头文件
- Yggdrasil 的 BSON 数据结构与辅助工具
- 归档数据包装 traits、序列化补丁等

---

### 2. 归档实现模板

#### `bson_iarchive_impl`

```cpp
template<class Archive>
class bson_iarchive_impl : public basic_bson_iarchive<Archive>
{
    // 主要成员与方法见下文
};
```

- **用途**：为 BSON 输入归档提供底层实现，支持各种类型的反序列化。
- **load 重载**：支持任意类型、集合大小类型、版本类型等的反序列化，自动断言类型安全。
- **use_array_optimization**：禁用数组优化（始终为 false）。

---

### 3. 归档类型定义

#### `naked_bson_iarchive`

```cpp
template<bool auto_id_skip>
class naked_bson_iarchive : public bson_iarchive_impl<naked_bson_iarchive<auto_id_skip>>
{
public:
    naked_bson_iarchive(buf_type& buf, unsigned int flags = 0);
    static bool is_skip_auto_id();
};
```

- **用途**：标准 BSON 输入归档，不包含 shared_ptr 辅助功能。
- **auto_id_skip**：模板参数，控制是否跳过自动 ID 字段。

#### `bson_iarchive`

```cpp
template<bool auto_id_skip>
class bson_iarchive : public bson_iarchive_impl<bson_iarchive<auto_id_skip>>
#if BOOST_VERSION < 105600
    , public boost::archive::detail::shared_ptr_helper
#endif
{
public:
    bson_iarchive(const buf_type& buf, unsigned int flags = 0);
    static bool is_skip_auto_id();
};
```

- **用途**：标准 BSON 输入归档，兼容 Boost 1.56.0 之前版本时自动包含 shared_ptr 辅助功能。
- **auto_id_skip**：模板参数，控制是否跳过自动 ID 字段。

---

### 4. 类型注册与序列化补丁

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::bson_iarchive<true>)`
- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::bson_iarchive<false>)`
- 针对 `bson_iarchive` 和 `naked_bson_iarchive`，通过特化 `binary_data_wrap_traits`，指定二进制数据包装类型为 `c_bson_binary_buffer_ref`。
- 包含 `iserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过特化自动应用到本归档类型。

---

### 5. 兼容性与扩展

- 针对 Boost 1.56.0 之前版本，自动继承 `shared_ptr_helper`，以支持 shared_ptr 的特殊序列化需求。
- 支持自动跳过 BSON 的 auto_id 字段，适应不同业务需求。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下
- 类型注册和补丁相关内容位于 `boost::archive::detail` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的 BSON 输入归档提供了标准实现，兼容 Boost.Serialization，支持类型注册、二进制包装、shared_ptr、自动 ID 跳过和序列化补丁，适用于高效的 BSON 数据反序列化场景。

