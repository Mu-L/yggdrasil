# wrap_reverse_iterator.hpp 文档

## 文件概述

`wrap_reverse_iterator.hpp` 主要用于将 C++ 的反向迭代器（reverse_iterator）包装为可导出到 Lua 的类型，便于在 Lua 脚本中安全、灵活地操作 C++ 容器的反向迭代器。该文件实现了通用的反向迭代器包装类、相关的类型萃取与操作工具，并支持丰富的运算符重载和类型特性。

## 命名空间结构
- `yggr`
  - `lua_wrap`
    - `detail`
    - `swap_support`

## 主要内容

### 1. 反向迭代器包装核心

#### `wrap_reverse_iterator_inner<TChild, TRIter, n_is_random_access>`
- 模板类，内部实现反向迭代器的包装。
- 支持随机访问和非随机访问两种迭代器，分别特化。
- 提供如下主要成员：
  - 构造与拷贝：支持多种迭代器类型的构造与转换。
  - `unwrap()`：获取底层迭代器。
  - `get_value()`/`set_value()`：获取/设置当前迭代器指向的值。
  - `plus`/`minus`/`plus_set`/`minus_set`：迭代器的前进/后退及其原地操作。
  - `compare`/`compare_eq`：与其他迭代器的比较。
  - `operator[]`/`at`：随机访问。
- 通过 SFINAE、类型萃取和 enable_if/disable_if 保证类型安全。

#### `wrap_reverse_iterator<TRIter>`
- 用户主用的反向迭代器包装类。
- 继承自 `wrap_reverse_iterator_inner`，自动根据迭代器类型选择特化。
- 支持赋值、swap、类型转换、拷贝、设置底层迭代器等操作。
- 便于导出到 Lua，支持常用的迭代器接口和运算符。

### 2. 非成员运算符重载
- `operator*`, `operator++`, `operator--`, `operator+`, `operator-`, `operator+=`, `operator-=` 等。
- 支持反向迭代器与数值、包装类型、其他迭代器的混合运算。
- `operator==`, `operator!=`, `operator<`, `operator<=`, `operator>`, `operator>=` 等比较运算符。
- `operator<<`：输出流支持。

### 3. swap 支持
- `swap_support` 命名空间下提供 `swap` 重载，支持标准库和 Boost 的 swap。
- 允许反向迭代器包装类型与原生迭代器、包装类型之间高效交换。

## 依赖关系
- 依赖 `iterator_ex`（自定义迭代器萃取与工具）、`detail::unwrap_t`、`detail::is_wrap_base_t`、`detail::riter_value_setter` 等。
- 使用 Boost MPL、Type Traits、enable_if/disable_if、assert 等。
- 依赖 `mplex::sfinae_type`、`YGGR_CONSTEXPR` 等自定义宏和类型。

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_reverse_iterator.hpp>
#include <vector>
#include <algorithm>

std::vector<int> v = {1, 2, 3, 4};
using riter_t = std::vector<int>::reverse_iterator;
yggr::lua_wrap::wrap_reverse_iterator<riter_t> riter(v.rbegin());

// 访问当前值
auto val = riter.get_value();
// 前进
++riter;
// 比较
if (riter == yggr::lua_wrap::wrap_reverse_iterator<riter_t>(v.rend())) {
    // 到达末尾
}
```

## 典型场景
- 导出 STL 容器的反向迭代器到 Lua，支持脚本端遍历、访问和修改容器内容。
- 需要类型安全、可扩展的迭代器包装以适配不同容器和自定义类型。

## License
详见项目根目录下 LICENSE 文件。
