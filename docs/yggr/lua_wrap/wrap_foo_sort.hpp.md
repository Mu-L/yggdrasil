# yggr/lua_wrap/wrap_foo_sort.hpp 文档

## 文件概述

`wrap_foo_sort.hpp` 提供了升序和降序排序算法包装函数 `wrap_foo_sort_aesc` 和 `wrap_foo_sort_desc`，用于在 Lua/C++ 交互中将 C++ STL 的 `std::sort` 算法以统一接口导出到 Lua，便于在 Lua 脚本中对容器区间进行排序操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 模板函数 `wrap_foo_sort_aesc`
- **定义**：
  ```cpp
  template<typename RandomIt>
  void wrap_foo_sort_aesc(RandomIt s, RandomIt e);
  ```
- **功能**：
  - 对 `[s, e)` 区间按升序排序。
  - 内部调用 `std::sort`，使用 `std::less` 比较器。

### 2. 模板函数 `wrap_foo_sort_desc`
- **定义**：
  ```cpp
  template<typename RandomIt>
  void wrap_foo_sort_desc(RandomIt s, RandomIt e);
  ```
- **功能**：
  - 对 `[s, e)` 区间按降序排序。
  - 内部调用 `std::sort`，使用 `std::greater` 比较器。

- **用途**：
  - 作为 Lua 绑定的排序算法接口，支持泛型容器和类型。

## 依赖关系
- `<algorithm>`（C++ 标准库 `std::sort`）
- `yggr/lua_wrap/detail/unwrap_t.hpp`
- `yggr/iterator_ex/iterator_traits.hpp`

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_foo_sort.hpp>
#include <vector>

std::vector<int> v = {3, 1, 2};
yggr::lua_wrap::wrap_foo_sort_aesc(v.begin(), v.end()); // v 变为 {1,2,3}
yggr::lua_wrap::wrap_foo_sort_desc(v.begin(), v.end()); // v 变为 {3,2,1}
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
