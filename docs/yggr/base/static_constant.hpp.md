---
# static_constant.hpp 文档

## 文件简介

static_constant.hpp 为 Yggdrasil 工程提供了跨平台、跨编译器的静态常量宏 `YGGR_STATIC_CONSTANT`，用于在类或结构体中安全、统一地声明静态常量。该文件自动适配 GCC 和其他主流编译器，保证静态常量声明的兼容性和可移植性。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`
- 依赖 Boost 的 `BOOST_STATIC_CONSTANT` 宏

---

## 主要内容

### 1. 宏定义

- **YGGR_STATIC_CONSTANT(type, assignment)**  
  用于在类、结构体或命名空间中声明静态常量。  
  - 在 GCC 下，宏展开为 `enum { assignment }`，避免 GCC 某些版本下的静态常量模板实例化问题。
  - 在其他编译器下，宏等价于 Boost 的 `BOOST_STATIC_CONSTANT`，即 `static const type assignment;`。

#### 示例

````cpp
struct Foo {
    YGGR_STATIC_CONSTANT(int, value = 42);
};
````

等价于（GCC 下）：
```cpp
struct Foo {
    enum { value = 42 };
};
```
或（其他编译器下）：
```cpp
struct Foo {
    static const int value = 42;
};
```

---

## 用法说明

- 推荐在模板类、结构体等需要静态常量的场景下统一使用该宏，保证跨平台兼容性。
- 可用于枚举值、模板参数、常量表达式等多种用途。

---

## 注意事项

- 宏会根据编译器自动适配，无需手动干预。
- 需先包含 `<yggr/base/yggrdef.h>`。

---

 

