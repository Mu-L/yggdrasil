---
# 文件：multi_index_ranked_index.hpp

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil


本文件遵循MIT开源协议，允许自由使用、复制、修改、分发和再授权，但需保留版权声明和许可声明。文件按“原样”提供，不附带任何明示或暗示的担保。
```

## 文件概述

本头文件是 yggdrasil 容器库对 Boost.MultiIndex ranked_index（有序排名索引）的适配与扩展，主要用于在 Boost 1.59 及以上版本下，便捷地使用 ranked_index 相关功能，并为 yggdrasil 框架提供统一的接口封装。

## 主要内容

1. **头文件依赖**  
   - 依赖 yggdrasil 的多项基础设施，包括预处理宏、类型扩展、SFINAE、ordered_index 适配、节点句柄 hacking 等。
   - 依赖 Boost.MultiIndex 的 ranked_index 及相关类型。

2. **条件编译与版本检测**  
   - 仅在定义了 `YGGR_BOOST_MULTI_INDEX_HAS_RANKED_INDEX`（即 Boost 版本 >= 1.59）时才允许编译和使用本模块，否则直接报错，防止低版本 Boost 环境下误用。

3. **命名空间导入**  
   - 将 `boost::multi_index::ranked_unique` 和 `ranked_non_unique` 引入 `yggr::container` 命名空间，便于直接使用。

4. **扩展与兼容性**  
   - 通过包含 `multi_index_ordered_index.hpp` 和节点 hacking 相关头文件，为 ranked_index 提供更好的兼容性和扩展能力，便于后续节点操作和元编程扩展。

## 典型使用场景

- 需要在 yggdrasil 框架下使用 Boost.MultiIndex 的 ranked_index（有序排名索引），并希望获得统一的接口风格和跨版本兼容性。
- 需要支持基于排名的高效元素访问、插入、删除等操作。
- 需要对 Boost.MultiIndex 的 ranked_index 进行进一步的元编程扩展或节点句柄操作。

## 主要接口说明

- `ranked_unique` / `ranked_non_unique`  
  直接引入 Boost.MultiIndex 的有序唯一/非唯一排名索引类型，支持基于排名的高效访问。

## 示例代码

```cpp
#include <yggr/container/multi_index_ranked_index.hpp>
#include <boost/multi_index_container.hpp>
#include <string>

struct Person {
    int id;
    std::string name;
};

using namespace yggr::container;
using namespace boost::multi_index;

typedef multi_index_container<
    Person,
    indexed_by<
        ranked_unique<member<Person, int, &Person::id>>
    >
> person_ranked_set;

person_ranked_set prs;

// 插入元素
prs.insert({1, "Alice"});
prs.insert({2, "Bob"});

// 基于排名访问
auto it = prs.get<0>().nth(1); // 获取排名为1的元素
if (it != prs.get<0>().end()) {
    // 使用 *it
}
```

## 注意事项

- 仅在 Boost 1.59 及以上版本可用，低版本会直接编译报错。
- 依赖 yggdrasil 的预处理宏和类型工具，需确保相关头文件已正确包含。
- 若需节点句柄相关操作，需结合 yggdrasil 的节点 hacking 支持。

---



