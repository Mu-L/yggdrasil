# yggr/lua_wrap/wrap_bidirectional_iterator.hpp 文档

## 文件概述

`wrap_bidirectional_iterator.hpp` 提供了双向迭代器包装器 `wrap_bidirectional_iterator` 和 `wrap_bidirectional_const_iterator`，用于将 C++ STL/自定义容器的双向迭代器安全导出到 Lua 环境，实现迭代器的移动、解引用、比较、赋值、交换等操作，并支持与原生迭代器的无缝互操作。

## 命名空间结构

- `yggr`
  - `lua_wrap`
    - `detail`
    - `swap_support`

## 主要内容

### 1. 模板类 `wrap_bidirectional_iterator<TIter>`
- **功能**：包装任意双向迭代器，提供标准迭代器接口，支持 Lua 导出。
- **主要成员类型**：
  - `base_type`、`value_type`、`iterator_category`、`pointer`、`difference_type`、`reference`
- **主要成员函数**：
  - 构造/拷贝/析构/赋值/交换
  - `unwrap()` 获取底层迭代器
  - `get_value()`/`set_value()` 访问和设置元素
  - `head_increment`/`tail_increment`/`head_decrement`/`tail_decrement` 支持前后移动
  - `compare_eq()` 比较
  - `next()`/`prev()` 快捷移动
  - `operator->` 支持成员访问
- **类型安全**：
  - 静态断言保证模板参数为双向迭代器

### 2. 模板类 `wrap_bidirectional_const_iterator<TIter>`
- **功能**：包装任意双向迭代器为只读迭代器，接口与上类似，但元素访问为只读
- **主要成员函数**：同上，部分接口为 const

### 3. 类型萃取与特化
- `detail::is_wrap_bidirectional_iterator<T>`、`is_wrap_bidirectional_const_iterator<T>`：类型萃取工具

### 4. 全局操作符重载
- 支持 *、++、--、==、!=、<< 等标准迭代器操作
- 支持与原生迭代器、包装器的混合比较
- 支持流输出
- 支持 swap（std/boost/自定义）

## 依赖关系
- `yggr/iterator_ex/iterator_traits.hpp`、`iterator.hpp`、`iterator_category_check.hpp`
- `yggr/lua_wrap/wrap_base_t.hpp`
- Boost（enable_if、mpl、type_traits 等）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_bidirectional_iterator.hpp>
#include <list>

std::list<int> lst = {1,2,3};
using Iter = std::list<int>::iterator;
yggr::lua_wrap::wrap_bidirectional_iterator<Iter> it(lst.begin());
++it;
int val = *it;
```

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
