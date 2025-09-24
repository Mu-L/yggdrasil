# yggr/lua_wrap/wrap_foo_find.hpp 文档

## 文件概述

`wrap_foo_find.hpp` 提供了一个泛型查找算法包装函数 `wrap_foo_find`，用于在 Lua/C++ 交互中将 C++ STL 的 `std::find` 算法以统一接口导出到 Lua，便于在 Lua 脚本中对容器进行元素查找操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 模板函数 `wrap_foo_find`
- **定义**：
  ```cpp
  template<typename InputIt, typename T>
  InputIt wrap_foo_find(InputIt s, InputIt e, const T& val);
  ```
- **功能**：
  - 对 `[s, e)` 区间执行线性查找，返回第一个等于 `val` 的迭代器。
  - 实现直接调用 `std::find`，与 STL 行为一致。
- **用途**：
  - 作为 Lua 绑定的查找算法接口，支持泛型容器和类型。

## 依赖关系
- `<algorithm>`（C++ 标准库 `std::find`）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_foo_find.hpp>
#include <vector>

std::vector<int> v = {1, 2, 3, 4};
auto it = yggr::lua_wrap::wrap_foo_find(v.begin(), v.end(), 3);
if (it != v.end()) { /* 找到元素 */ }
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
