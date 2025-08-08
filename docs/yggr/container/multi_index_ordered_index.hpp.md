---
# 文件：multi_index_ordered_index.hpp

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil


本文件遵循MIT开源协议，允许自由使用、复制、修改、分发和再授权，但需保留版权声明和许可声明。文件按“原样”提供，不附带任何明示或暗示的担保。
```

## 文件概述

本头文件是 yggdrasil 容器库对 Boost.MultiIndex 有序索引（ordered_index）的适配与扩展，主要用于增强 Boost.MultiIndex 的有序索引功能，提供更好的兼容性、可移植性和便捷的接口封装，支持不同 Boost 版本和 C++ 标准下的有序索引操作。

## 主要内容

1. **头文件依赖**  
   - 依赖 yggdrasil 自身的 move、预处理宏、类型扩展、SFINAE、配置、节点句柄等模块。
   - 依赖 Boost.MultiIndex 的 ordered_index 及相关 MPL、类型特征工具。

2. **命名空间导入**  
   - 将 `boost::multi_index::ordered_unique` 和 `ordered_non_unique` 引入 `yggr::container` 命名空间，便于直接使用。

3. **emplace/emplace_hint 封装**  
   - 针对不同 C++ 标准（C++11 及以上的变参模板，或旧标准下的宏展开）和 Boost 版本，封装了 `emplace` 和 `emplace_hint` 方法，支持有序索引的高效原地构造插入。
   - 兼容 Boost 早期版本不支持 emplace 的情况，自动降级为 insert。

4. **节点句柄（node handle）相关操作**  
   - 对 Boost 1.74.0 之前的版本，提供了 extract（节点提取）和 insert（节点插入）接口，支持节点级别的高效移动和插入操作，便于容器间元素迁移。
   - 通过 reinterpret_cast 及 hacking 技巧，兼容 Boost 内部实现的差异。

5. **宏与元编程支持**  
   - 利用宏和预处理展开，支持不同参数数量的 emplace/emplace_hint 重载，兼容无变参模板的编译环境。
   - 提供 YGGR_PP_CONTAINER_RANGE_SIZE_SUPPORT 宏，扩展 ordered_index 的范围大小支持。

## 典型使用场景

- 需要在 yggdrasil 框架下使用 Boost.MultiIndex 的有序索引，并希望获得更好的跨版本兼容性和接口一致性。
- 需要在 C++11 及以上标准下高效地原地构造插入元素（emplace），或在旧标准下自动降级为 insert。
- 需要支持节点句柄（node handle）操作，实现容器间元素的高效迁移（如 extract/insert）。
- 需要对 Boost.MultiIndex 的 ordered_index 进行进一步的元编程扩展。

## 主要接口说明

- `emplace` / `emplace_hint`  
  支持变参模板和宏展开两种方式，自动适配 Boost 版本和 C++ 标准，原地构造插入元素。

- `extract`  
  从有序索引中提取节点，返回节点句柄，便于后续插入到其他容器。

- `insert`  
  支持节点句柄的插入，兼容 Boost 1.74.0 之前的实现。

- `ordered_unique` / `ordered_non_unique`  
  直接引入 Boost.MultiIndex 的有序唯一/非唯一索引类型。

## 示例代码

```cpp
#include <yggr/container/multi_index_ordered_index.hpp>
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
        ordered_unique<member<Person, int, &Person::id>>,
        ordered_non_unique<member<Person, std::string, &Person::name>>
    >
> person_set;

person_set ps;

// 原地构造插入（C++11及以上）
ps.get<0>().emplace(1, "Alice");

// 节点提取与插入（Boost 1.74.0及以下）
#if (BOOST_VERSION < 107400)
auto node = extract(ps.get<0>(), 1);
insert(ps.get<0>(), std::move(node));
#endif
```

## 注意事项

- 该头文件大量使用条件编译和宏，确保在不同 Boost 版本和 C++ 标准下都能正常工作。
- 节点句柄相关操作仅在 Boost 1.74.0 及以下版本有效，1.74.0 及以上请直接使用 Boost 官方接口。
- 依赖 yggdrasil 的预处理宏和类型工具，需确保相关头文件已正确包含。

---



