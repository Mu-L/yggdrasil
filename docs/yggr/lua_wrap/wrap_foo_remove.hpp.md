# yggr/lua_wrap/wrap_foo_remove.hpp 文档

## 文件概述

`wrap_foo_remove.hpp` 提供了一个泛型移除算法包装函数 `wrap_foo_remove`，用于在 Lua/C++ 交互中将 C++ STL 的 `std::remove` 算法以统一接口导出到 Lua，便于在 Lua 脚本中对容器区间进行元素移除操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 模板函数 `wrap_foo_remove`
- **定义**：
  ```cpp
  template<typename ForwardIt, typename T>
  ForwardIt wrap_foo_remove(ForwardIt s, ForwardIt e, const T& val);
  ```
- **功能**：
  - 对 `[s, e)` 区间执行移除操作，返回移除后新逻辑结尾的迭代器。
  - 实现直接调用 `std::remove`，与 STL 行为一致。
- **用途**：
  - 作为 Lua 绑定的移除算法接口，支持泛型容器和类型。

## 依赖关系
- `<algorithm>`（C++ 标准库 `std::remove`）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_foo_remove.hpp>
#include <vector>

std::vector<int> v = {1, 2, 3, 2};
auto it = yggr::lua_wrap::wrap_foo_remove(v.begin(), v.end(), 2);
v.erase(it, v.end()); // 真正移除元素
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
