# yggr/lua_wrap/wrap_foo_of_container.hpp 文档

## 文件概述

`wrap_foo_of_container.hpp` 提供了一组针对容器的通用操作函数包装，便于将 C++ STL/自定义容器的常用操作（如 size、resize、empty、clear、迭代器等）以统一接口导出到 Lua，实现容器在 Lua 脚本中的高效操作和遍历。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 容器通用操作函数
- **size/ssize/wraped_size/wraped_ssize**：获取容器元素数量，支持包装类型返回
- **resize**：调整容器大小，支持带初值重载
- **empty**：判断容器是否为空
- **clear**：清空容器
- **begin/end/cbegin/cend/rbegin/rend/crbegin/crend**：获取包装后的正/反向迭代器，支持常量和非常量版本

### 2. 主要接口说明
- `wrap_foo_size` / `wrap_foo_wraped_size`：返回容器元素数量，后者返回包装类型
- `wrap_foo_ssize` / `wrap_foo_wraped_ssize`：返回有符号元素数量，后者返回包装类型
- `wrap_foo_resize`：重设容器大小，支持带初值
- `wrap_foo_empty`：判断容器是否为空
- `wrap_foo_clear`：清空容器
- `wrap_foo_ref_begin`/`wrap_foo_cref_begin`/`wrap_foo_cbegin`/`wrap_foo_ref_end`/`wrap_foo_cref_end`/`wrap_foo_cend`：获取包装正向迭代器
- `wrap_foo_ref_rbegin`/`wrap_foo_cref_rbegin`/`wrap_foo_crbegin`/`wrap_foo_ref_rend`/`wrap_foo_cref_rend`/`wrap_foo_crend`：获取包装反向迭代器

### 3. 类型适配与包装
- 支持包装类型（如 `wrap_base_t`）和原生类型的自动适配
- 通过 `detail::unwrap_object` 实现类型解包，保证泛型兼容

## 依赖关系
- `yggr/container/size.hpp`、`resize.hpp`、`empty.hpp`、`clear.hpp`、`begin.hpp`、`end.hpp`、`rbegin.hpp`、`rend.hpp`
- `yggr/lua_wrap/wrap_base_t.hpp`、`detail/unwrap_t.hpp`
- Boost（type_traits、mpl 等）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_foo_of_container.hpp>
#include <vector>

std::vector<int> v = {1,2,3};
auto sz = yggr::lua_wrap::wrap_foo_size(v);
if (!yggr::lua_wrap::wrap_foo_empty(v)) {
    yggr::lua_wrap::wrap_foo_clear(v);
}
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
