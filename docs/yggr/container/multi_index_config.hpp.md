---
# multi_index_config.hpp 文档

## 概述

`multi_index_config.hpp` 是 yggdrasil 项目中用于适配 Boost.MultiIndex 不同版本特性的配置头文件。该文件通过检测 Boost 版本，自动定义一系列宏，标记当前 Boost.MultiIndex 是否支持 emplace、shrink_to_fit、哈希索引比较器、ranked_index、6参数 ordered_index 等特性，便于后续代码根据这些特性进行条件编译和兼容性处理。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含基础定义头文件 `<yggr/base/yggrdef.h>`。
- 根据 Boost 版本号，自动定义以下特性宏：
  - `YGGR_BOOST_MULTI_INDEX_HAS_EMPLACE`：Boost >= 1.55.0 时支持 emplace
  - `YGGR_BOOST_MULTI_INDEX_HAS_SHRINK_TO_FIT`：Boost >= 1.55.0 时支持 shrink_to_fit
  - `YGGR_BOOST_MULTI_INDEX_HASHED_INDEX_HAS_COMPARER`：Boost >= 1.56.0 时哈希索引支持比较器
  - `YGGR_BOOST_MULTI_INDEX_HAS_RANKED_INDEX`：Boost >= 1.59.0 时支持 ranked_index
  - `YGGR_BOOST_MULTI_INDEX_ARGS6_VER_ORDERED_INDEX`：Boost >= 1.59.0 时 ordered_index 支持 6 个参数
- 这些宏可用于后续多索引容器相关代码的条件编译，提升兼容性和可移植性。

## 适用场景

- 需要在不同 Boost 版本下，自动适配 Boost.MultiIndex 新特性或兼容性差异的场景。
- 泛型容器、模板库开发中对 Boost.MultiIndex 特性检测的需求。

## 使用示例

```cpp
#include <yggr/container/multi_index_config.hpp>

#ifdef YGGR_BOOST_MULTI_INDEX_HAS_EMPLACE
// 使用 emplace 相关代码
#endif
```

---

本文件为 yggdrasil 容器适配体系的 Boost.MultiIndex 版本特性检测与配置组件，便于在模板库和泛型容器开发中统一处理多索引容器的特性兼容性。

