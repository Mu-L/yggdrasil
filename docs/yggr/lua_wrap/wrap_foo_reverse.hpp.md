# yggr/lua_wrap/wrap_foo_reverse.hpp 文档

## 文件概述

`wrap_foo_reverse.hpp` 提供了一个泛型反转算法包装函数 `wrap_foo_reverse`，用于在 Lua/C++ 交互中将 C++ STL 的 `std::reverse` 算法以统一接口导出到 Lua，便于在 Lua 脚本中对容器区间进行原地反转操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 模板函数 `wrap_foo_reverse`
- **定义**：
  ```cpp
  template<typename BidirIt>
  void wrap_foo_reverse(BidirIt s, BidirIt e);
  ```
- **功能**：
  - 对 `[s, e)` 区间执行原地反转操作。
  - 实现直接调用 `std::reverse`，与 STL 行为一致。
- **用途**：
  - 作为 Lua 绑定的反转算法接口，支持泛型容器和类型。

## 依赖关系
- `<algorithm>`（C++ 标准库 `std::reverse`）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_foo_reverse.hpp>
#include <vector>

std::vector<int> v = {1, 2, 3};
yggr::lua_wrap::wrap_foo_reverse(v.begin(), v.end()); // v 变为 {3,2,1}
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
