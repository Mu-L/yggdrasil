---
# obj_creator.hpp 文档

## 文件简介

obj_creator.hpp 提供了一个通用的对象静态工厂模板 `yggr::obj_creator`，用于统一和简化对象的创建流程。支持普通对象和 `void` 特化，兼容 C++11 可变参数模板和旧标准下的多参数构造。还提供了便捷的全局工厂函数接口，适合在泛型编程、工厂模式、单例等场景下使用。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`
- `<yggr/nonable/noncreateable.hpp>`
- `<yggr/ppex/foo_params.hpp>`
- `<boost/type_traits/add_reference.hpp>`
- `<boost/type_traits/add_const.hpp>`
- Boost 预处理器相关宏

---

## 命名空间

- yggr

---

## 主要类与接口

### 1. 模板类 `yggr::obj_creator<T>`

- **功能**：禁止实例化，仅提供静态成员函数用于对象创建。
- **类型定义**：
  - `value_type`：对象类型 `T`
  - `reference_type`：`T&`
  - `const_reference_type`：`const T&`
  - `create_result_type`：返回值类型（一般为 `T`）
  - `static_create_result_type`：静态对象返回类型（`T&`）
  - `static_const_create_result_type`：静态常量对象返回类型（`const T&`）

- **主要静态成员函数**：
  - `create(...)`  
    创建一个临时对象并返回（按值返回）。
  - `static_create(...)`  
    创建或返回一个静态对象（单例），返回引用。
  - `static_const_create(...)`  
    创建或返回一个静态常量对象，返回常量引用。

- **参数支持**：
  - C++11 及以上：支持任意参数个数（可变参数模板）。
  - 旧标准：通过 Boost 预处理器宏支持多参数重载。

### 2. `yggr::obj_creator<void>` 特化

- 针对 `void` 类型的特化，所有成员函数均为空实现（用于泛型兼容）。

### 3. 全局工厂函数

- `create_object<T>(...)`  
  等价于 `obj_creator<T>::create(...)`
- `static_create_object<T>(...)`  
  等价于 `obj_creator<T>::static_create(...)`
- `static_const_create_object<T>(...)`  
  等价于 `obj_creator<T>::static_const_create(...)`
- 支持可变参数模板或多参数重载。

---

## 用法示例

````cpp
#include <yggr/base/obj_creator.hpp>

struct Foo {
    Foo(int a, double b) : x(a), y(b) {}
    int x;
    double y;
};

// 创建临时对象
Foo f = yggr::obj_creator<Foo>::create(1, 2.0);

// 获取静态对象（单例）
Foo& f_static = yggr::obj_creator<Foo>::static_create(3, 4.0);

// 全局工厂函数用法
auto f2 = yggr::create_object<Foo>(5, 6.0);
````

---

## 注意事项

- 该工厂模板禁止实例化，仅能通过静态成员函数调用。
- 静态对象（`static_create`/`static_const_create`）每种参数组合只会构造一次，适合单例或缓存场景。
- 兼容 C++11 及更早标准，参数数量受限于 `YGGR_PP_FOO_DEFAULT_PARAMS_LEN` 宏设置。

---

 

