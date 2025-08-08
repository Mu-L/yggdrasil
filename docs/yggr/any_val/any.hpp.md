---
# 文件：any.hpp

## 简介

any.hpp 是 yggdrasil 项目中实现类型安全的通用容器 `yggr::any` 的核心头文件。`yggr::any` 类允许存储任意类型的对象，并在运行时安全地进行类型查询和转换，类似于 `boost::any`，但结合了自定义的内存管理和序列化支持。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改、分发和商业用途，但需保留原作者版权声明和许可信息。

 <!-- ## 作者 -->

 <!-- - xu yang -->

## 主要内容

- 头文件保护宏，防止重复包含。
- 包含类型特征、序列化、内存管理、类型工具等相关依赖。
- 定义了 `yggr::any` 类，实现任意类型的存储、拷贝、移动、类型查询、类型安全转换等功能。
- 提供了类型安全的 `any_cast` 和 `unsafe_any_cast` 工具函数。
- 支持序列化和反序列化。
- 提供了异常类型 `yggr::bad_any_cast`，用于类型转换失败时抛出。
- 支持与标准库和 Boost 的 `swap` 机制集成。

## 主要类与函数

### 1. `yggr::any`

- 支持存储任意类型的对象。
- 支持拷贝构造、移动构造、赋值、移动赋值、swap 等操作。
- 提供 `empty()` 判断是否有内容，`type()` 查询存储类型。
- 内部采用小对象优化（Small Object Optimization），提升性能。
- 支持序列化（通过 Boost.Serialization）。

### 2. `yggr::any_cast` 和 `yggr::unsafe_any_cast`

- `any_cast<T>(any&)`：类型安全地将 `any` 转换为指定类型，类型不匹配时抛出 `bad_any_cast`。
- `unsafe_any_cast<T>(any&)`：不进行类型检查，直接转换，适合已知类型场景。

### 3. `yggr::bad_any_cast`

- 继承自 `std::bad_cast`，用于类型转换失败时抛出异常。

### 4. swap 支持

- 提供 `swap` 支持，可与标准库和 Boost 的 `swap` 机制无缝集成。

## 用法示例

```cpp
#include <yggr/any_val/any.hpp>

yggr::any a = 10;
int value = yggr::any_cast<int>(a); // value == 10

a = std::string("hello");
std::string str = yggr::any_cast<std::string>(a); // str == "hello"

// 类型不匹配时抛出异常
try {
    double d = yggr::any_cast<double>(a);
} catch(const yggr::bad_any_cast& e) {
    // 处理类型转换失败
}
```

## 依赖

- Boost.TypeTraits、Boost.Serialization、Boost.TypeIndex 等 Boost 组件
- yggdrasil 项目相关基础设施

---

如需详细功能和实现细节，请参考本文件实现及相关依赖头文件。

