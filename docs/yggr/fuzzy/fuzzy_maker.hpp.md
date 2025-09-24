---
fuzzy_maker.hpp 文档

---

## 文件说明

**文件路径**fuzzy_maker.hpp


**版权**：Copyright (c) 2010-2024 yggdrasil  
**许可证**：MIT License

### 主要内容

本文件实现了一个通用的模糊字符串处理模板类 `fuzzy_maker`，支持多字符集、多分配器和正则表达式配置。  
通过静态成员函数，提供了正则表达式的生成、字符串的模糊过滤与替换等功能，支持自定义配置和分配器。

### 主要结构

- **yggr::fuzzy::fuzzy_maker\<Config\>**
  - 模板参数 `Config` 用于注入正则表达式和格式配置。
  - 继承自 `nonable::noncreateable`，不可实例化，仅提供静态接口。
  - `s_regex<Char>()`：返回指定字符类型的正则表达式对象。
  - `make_string(BiIter s, BiIter e)`：对迭代器区间进行模糊处理，返回处理结果。
  - `make_string(const Alloc& alloc, BiIter s, BiIter e)`：支持自定义分配器的模糊处理。
  - 支持 ICU（国际化）下的 Unicode 正则表达式处理（条件编译）。
  - 其他重载和辅助接口支持不同字符串类型和用法。

### 依赖

- yggrdef.h：基础类型定义。
- noncreateable.hpp：不可实例化基类。
- is_allocator.hpp、`allocator_t.hpp`：分配器相关工具。
- regex_parse.hpp：正则表达式处理。
- Boost.Regex 及相关 MPL 元编程工具。
- 可选 ICU 支持。

### 用法场景

用于字符串的模糊搜索、过滤、正则替换等场景，支持多字符集和自定义分配器，适合高性能和多样化需求的字符串处理。

---



