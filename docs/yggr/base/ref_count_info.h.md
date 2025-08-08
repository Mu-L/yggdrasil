---
# ref_count_info.h 文档

## 文件简介

ref_count_info.h 提供了一个通用的线程安全引用计数工具模板类 `ref_count_info`，用于管理对象的引用计数，支持原子操作。还提供了引用计数锁辅助类 `ref_count_info_locker` 以及一组便捷的比较操作符重载。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`
- `<boost/atomic.hpp>`

---

## 命名空间

- yggr

---

## 主要模板类

### yggr::ref_count_info

#### 模板参数

- `Val`：引用计数的数值类型，默认为 `yggr::u64`。

#### 主要类型定义

- `value_type`：引用计数的数值类型。
- `count_type`：`boost::atomic<value_type>`，用于原子操作的计数类型。

#### 构造与析构

- `ref_count_info()`：构造函数，初始化计数为 0。
- `ref_count_info(const this_type& right)`：拷贝构造函数，计数值取自参数对象。
- `~ref_count_info()`：析构函数。

#### 主要成员函数

- `this_type& operator=(const this_type& right)`  
  拷贝赋值，计数值取自参数对象。

- `value_type grab()`  
  原子性地增加计数，返回增加前的计数值。

- `value_type drop()`  
  原子性地减少计数，返回减少前的计数值。

- `void reset()`  
  计数重置为 0。

- `value_type use_count() const`  
  获取当前计数值。

- `bool empty() const`  
  判断计数是否为 0。

#### 成员变量

- `count_type _count`  
  当前引用计数。

---

## 比较操作符重载

支持 `==`, `!=`, `<`, `<=`, `>`, `>=` 六种比较操作，允许 `ref_count_info` 与任意类型或两个 `ref_count_info` 之间直接比较，比较的实际是 `use_count()` 的值。

---

## 辅助结构体

### yggr::ref_count_info_locker

- **模板参数**：`T`，引用计数类型。
- **构造函数**：`ref_count_info_locker(ref_count_type& rc)`，构造时 grab()，析构时 drop()，用于自动管理引用计数的增减，适合作用域锁定。

---

## 用法示例

````cpp
#include <yggr/base/ref_count_info.h>

yggr::ref_count_info<> ref_cnt;
ref_cnt.grab(); // 引用计数+1
ref_cnt.drop(); // 引用计数-1

if(ref_cnt.empty()) { /* 计数为0 */ }

yggr::ref_count_info_locker<yggr::ref_count_info<>> locker(ref_cnt); // 作用域内自动grab/drop
````

---

## 注意事项

- 所有 grab/drop/reset 操作均为原子操作，适合多线程环境。
- 支持与普通数值类型直接比较引用计数。
- `ref_count_info_locker` 适合用于作用域自动管理引用计数。

---

 

