---
filter_string_config.hpp 文档

---

## 文件说明

**文件路径**filter_string_config.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件定义了模糊字符串过滤相关的静态配置接口，主要用于正则表达式格式和字符串处理的统一配置。  
通过静态成员函数，提供了正则表达式格式字符串和过滤用正则表达式的获取接口，支持多字符类型。

### 主要结构

- **yggr::fuzzy::filter_string_config**
  - 继承自 `nonable::noncreateable`，不可实例化，仅提供静态接口。
  - `s_fmt<Char>()`：返回模糊匹配格式字符串，支持不同字符类型。
  - `s_str_re<Char>()`：返回用于字符串过滤的正则表达式，支持不同字符类型。

### 依赖

- yggrdef.h：基础类型定义。
- noncreateable.hpp：不可实例化基类。
- const_strings.hpp：常量字符串宏定义。

### 用法场景

用于模糊搜索、字符串过滤等场景，统一管理正则表达式格式和过滤规则，便于维护和多字符集支持。

---



