---
# new.hpp 文档

## 文件简介

new.hpp 为 Yggdrasil 工程提供了统一的 `new` 运算符宏定义，便于跨平台、跨标准地使用普通和不抛异常的 `new`。通过宏 `yggr_new` 和 `yggr_nothrow_new`，可以简化内存分配代码，并提升代码可读性和可维护性。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<new>`（C++ 标准头文件，提供 `std::nothrow`）

---

## 主要内容

### 1. 宏定义

- `yggr_new`  
  等价于标准的 `new` 运算符，用于普通内存分配。

- `yggr_nothrow_new`  
  等价于 `new (std::nothrow)`，用于不抛出异常的内存分配（分配失败时返回 `nullptr` 而不是抛出异常）。

### 2. 命名空间

- `namespace yggr { }`  
  预留命名空间，便于后续扩展。

---

## 用法示例

````cpp
#include <yggr/base/new.hpp>

int* p1 = yggr_new int;                // 普通new
int* p2 = yggr_nothrow_new int;        // 不抛异常的new

if (!p2) {
    // 分配失败处理
}
````

---

## 注意事项

- 推荐在 Yggdrasil 工程中统一使用 `yggr_new` 和 `yggr_nothrow_new`，便于后续全局替换或自定义内存分配策略。
- `yggr_nothrow_new` 分配失败时返回 `nullptr`，不会抛出 `std::bad_alloc` 异常。

---

 

