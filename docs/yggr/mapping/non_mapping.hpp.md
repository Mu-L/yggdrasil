# non_mapping.hpp 文档

## 文件概述

`non_mapping.hpp` 定义了一个空实现的“映射”结构 `non_mapping`，用于在泛型/模板代码中作为“无映射”或“占位”类型使用。该类型实现了常见的映射接口，但所有操作均为无效操作或返回默认值，适合用作禁用映射功能的场景。

## 命名空间结构

- `yggr`
  - `mapping`

## 主要内容

### 1. 结构体 `non_mapping`
- 构造与析构：
  - `non_mapping()` 默认构造，无操作。
  - `~non_mapping()` 析构，无操作。
- 基本方法：
  - `void clear()`：无操作。
  - `std::size_t size() const`：返回 0。
  - `std::size_t mapping_value_size() const`：返回 0。
  - `static std::size_t s_mapping_value_size()`：返回 0。
- 数据操作：
  - `bool append(const Val&)`：始终返回 true。
  - `bool remove(const Key&)`（支持模板参数 Tag 或 size_type）：始终返回 true。
  - `bool modify(const Key1&, const Key2&)`（支持模板参数 Tag/size_type）：始终返回 true。
  - `std::pair<Key, bool> mapping_value(const Key&) const`（支持模板参数 Tag/size_type）：返回 {key, true}。
- 静态方法：
  - `static s32 create_tag_object()`：返回 0。

### 2. 设计意图
- 作为泛型代码中的“空映射”类型，屏蔽所有映射相关操作。
- 保证接口兼容性，便于模板参数切换。
- 所有操作均为无副作用的空实现。

## 依赖关系
- 依赖 `<yggr/base/yggrdef.h>` 基础类型定义。
- 仅使用标准类型和简单模板。

## 用法示例

```cpp
#include <yggr/mapping/non_mapping.hpp>

yggr::mapping::non_mapping nm;
nm.append(123); // 返回 true，但无实际操作
size_t sz = nm.size(); // 始终为 0
```

## 典型场景
- 需要在模板代码中禁用映射功能时作为占位类型。
- 用于泛型容器、数据结构的“无映射”实现。

## License
详见项目根目录下 LICENSE 文件。
