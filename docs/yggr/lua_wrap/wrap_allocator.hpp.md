# yggr/lua_wrap/wrap_allocator.hpp 文档

## 文件概述

`wrap_allocator.hpp` 提供了一个通用的分配器包装器 `wrap_allocator`，用于将 C++ 分配器类型适配到 Lua 环境，便于在 Lua 脚本中安全、透明地操作 C++ 容器的分配器。该包装器支持分配器的构造、拷贝、比较、分配/释放、对象构造/析构等常用操作，并通过类型萃取和静态断言保证类型安全。

## 命名空间结构

- `yggr`
  - `lua_wrap`
    - `detail`

## 主要内容

### 1. 模板类 `wrap_allocator<TAlloc>`
- **功能**：包装任意符合 allocator 概念的类型，提供标准分配器接口，并可导出到 Lua。
- **主要成员类型**：
  - `value_type`、`pointer`、`const_pointer`、`reference`、`const_reference`、`size_type`、`difference_type` 等
- **主要成员函数**：
  - 构造/拷贝/析构
  - `unwrap()`：获取底层分配器引用
  - `get_allocator()`、`copy()`：Lua 友好接口
  - `address()`、`allocate()`、`deallocate()`、`max_size()`、`construct()`、`destroy()`
  - `compare_eq()`：分配器相等性比较
- **类型安全**：
  - 使用 `BOOST_MPL_ASSERT` 静态断言，确保模板参数为合法分配器类型

### 2. 类型萃取与特化
- `detail::is_wrap_allocator<T>`：类型萃取工具，用于判断类型是否为 `wrap_allocator` 实例

### 3. 非成员操作符重载
- `operator==`、`operator!=`：支持与原生分配器及其他 `wrap_allocator` 的相等/不等比较
- `operator<<`：支持输出到流（输出对象地址）

## 依赖关系
- `yggr/container_ex/allocator_traits.hpp`
- `yggr/container_ex/is_allocator.hpp`
- `yggr/lua_wrap/detail/unwrap_t.hpp`
- `yggr/lua_wrap/detail/luabind_function_noexcept.hpp`
- `yggr/lua_wrap/wrap_base_t.hpp`
- Boost（类型萃取、enable_if、addressof 等）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_allocator.hpp>
#include <vector>

// 包装 std::allocator 并导出到 Lua
using MyAlloc = yggr::lua_wrap::wrap_allocator<std::allocator<int>>;

// C++ 侧注册到 Lua
// luabind::module(L)[ ... ]

// Lua 侧可通过 get_allocator、copy 等接口访问
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
