# yggr/lua_wrap/wrap_deque.hpp 文档

## 文件概述

`wrap_deque.hpp` 提供了通用的双端队列包装器 `wrap_deque`，用于将 C++ STL/自定义容器的 `deque` 适配导出到 Lua 环境，实现容器的构造、赋值、元素访问、迭代、修改、分配器管理等操作，并支持与 Lua 侧的高效交互。

## 命名空间结构

- `yggr`
  - `lua_wrap`
    - `detail`

## 主要内容

### 1. 模板类 `wrap_deque<Val, Ax, Deque>`
- **功能**：包装任意 `Deque<Val, Ax>` 类型，提供标准容器接口，支持 Lua 导出。
- **主要成员类型**：
  - `base_type`、`allocator_type`、`value_type`、`size_type`、`iterator`、`reverse_iterator` 等
  - 包装类型：`wrap_allocator_type`、`wrap_iterator_type`、`wrap_const_iterator_type`、`wrap_reverse_iterator_type`、`wrap_const_reverse_iterator_type`
- **主要成员函数**：
  - 多种构造/拷贝/赋值/析构，支持分配器、区间、initializer_list 等多种初始化方式
  - `unwrap()` 获取底层容器，`copy()` 拷贝自身
  - `assign()` 支持多种方式批量赋值
  - `get_allocator()`/`get_wraped_allocator()` 获取分配器
  - `at()`/`operator[]`/`front()`/`back()` 元素访问
  - `begin()`/`end()`/`rbegin()`/`rend()`/`cbegin()`/`cend()`/`crbegin()`/`crend()` 迭代器
  - `empty()`/`size()`/`max_size()`/`resize()`/`clear()`/`swap()`/`insert()`/`erase()`/`push_back()`/`pop_back()`/`push_front()`/`pop_front()`/`shrink_to_fit()` 等容器操作
- **类型安全**：
  - 静态断言保证模板参数为合法容器类型

### 2. 类型萃取与特化
- `detail::is_wrap_deque<T>`：类型萃取工具

### 3. 全局操作符重载与辅助
- 支持与原生容器、包装器的赋值、比较、swap 等操作
- 支持流输出

## 依赖关系
- `yggr/container/deque.hpp`、`wrap_allocator.hpp`、`wrap_random_access_iterator.hpp`、`wrap_reverse_iterator.hpp`
- Boost（enable_if、mpl、type_traits 等）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_deque.hpp>
#include <deque>

yggr::lua_wrap::wrap_deque<int> dq1;
dq1.push_back(42);
int val = dq1.front();
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
