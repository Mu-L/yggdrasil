---
# error.hpp 文档

## 文件简介

error.hpp 定义了 Yggdrasil 工程通用的错误对象类 `yggr::error`，用于封装错误码与错误信息，并支持拷贝、移动、交换等操作。该类便于在工程中统一管理和传递错误状态，支持与标准输出流集成，便于调试和日志记录。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`
- `<yggr/base/static_constant.hpp>`
- `<yggr/move/move.hpp>`
- `<yggr/utility/copy_or_move_or_swap.hpp>`
- `<yggr/support/operator_t.hpp>`
- `<ostream>`
- `<string>`

---

## 命名空间

- yggr

---

## 主要类

### yggr::error

#### 类型定义

- `err_string_type`：错误消息字符串类型，等价于 `std::string`。

#### 静态常量

- `E_unknown_error`：未知错误码，值为 `0xffffffff`。

#### 构造与析构

- `error()`  
  默认构造函数，错误码为 0，消息为空。
- `error(u32 code)`  
  指定错误码构造，消息为空。
- `error(u32 code, const err_string_type& msg)`  
  指定错误码和消息构造。
- `error(u32 code, const err_string_type& class_name, const err_string_type& other_msg, const err_string_type& msg)`  
  指定错误码、类名、附加消息和主消息构造。
- `error(const error& right)`  
  拷贝构造函数。
- `error(BOOST_RV_REF(error) right)`  
  移动构造函数。
- `~error()`  
  析构函数。

#### 赋值与交换

- `error& operator=(const error& right)`  
  拷贝赋值。
- `error& operator=(BOOST_RV_REF(error) right)`  
  移动赋值。
- `void swap(error& right)`  
  与另一个 `error` 对象交换内容。
- `void swap(BOOST_RV_REF(error) right)`  
  与右值 `error` 对象交换内容。

#### 成员函数

- `u32 code() const`  
  获取错误码。
- `const err_string_type& message() const`  
  获取错误消息。
- `const err_string_type& what() const`  
  获取错误消息（等价于 `message()`）。
- `explicit operator bool() const`  
  判断错误对象是否有效（错误码非 0 时为真）。

---

## 运算符重载

- `operator<<`  
  支持将 `error` 对象输出到标准输出流，格式为：
  ```
  code: <错误码>
  msg: <错误消息>
  ```

---

## 用法示例

````cpp
#include <yggr/base/error.hpp>

yggr::error err1; // 默认无错误
yggr::error err2(1001, "文件未找到");
if (err2) {
    std::cout << err2 << std::endl;
}
````

---

## 注意事项

- 错误码为 0 时，`error` 对象视为无错误。
- 支持拷贝、移动和交换，适合在容器、函数返回值等多种场景下使用。
- 推荐配合 `error_make.hpp` 的宏工具批量定义错误码和错误消息。

---

 

