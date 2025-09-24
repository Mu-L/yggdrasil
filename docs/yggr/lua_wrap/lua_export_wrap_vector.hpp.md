# yggr/lua_wrap/lua_export_wrap_vector.hpp 文档

## 文件概述

`lua_export_wrap_vector.hpp` 主要用于将 C++ 的 vector 包装器（wrap_vector）导出到 Lua，使其能够在 Lua 脚本中以类似 STL vector 的方式进行操作。该文件通过模板和 luabind 框架，自动为不同类型的 vector 包装器生成 Lua 绑定，包括构造、赋值、元素访问、迭代器、插入、删除等常用操作。

## 命名空间结构
- `yggr`
  - `lua_wrap`

## 主要内容

### 1. 模板函数 `export_wrap_vector`
- **模板参数**：
  - `WrapVector`：被包装的 vector 类型
  - `ClassType`：luabind::class_ 类型
  - `ValueType`：元素类型
  - `Allocator`：分配器类型
- **功能**：
  - 通过 luabind::class_，将 C++ 的 wrap_vector 相关方法导出到 Lua。
  - 支持多种构造函数、赋值、元素访问、迭代器、插入、删除、push_back、pop_back、resize 等操作。
  - 支持不同类型的迭代器（正向、反向、常量等）。
  - 通过静态断言确保类型安全。
- **主要绑定方法**：
  - 构造函数（默认、拷贝、带分配器等）
  - 赋值（operator=）
  - 比较（operator==, operator!=）
  - 元素访问（at, front, back, operator[]）
  - 迭代器（begin, end, rbegin, rend, cbegin, cend, crbegin, crend）
  - 容量相关（empty, size, max_size, reserve, capacity, shrink_to_fit, clear）
  - 修改器（insert, erase, push_back, pop_back, resize）

### 2. 类型萃取与静态断言
- 使用 `boost::is_same`、`boost::is_base_of` 等类型萃取工具，确保模板参数的正确性。
- 通过 `YGGR_STATIC_ASSERT` 保证类型安全。

### 3. 依赖与前置声明
- 依赖于 luabind、yggr 自身的容器包装器、boost 类型萃取等。
- 需要先包含相关的 wrap_vector、wrap_iterator、wrap_reverse_iterator 等头文件。

## 依赖关系
- `luabind/luabind.hpp`
- `yggr/lua_wrap/wrap_vector.hpp`
- `yggr/lua_wrap/wrap_iterator.hpp`
- `yggr/lua_wrap/wrap_reverse_iterator.hpp`
- `boost/type_traits/is_same.hpp`
- `boost/type_traits/is_base_of.hpp`

## 用法示例

```cpp
// C++ 侧注册：
#include <yggr/lua_wrap/lua_export_wrap_vector.hpp>

// 假设有 MyVector 包装器
luabind::module(L)
[
    yggr::lua_wrap::export_wrap_vector<MyVector>("MyVector")
];
```

```lua
-- Lua 侧使用：
local v = MyVector()
v:push_back(123)
print(v:size())
```

## 许可证
本文件遵循 yggdrasil 项目的开源许可证。
