---
# 文件：basic_bson_iarchive.hpp

## 简介

该头文件定义了 BSON 格式反序列化归档的基础模板类 `basic_bson_iarchive`，用于从 BSON 数据流中读取和还原对象。该类集成了 Boost.Serialization 框架，支持对 Boost 内部归档类型（如对象ID、版本、类名等）的读取，并提供了对自定义类型的扩展支持。

---

## 主要内容

### 1. 类模板 `basic_bson_iarchive`

```cpp
template<typename Archive>
class basic_bson_iarchive : public boost::archive::detail::common_iarchive<Archive>
{
    // 主要成员与方法见下文
};
```

#### 主要类型定义

- `archive_type`：归档类型模板参数
- `base_type`：基类，Boost 的通用输入归档
- `buf_type`：BSON 缓冲区类型（`nsql_database_system::c_bson`）
- `proxy_type`：BSON 访问代理
- `buf_citer_type`：BSON 缓冲区常量迭代器
- `buf_inner_string_type`：BSON 内部字符串类型

#### 主要成员变量

- `_start`：当前读取位置的迭代器
- `_end`：缓冲区结束迭代器

#### 构造与析构

- `basic_bson_iarchive(const buf_type& buf, unsigned int flags)`  
  构造函数，初始化读取区间，并根据归档类型是否跳过自动ID进行调整。
- `~basic_bson_iarchive()`  
  析构函数。

#### 主要成员函数

- `load_override`  
  重载函数，支持 Boost 内部类型（如 object_id_type、version_type、class_id_type、class_name_type、tracking_type 等）的读取。
- `load_begin` / `load_end`  
  用于序列化流程中对象的开始与结束标记处理，支持多种字符串类型。
- `skip_override`  
  跳过特定类型的读取（如 class_id_type）。
- `prv_load_override`  
  内部辅助函数，根据类型特性选择不同的反序列化策略。
- 模板重载 `load_override`  
  支持自定义类型的反序列化，要求类型满足 BSON 拼接特性（`is_bson_splice_t`）。

---

## 典型用法

该类通常作为 BSON 输入归档的基础，被具体归档类继承，用于实现自定义对象的反序列化。例如：

```cpp
// 伪代码
nsql_database_system::c_bson bson_data = ...;
my_bson_iarchive ar(bson_data, flags);
ar >> my_object;
```

---

## 依赖与扩展

- 依赖 Boost.Serialization 框架
- 依赖 Yggdrasil 的 BSON 数据结构与访问代理
- 支持对 Boost 内部归档类型的自动处理
- 可扩展支持自定义类型的 BSON 反序列化

---

## 命名空间

- 所有内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 BSON 格式的反序列化提供了基础设施，兼容 Boost.Serialization，适用于需要将 BSON 数据还原为 C++ 对象的场景。

