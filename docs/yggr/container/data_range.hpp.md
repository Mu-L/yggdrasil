---
# data_range.hpp 文档

## 概述

`data_range.hpp` 提供了一个线程安全的数据区间管理类 `data_range`，用于维护一个可递增/递减的区间值，常用于分布式、并发或资源池等场景下的区间分配与回收。该类支持原子操作，能安全地在多线程环境下进行区间游标的前进与后退，并在越界时抛出自定义错误。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容

### 1. 头文件保护

防止重复包含。

### 2. 依赖

- `<yggr/base/error_make.hpp>`：自定义错误生成器
- `<boost/atomic.hpp>`：原子操作支持
- `<cassert>`：断言检查

### 3. data_range 类模板

#### 模板参数

- `T`：区间值类型，需支持比较、加减等操作。

#### 主要成员

- `value_type`：区间值类型别名
- `data_range(const value_type& start, const value_type& last)`：构造函数，指定区间起止
- `data_range(const value_type& start, const value_type& last, const value_type& now)`：指定当前值
- `is_in(const value_type& val)`：判断值是否在区间内（左闭右开）
- `is_not_in(const value_type& val)`：判断值是否不在区间内
- `left_limit()` / `right_limit()`：获取区间左右端点
- `now()`：获取当前值
- `reset()`：重置当前值为区间起点
- `next()`：原子递增当前值，返回递增前的值，超出右界抛出异常
- `before()`：原子递减当前值，返回递减前的值，超出左界抛出异常

#### 错误处理

- 内部定义了 `E_left_limited` 和 `E_right_limited` 两种错误码，分别表示越过左/右边界。

#### 线程安全

- 通过 `boost::atomic` 保证 `_now_val` 的原子性，支持多线程安全操作。

## 适用场景

- 并发环境下的区间分配、资源池管理、ID 生成等需要线程安全区间游标的场景。

## 使用示例

```cpp
yggr::container::data_range<int> dr(0, 100);
int v1 = dr.next();   // 获取下一个值
int v2 = dr.before(); // 获取上一个值
dr.reset();           // 重置为起点
```

---

如需扩展支持其他类型，请确保类型 T 支持必要的算术和比较操作。

