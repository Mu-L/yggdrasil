---
filter_string.hpp 文档

---

## 文件说明

**文件路径**filter_string.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件定义了模糊字符串过滤的主类型 `filter_string`，用于统一封装字符串模糊匹配与过滤相关功能。  
通过类型别名，将 `fuzzy_maker<filter_string_config>` 封装为 `filter_string`，便于直接使用。

### 主要结构

- **yggr::fuzzy::filter_string**
  - 类型定义：`typedef fuzzy_maker<filter_string_config> filter_string;`
  - 依赖于 `filter_string_config` 提供的正则表达式配置和 `fuzzy_maker` 的模糊匹配实现。
- 文件注释建议所有函数调用应使用 try-catch 进行异常处理，捕获 `filter_string::error_type`。

### 依赖

- yggrdef.h：基础类型定义。
- filter_string_config.hpp：正则表达式配置。
- fuzzy_maker.hpp：模糊匹配实现。

### 用法场景

用于字符串的模糊搜索、过滤等场景，支持正则表达式配置和异常安全调用。

---



