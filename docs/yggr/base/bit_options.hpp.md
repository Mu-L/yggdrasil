---
# bit_options.hpp 文档

## 文件简介

bit_options.hpp 提供了一组用于按位操作选项（bit options/flags）的通用模板函数，支持检测、添加、移除、替换等常见位操作。适用于枚举类型或整型作为位掩码的场景，如权限、状态、配置标志等。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`

---

## 命名空间

- yggr

---

## 主要功能与接口

### 检查操作

- `has_bit_options(opts, chk)`  
  检查 `opts` 是否包含 `chk` 指定的所有位（全包含）。

- `has_bit_options_in(opts, chk)`  
  检查 `opts` 是否包含 `chk` 指定的任意一位（部分包含）。

- `check_bit_options(opts, chk)`  
  返回 `opts` 与 `chk` 的按位与结果。

### 移除（擦除）操作

- `erase_bit_options(opts, rm)`  
  从 `opts` 中移除 `rm` 指定的位。

- `erase_bit_options_if_exists(opts, chk, rm)`  
  仅当 `opts` 包含 `chk` 时，移除 `rm` 指定的位。

- `erase_bit_options_if_not_exists(opts, chk, rm)`  
  仅当 `opts` 不包含 `chk` 时，移除 `rm` 指定的位。

- `erase_bit_options_if_in(opts, chk)`  
  仅当 `opts` 与 `chk` 有交集时，移除 `chk` 指定的位。

- `erase_bit_options_if_in(opts, chk, rm)`  
  仅当 `opts` 与 `chk` 有交集时，移除 `rm` 指定的位。

- `erase_bit_options_if_not_in(opts, chk, rm)`  
  仅当 `opts` 与 `chk` 没有交集时，移除 `rm` 指定的位。

### 添加（追加）操作

- `append_bit_options(opts, add)`  
  向 `opts` 添加 `add` 指定的位。

- `append_bit_options_if_exists(opts, chk, add)`  
  仅当 `opts` 包含 `chk` 时，添加 `add` 指定的位。

- `append_bit_options_if_not_exists(opts, chk, add)`  
  仅当 `opts` 不包含 `chk` 时，添加 `add` 指定的位。

- `append_bit_options_if_in(opts, chk)`  
  仅当 `opts` 与 `chk` 有交集时，添加 `chk` 指定的位。

- `append_bit_options_if_not_in(opts, chk)`  
  仅当 `opts` 与 `chk` 没有交集时，添加 `chk` 指定的位。

- `append_bit_options_if_in(opts, chk, add)`  
  仅当 `opts` 与 `chk` 有交集时，添加 `add` 指定的位。

- `append_bit_options_if_not_in(opts, chk, add)`  
  仅当 `opts` 与 `chk` 有交集时，添加 `add` 指定的位。

### 替换操作

- `replace_bit_options(opts, rm, add)`  
  先移除 `rm` 指定的位，再添加 `add` 指定的位。

- `replace_bit_options_if_exists(opts, chk, add)`  
  仅当 `opts` 包含 `chk` 时，替换为 `add` 指定的位。

- `replace_bit_options_if_exists(opts, chk, rm, add)`  
  仅当 `opts` 包含 `chk` 时，移除 `rm` 并添加 `add`。

- `replace_bit_options_if_not_exists(opts, chk, rm, add)`  
  仅当 `opts` 不包含 `chk` 时，移除 `rm` 并添加 `add`。

- `replace_bit_options_if_in(opts, chk, add)`  
  仅当 `opts` 与 `chk` 有交集时，替换为 `add`。

- `replace_bit_options_if_not_in(opts, chk, add)`  
  仅当 `opts` 与 `chk` 有交集时，替换为 `add`。

- `replace_bit_options_if_in(opts, chk, rm, add)`  
  仅当 `opts` 与 `chk` 有交集时，移除 `rm` 并添加 `add`。

- `replace_bit_options_if_not_in(opts, chk, rm, add)`  
  仅当 `opts` 与 `chk` 没有交集时，移除 `rm` 并添加 `add`。

---

## 用法示例

````cpp
#include <yggr/base/bit_options.hpp>

enum MyFlags {
    FLAG_A = 0x01,
    FLAG_B = 0x02,
    FLAG_C = 0x04
};

int opts = FLAG_A | FLAG_B;

if (yggr::has_bit_options(opts, FLAG_A)) {
    opts = yggr::erase_bit_options(opts, FLAG_A);
}

opts = yggr::append_bit_options(opts, FLAG_C);
````

---

## 注意事项

- 所有函数均为模板，适用于整型、枚举等支持位运算的类型。
- 返回值均为新值，不会修改原参数。
- 推荐用于位掩码、标志位等场景，提升代码可读性和复用性。

---

 

