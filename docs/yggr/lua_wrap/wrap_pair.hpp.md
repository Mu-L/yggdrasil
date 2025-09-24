# yggr/lua_wrap/wrap_pair.hpp 文档

## 文件概述

`wrap_pair.hpp` 提供了通用的 pair 包装器 `wrap_pair`，用于将 C++ STL/自定义容器的 `pair` 适配导出到 Lua 环境，实现 pair 的构造、赋值、元素访问、比较、交换等操作，并支持与 Lua 侧的高效交互。

## 命名空间结构

- `yggr`
  - `lua_wrap`
    - `detail`
    - `swap_support`

## 主要内容

### 1. 模板类 `wrap_pair<First, Second, TPair>`
- **功能**：包装任意 `TPair<First, Second>` 类型，提供标准 pair 接口，支持 Lua 导出。
- **主要成员类型**：
  - `base_type`、`first_type`、`second_type`
- **主要成员函数**：
  - 多种构造/拷贝/赋值/析构，支持 pair、原生类型、包装类型等多种初始化方式
  - `unwrap()` 获取底层 pair，`copy()` 拷贝自身
  - `get_first()`/`get_second()` 获取元素，`set_first()`/`set_second()` 设置元素
  - `compare_eq()`/`compare()` 支持与原生 pair、包装器的等值和大小比较
  - `swap()` 支持与原生 pair、包装器的交换
- **类型安全**：
  - 静态断言保证模板参数为合法 pair 类型

### 2. 类型萃取与特化
- `detail::is_wrap_pair<T>`：类型萃取工具

### 3. 全局操作符重载与辅助
- 支持与原生 pair、包装器的 ==、!=、<、<=、>、>= 等比较操作
- 支持流输出
- 支持 swap（std/boost/自定义）
- 提供 `make_pair` 工具函数

## 依赖关系
- `yggr/utility/pair.hpp`、`type_traits/is_pair.hpp`
- Boost（enable_if、mpl、type_traits 等）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_pair.hpp>
#include <utility>

yggr::lua_wrap::wrap_pair<int, double> p1(1, 3.14);
auto f = p1.get_first();
p1.set_second(2.71);
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
