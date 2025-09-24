# yggr/lua_wrap/wrap_foo_shuffle.hpp 文档

## 文件概述

`wrap_foo_shuffle.hpp` 提供了一个泛型洗牌算法包装函数 `wrap_foo_shuffle`，用于在 Lua/C++ 交互中将 C++ STL/自定义的 `shuffle` 算法以统一接口导出到 Lua，便于在 Lua 脚本中对容器区间进行随机重排操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 模板函数 `wrap_foo_shuffle`
- **定义**：
  ```cpp
  template<typename RandomIt>
  void wrap_foo_shuffle(RandomIt s, RandomIt e);
  ```
- **功能**：
  - 对 `[s, e)` 区间执行原地随机重排（洗牌）操作。
  - 实现直接调用 `algorithm::shuffle`，可兼容自定义算法实现。
- **用途**：
  - 作为 Lua 绑定的洗牌算法接口，支持泛型容器和类型。

## 依赖关系
- `yggr/algorithm/shuffle.hpp`（自定义或兼容 STL 的洗牌算法）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_foo_shuffle.hpp>
#include <vector>

std::vector<int> v = {1, 2, 3};
yggr::lua_wrap::wrap_foo_shuffle(v.begin(), v.end()); // v 顺序被打乱
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
