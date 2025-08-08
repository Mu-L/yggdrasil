---
# 文件：bson_serialize_mark.hpp

## 简介

该头文件定义了 Yggdrasil 框架下 BSON 序列化过程中的标记类型，用于标识 BSON 序列化时数组的起始和结束。通过这些标记类型，可以在归档实现中明确区分数组结构的边界，提升序列化/反序列化的类型安全性和可读性。

---

## 主要内容

### 1. 类定义

#### `bson_serialize_mark`

```cpp
class bson_serialize_mark
{
public:
    struct bson_mark_array_start {};
    struct bson_mark_array_end {};
};
```

- **用途**：作为 BSON 序列化过程中的辅助标记类型。
- **成员结构体**：
  - `bson_mark_array_start`：表示数组序列化的起始标记。
  - `bson_mark_array_end`：表示数组序列化的结束标记。

这些结构体通常在 BSON 归档实现中被用作类型标记，以便在序列化和反序列化时正确处理数组边界。

---

## 命名空间

- 所有内容位于 `yggr::archive` 命名空间下。

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 BSON 序列化过程提供了数组边界的类型安全标记，是 BSON 归档实现中处理复杂结构的基础工具。

