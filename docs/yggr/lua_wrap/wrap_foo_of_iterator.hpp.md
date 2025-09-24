# yggr/lua_wrap/wrap_foo_of_iterator.hpp 文档

## 文件概述

`wrap_foo_of_iterator.hpp` 提供了一组针对迭代器的通用操作函数包装，便于将 C++ STL/自定义迭代器的常用操作（如 advance、distance、next、prev 等）以统一接口导出到 Lua，实现迭代器在 Lua 脚本中的高效移动和距离计算。

## 命名空间结构

- `yggr`
  - `lua_wrap`
    - `detail`

## 主要内容

### 1. 迭代器通用操作函数
- **wrap_foo_advance**：对迭代器原地前进/后退 n 步
- **wrap_foo_advance_copy**：返回前进/后退 n 步后的新迭代器
- **wrap_foo_distance / wrap_foo_wraped_distance**：计算两个迭代器间距离，支持包装类型返回
- **wrap_foo_next / wrap_foo_prev**：获取前进/后退 n 步后的新迭代器

### 2. 类型适配与包装
- 支持包装类型（如 `wrap_base_t`）和原生类型的自动适配
- 通过 `detail::advance_distance_unpacker` 实现类型解包，保证泛型兼容

## 依赖关系
- `yggr/iterator_ex/iterator_traits.hpp`、`iterator.hpp`、`is_const_iterator.hpp`
- `yggr/lua_wrap/wrap_base_t.hpp`、`detail/unwrap_t.hpp`
- Boost（type_traits、mpl 等）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_foo_of_iterator.hpp>
#include <vector>

std::vector<int> v = {1,2,3,4,5};
auto it = v.begin();
yggr::lua_wrap::wrap_foo_advance(it, 2); // it 前进2步
int dist = yggr::lua_wrap::wrap_foo_distance(v.begin(), v.end());
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
