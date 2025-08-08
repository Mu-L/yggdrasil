---
# inc_ver.h 文档

## 文件简介

inc_ver.h 定义了一个自增版本号类 `inc_ver`，用于线程安全地管理和递增64位无符号整数版本号。该类适用于需要版本控制或乐观锁等场景。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`
- `<yggr/move/move.hpp>`
- `<yggr/mplex/limits.hpp>`
- `<yggr/support/operator_t.hpp>`
- `<boost/ref.hpp>`
- `<boost/atomic.hpp>`

---

## 类定义

### yggr::inc_ver

#### 类型定义

- `value_type`：类型为 `u64`，即 64 位无符号整数。
- `ver_type`：类型为 `boost::atomic<value_type>`，用于原子操作的版本号。
- `numeric_limits_type`：用于获取 `value_type` 的数值极限。

#### 构造与析构

- `inc_ver()`：构造函数，初始化版本号为 0。
- `inc_ver(BOOST_RV_REF(this_type) right)`：移动构造函数。
- `inc_ver(const this_type& right)`：拷贝构造函数。
- `~inc_ver()`：析构函数。

#### 赋值操作

- `operator=(BOOST_RV_REF(this_type) right)`：移动赋值操作符，线程安全地赋值。
- `operator=(const this_type& right)`：拷贝赋值操作符，线程安全地赋值。

#### 主要成员函数

- `u64 grab(void) const`  
  原子性地将版本号加一（若未溢出），返回递增前的版本号。若已达最大值则回绕为 0。

- `u64 now_ver(void) const`  
  获取当前版本号。

- `operator bool(void) const`  
  判断当前版本号是否为非零。

- `operator u64(void) const`  
  隐式转换为 `u64`，返回当前版本号。

#### 成员变量

- `mutable ver_type _ver`  
  版本号，支持原子操作。

---

## 线程安全

所有对 `_ver` 的操作均通过 `boost::atomic` 实现，确保多线程环境下的安全性。

---

## 用法示例

````cpp
#include <yggr/base/inc_ver.h>

yggr::inc_ver ver;
u64 old_ver = ver.grab(); // 递增版本号
u64 current = ver.now_ver(); // 获取当前版本号
if(ver) { /* 版本号非零 */ }
````

---

## 注意事项

- 版本号达到最大值时会回绕为 0。
- 赋值和递增操作均为线程安全。

---

 

