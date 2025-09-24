---
GitHub Copilot: ids_parsers.hpp 文档

---

# 文件：ids_parsers.hpp

## 版权声明
- 版权所有 (c) 2010-2024 yggdrasil

- 采用 MIT 许可协议，允许自由使用、复制、修改、分发等。

## 主要内容

### 1. Boost.MultiIndex 相关别名
- 引入并重命名了 Boost.MultiIndex 的常用 key extractor，如 `identity`、`member`、`mem_fun`、`composite_key` 等，便于ID索引和解析。

### 2. 类型信息解析工具
- `use_typeid_name`：获取类型名（typeid(Obj).name()），支持自定义返回类型。
- `use_object_typeid_name`：通过对象成员函数获取类型信息名。
- `use_typeid`：直接获取类型的 `type_info`。

### 3. 类型解析注册器
- `reg_type_parser`：用于注册和调用类型解析器，支持模板调用。

### 4. 宏定义
- 提供一系列宏，简化 Boost.MultiIndex 及类型解析相关操作，如 `YGGR_IDS_PARSER_MEMBER`、`YGGR_IDS_PARSER_USE_TYPEID_NAME` 等。

### 5. 依赖
- 依赖 Yggdrasil 基础类型、Boost.MultiIndex、typeinfo、模板元编程等。

---

## 用途说明
本文件为Yggdrasil系统提供了ID类型的辅助解析工具，便于在多索引容器、类型注册、反射等场景下进行类型信息提取和索引操作。



