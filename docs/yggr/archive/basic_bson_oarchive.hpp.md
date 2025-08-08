---
# 文件：basic_bson_oarchive.hpp

## 简介

该头文件定义了 BSON 格式序列化归档的基础模板类 `basic_bson_oarchive`，用于将 C++ 对象序列化为 BSON 数据。该类集成了 Boost.Serialization 框架，支持对 Boost 内部归档类型（如对象ID、版本、类名等）的写入，并提供了对自定义类型的扩展支持。

---

## 主要内容

### 1. 类模板 `basic_bson_oarchive`

```cpp
template<typename Archive>
class basic_bson_oarchive : public boost::archive::detail::common_oarchive<Archive>
{
    // 主要成员与方法见下文
};
```

#### 主要类型定义

- `archive_type`：归档类型模板参数
- `base_type`：基类，Boost 的通用输出归档
- `buf_type`：BSON 缓冲区类型（`nsql_database_system::c_bson`）
- `proxy_type`：BSON 访问代理
- `buf_inner_string_type`：BSON 内部字符串类型

#### 主要成员变量

- `_buf`：BSON 缓冲区的引用，用于存储序列化结果

#### 构造与析构

- `basic_bson_oarchive(buf_type& buf, unsigned int flags)`  
  构造函数，初始化缓冲区和归档标志。
- `~basic_bson_oarchive()`  
  析构函数。

#### 主要成员函数

- `save_override`  
  重载函数，支持 Boost 内部类型（如 object_id_type、version_type、class_id_type、class_name_type、tracking_type 等）的写入。
- `save_begin` / `save_end`  
  用于序列化流程中对象的开始与结束标记处理，支持多种字符串类型。
- 模板重载 `save_override`  
  支持自定义类型的序列化，要求类型满足 BSON 拼接特性（`is_bson_splice_t`）。
- `prv_save_override`  
  内部辅助函数，根据类型特性选择不同的序列化策略（区分内部类型和非内部类型）。

---

## 典型用法

该类通常作为 BSON 输出归档的基础，被具体归档类继承，用于实现自定义对象的序列化。例如：

```cpp
// 伪代码
nsql_database_system::c_bson bson_data;
my_bson_oarchive ar(bson_data, flags);
ar << my_object;
```

---

## 依赖与扩展

- 依赖 Boost.Serialization 框架
- 依赖 Yggdrasil 的 BSON 数据结构与访问代理
- 支持对 Boost 内部归档类型的自动处理
- 可扩展支持自定义类型的 BSON 序列化

---

## 命名空间

- 所有内容位于 `yggr::archive` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 BSON 格式的序列化提供了基础设施，兼容 Boost.Serialization，适用于需要将 C++ 对象保存为 BSON 数据的场景。

