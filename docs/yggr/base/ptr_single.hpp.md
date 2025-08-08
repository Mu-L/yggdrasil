---
# ptr_single.hpp 文档

## 文件简介

ptr_single.hpp 提供了一个线程安全的单例智能指针模板类 `yggr::ptr_single`，用于全局唯一对象的懒加载与安全访问。支持多种构造参数，兼容 C++11 可变参数模板和旧标准下的多参数重载。适用于需要全局唯一实例且线程安全的场景，如配置管理器、资源池等。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`
- `<yggr/base/static_constant.hpp>`
- `<yggr/bind/bind.hpp>`
- `<yggr/move/move.hpp>`
- `<yggr/smart_ptr_ex/shared_ptr.hpp>`
- `<yggr/nonable/noncreateable.hpp>`
- `<yggr/ppex/foo_params.hpp>`
- `<yggr/safe_container/safe_wrap.hpp>`
- `<boost/weak_ptr.hpp>`
- `<boost/shared_mutex.hpp>`

---

## 命名空间

- yggr

---

## 主要模板类

### yggr::ptr_single<T, Mutex, ver>

#### 模板参数

- `T`：单例对象类型。
- `Mutex`：用于线程安全的互斥量类型，默认为 `boost::shared_mutex`。
- `ver`：版本号，默认为 0。

#### 类型定义

- `obj_type` / `value_type`：对象类型 `T`
- `obj_ptr_type`：`shared_ptr<T>`，对象的智能指针类型
- `obj_weak_ptr_type`：`weak_ptr<T>`，对象的弱引用类型
- `version_type`：`yggr::u32`，版本号类型

#### 主要静态方法

- `get_ins()`  
  获取单例对象的 `shared_ptr`。

- `get_weak_ins()`  
  获取单例对象的 `weak_ptr`。

- `init_ins(const obj_ptr_type& ptr)`  
  用已有的智能指针初始化单例对象。

- `init_ins(Args&&... args)`  
  使用参数构造并初始化单例对象（C++11 可变参数模板）。

- `init_ins_d(D&& d, Args&&... args)`  
  支持带自定义分配器或删除器的初始化。

- `init_ins_da(D&& d, A&& a, Args&&... args)`  
  支持带自定义分配器和参数的初始化。

- `uninstall()`  
  卸载并销毁单例对象。

- `version()`  
  获取当前单例模板的版本号。

#### 内部机制

- 使用 `safe_wrap` 包装对象，保证多线程安全。
- 通过静态局部变量实现单例，懒加载。
- 支持自定义构造参数、分配器、删除器等。

---

## 用法示例

````cpp
#include <yggr/base/ptr_single.hpp>

struct Config {
    int value;
    Config(int v) : value(v) {}
};

// 初始化单例对象
auto ptr = yggr::ptr_single<Config>::init_ins(42);

// 获取单例对象
auto shared = yggr::ptr_single<Config>::get_ins();
if (shared) {
    std::cout << shared->value << std::endl;
}

// 卸载单例对象
yggr::ptr_single<Config>::uninstall();
````

---

## 注意事项

- 禁止实例化（继承自 `nonable::noncreateable`），只能通过静态方法访问。
- 支持多参数构造，兼容 C++11 及更早标准。
- 单例对象在 `uninstall()` 后会被销毁，需谨慎管理生命周期。
- 线程安全，适合多线程环境下的全局对象管理。

---

 

