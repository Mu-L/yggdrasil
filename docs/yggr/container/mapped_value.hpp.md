---
# mapped_value.hpp 文档

## 概述

`mapped_value.hpp` 是 yggdrasil 项目中用于通用容器元素“映射值”和“映射键”访问的辅助头文件。该文件通过类型萃取和泛型工具，统一为 map、set、pair 及普通类型等容器元素提供 mapped_value（映射值）和 mapped_key（映射键）的获取接口，便于泛型算法和容器操作中安全、统一地访问元素的 value 或 key。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含基础定义、pair、类型萃取、适配器等相关头文件。
- 在 `yggr::container::detail` 命名空间下实现 `mapped_value_helper` 和 `mapped_key_helper`，根据容器是否为“映射容器”自动选择访问 pair 的第二项（value）或第一项（key），否则直接返回对象本身。
- 提供泛型接口 `mapped_value<Container, T>(T&)` 和 `mapped_key<Container, T>(T&)`，自动根据容器类型和元素类型返回正确的 value 或 key 引用。
- 支持常量和非常量版本。
- 将 `mapped_value` 和 `mapped_key` 提升到 yggr 命名空间，便于全局统一调用。

## 适用场景

- 需要在泛型算法或容器操作中，统一访问 map、set、pair、普通类型等容器元素的 value 或 key。
- 需要屏蔽容器类型差异，提升代码复用性和可维护性的场景。

## 使用示例

```cpp
#include <yggr/container/mapped_value.hpp>

std::map<int, std::string>::value_type p = {1, "hello"};
auto& v = yggr::mapped_value<std::map<int, std::string>>(p); // 获取 value
auto& k = yggr::mapped_key<std::map<int, std::string>>(p);   // 获取 key
```

---

本文件为 yggdrasil 容器适配体系的元素访问辅助组件，便于在模板库和泛型容器开发中统一处理容器元素的 value/key 访问。

