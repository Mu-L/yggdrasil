---
# 文件：bson_archive_helper.hpp

## 简介

该头文件定义了 Yggdrasil 框架下 BSON 归档辅助工具类 `bson_archive_helper`，用于简化 BSON 数据缓冲区的管理、对象的序列化与反序列化操作。该类为 BSON 归档提供了统一的缓冲区操作接口和异常安全的序列化流程，适用于基于 BSON 的数据交换和存储场景。

---

## 主要内容

### 1. 模板类 `bson_archive_helper`

```cpp
template<typename Archive>
class bson_archive_helper
{
    // 主要成员与方法见下文
};
```

#### 主要类型定义

- `archive_type`：归档类型模板参数
- `buf_type`：BSON 缓冲区类型（`nsql_database_system::c_bson`）
- `output_stream_type` / `input_stream_type`：输出/输入流类型，均为 BSON 缓冲区

---

#### 主要缓冲区操作

- **拷贝与移动**
  - `buf_copy(buf1, buf2)`：支持右值引用和常量引用的缓冲区拷贝/移动，自动避免自拷贝。
- **交换**
  - `buf_swap(buf1, buf2)`：交换两个缓冲区内容，自动避免自交换。
- **大小与状态**
  - `buf_size(buf)`：获取缓冲区大小
  - `buf_empty(buf)`：判断缓冲区是否为空
  - `buf_clear(buf)`：清空缓冲区
  - `buf_init(buf)`：初始化缓冲区
- **指针与比较**
  - `buf_real_val_ptr(buf)`：获取缓冲区真实值指针
  - `buf_val_ptr(buf)`：获取缓冲区值指针
  - `buf_compare(buf1, buf2)`：比较两个缓冲区内容是否相等

---

#### 缓冲区赋值

- `buf_assign(buf, args...)`：支持变参模板（C++11）或宏展开（C++03），将参数赋值到缓冲区。

---

#### 序列化与反序列化

- `save(const Object& obj, buf_type& buf)`  
  将对象序列化为 BSON 缓冲区，异常安全，支持 Boost 异常和系统异常处理。
- `load(boost::serialization::nvp<Object>& nvp, buf_type& buf)`  
  从 BSON 缓冲区反序列化带名字值对的对象，异常安全。
- `load(Object& obj, buf_type& buf)`  
  从 BSON 缓冲区反序列化对象，异常安全。

---

## 典型用法

```cpp
nsql_database_system::c_bson buf;
MyObject obj;

// 序列化
yggr::archive::archive_helper::bson_archive_helper<MyArchive>::save(obj, buf);

// 反序列化
yggr::archive::archive_helper::bson_archive_helper<MyArchive>::load(obj, buf);
```

---

## 设计特点

- 统一的缓冲区操作接口，便于归档代码复用
- 支持 C++11 变参模板和 C++03 宏展开
- 异常安全，自动处理 Boost 和系统异常
- 适配 Yggdrasil 的 BSON 数据结构

---

## 命名空间

- 所有内容位于 `yggr::archive::archive_helper` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的 BSON 归档提供了高效、类型安全的辅助工具，简化了缓冲区管理和对象序列化流程，适用于各种基于 BSON 的数据处理场景。

