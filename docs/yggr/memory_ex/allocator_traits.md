# `allocator_traits.hpp` 文档

## 概述

`yggr/memory_ex/allocator_traits.hpp` 提供了一个兼容 Boost 容器分配器的 traits 扩展，主要用于统一和扩展分配器（Allocator）的特性检测与类型萃取，便于泛型容器或内存管理组件自动适配不同分配器的特性。

该文件的核心是 `yggr::memory_ex::allocator_traits` 模板结构体，它在继承 `boost::container::allocator_traits` 的基础上，增加了对 `segment_manager` 和 `version` 类型的自动检测与萃取。

## 文件位置

- 源文件：`yggr/memory_ex/allocator_traits.hpp`
- 本文档：`docs/allocator_traits.md`

## 主要类型与结构

### 1. `allocator_traits<Alloc>`

- 继承自 `boost::container::allocator_traits<Alloc>`。
- 默认定义：
  - `typedef mplex::null_type segment_manager;`（无 segment_manager 时为 null_type）
  - `typedef boost::container::dtl::version_type<Alloc, 0> version;`（或低版本 Boost 用 `container_detail` 命名空间）

### 2. 偏特化 `allocator_traits< TPLAlloc<T1, T2> >`

- 用于适配形如 `SomeAllocator<T1, T2>` 的模板分配器。
- 自动检测并萃取：
  - `segment_manager`：如果分配器类型定义了 `segment_manager`，则提取其类型，否则为 `null_type`。
  - `version`：如果分配器类型定义了 `version`，则提取其类型，否则为 `boost::container::dtl::version_type<Alloc, 0>`。

### 3. 辅助 traits 检测结构

- `has_segment_manager_t<T>`：检测类型 T 是否有 `segment_manager` 成员类型。
- `allocator_segment_manager_t<T>`：根据检测结果萃取 `segment_manager` 类型或为 `null_type`。
- `has_version_t<T>`：检测类型 T 是否有 `version` 成员类型。
- `allocator_version_t<T>`：根据检测结果萃取 `version` 类型或为默认。

这些检测均采用 SFINAE 技术和 `sizeof` trick 实现。

## 用法示例

```cpp
#include <yggr/memory_ex/allocator_traits.hpp>
#include <boost/container/vector.hpp>

// 假设有自定义分配器 MyAlloc<T, SegmentManager>

using namespace yggr::memory_ex;

// 获取分配器的 segment_manager 类型
using seg_mgr_type = allocator_traits< MyAlloc<int, MySegMgr> >::segment_manager;

// 获取分配器的 version 类型
using version_type = allocator_traits< MyAlloc<int, MySegMgr> >::version;

// 兼容 boost::container::vector
boost::container::vector<int, MyAlloc<int, MySegMgr>> vec;
```

## 注意事项

1. **Boost 版本兼容性**：
   - `version` 类型的定义根据 Boost 版本自动切换命名空间（`container_detail` vs `dtl`）。
   - 若项目升级 Boost，需确认 `BOOST_VERSION` 宏的定义与实际一致。
2. **SFINAE 检测**：
   - traits 检测依赖于类型成员的存在性，若分配器未定义 `segment_manager` 或 `version`，则自动回退为默认类型。
3. **泛型适配**：
   - 该 traits 设计用于泛型容器或内存池等场景，便于自动适配不同分配器的扩展特性。
4. **null_type**：
   - 当分配器不支持 `segment_manager` 时，`segment_manager` 类型为 `mplex::null_type`，可用作类型萃取的判别条件。

## 建议测试用例

- 针对有/无 `segment_manager` 和 `version` 成员的分配器类型，验证 `allocator_traits` 的类型萃取结果。
- 验证与 Boost 容器的兼容性（如 `boost::container::vector`、`boost::container::map` 等）。
- 升级 Boost 版本后，验证 `version` 类型的命名空间切换是否正确。

## 结语

`allocator_traits.hpp` 是一个面向泛型分配器适配的底层工具，适合需要支持多种分配器特性的高性能容器或内存管理组件。
