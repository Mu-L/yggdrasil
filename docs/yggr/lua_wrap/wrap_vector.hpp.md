# wrap_vector.hpp 文档

## 文件概述

`wrap_vector.hpp` 提供了 C++ STL `vector` 容器的通用包装类 `wrap_vector`，用于将 vector 及其相关操作安全、便捷地导出到 Lua 脚本环境。该包装支持多种构造、赋值、迭代、元素访问、修改、比较、swap 及流输出等操作，兼容自定义分配器和多种 vector 变体。

## 命名空间结构

- `yggr`
  - `lua_wrap`
    - `detail`
    - `swap_support`

## 主要内容

### 1. 类型与模板结构
- `wrap_vector<Val, Ax, Vector>`：主包装模板，支持自定义元素类型、分配器和 vector 实现。
- 类型萃取：`is_wrap_vector` 用于类型判断。
- 支持多种构造方式，包括：
  - 默认、分配器、区间、拷贝、移动、initializer_list 等。
  - 支持不同分配器/底层 vector 类型的兼容构造与赋值。

### 2. 主要成员与接口
- 元素访问：`at`、`operator[]`、`front`、`back`、`data`。
- 迭代器：`begin`、`end`、`rbegin`、`rend` 及其 const/wrap 版本，支持导出到 Lua。
- 容量管理：`empty`、`size`、`max_size`、`capacity`、`reserve`、`shrink_to_fit`、`resize`。
- 修改操作：`clear`、`insert`、`erase`、`push_back`、`pop_back`、`emplace`、`emplace_back`。
- 分配器访问：`get_allocator`、`get_wraped_allocator`。
- 赋值与拷贝：支持多种 vector 变体、分配器、initializer_list。
- swap 支持：与原生 vector、其他 wrap_vector 变体高效交换。
- 比较与流输出：重载 `==`、`!=`、`<`、`<=`、`>`、`>=` 及 `operator<<`。

### 3. Lua 导出友好
- 提供 wrap 版本的迭代器、分配器、区间操作，便于 Lua 脚本端安全访问和操作。
- 支持类型安全的下标、区间、容量等参数传递。

### 4. 依赖关系
- 依赖 `container::vector`、`wrap_base_t`、`wrap_allocator`、`wrap_random_access_iterator`、`wrap_reverse_iterator` 等自定义包装与工具。
- 使用 Boost MPL、Type Traits、enable_if/disable_if、move/copy/swap、assert、宏展开等。

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_vector.hpp>
#include <vector>

yggr::lua_wrap::wrap_vector<int> wvec;
wvec.push_back(42);
int val = wvec[0];

// Lua 脚本中可通过导出接口访问和操作 wvec
```

## 典型场景
- 导出 STL vector 到 Lua，支持脚本端遍历、访问、修改、容量管理等。
- 需要类型安全、可扩展的容器包装以适配不同分配器和自定义 vector 类型。

## License
详见项目根目录下 LICENSE 文件。
