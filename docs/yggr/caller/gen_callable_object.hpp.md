---
# gen_callable_object.hpp

该头文件属于 yggdrasil 项目，实现了通用的可调用对象生成工具。其主要功能是根据传入对象的类型（指针或非指针），返回合适的可调用对象引用，便于统一处理函数指针、函数对象、lambda 等。

## 主要功能

- **gen_callable_object**：根据传入对象类型，返回合适的可调用对象引用。
  - 支持函数指针、函数对象、lambda 表达式等。
  - 自动处理指针类型和非指针类型的可调用对象。

## 主要接口

```cpp
template<typename F>
auto gen_callable_object(const F& f) -> ...;

template<typename F>
auto gen_callable_object(F& f) -> ...;
```

- **参数说明**：
  - `f`：可调用对象，可以是函数指针、函数对象、lambda 等。
- **返回值**：
  - 如果 `f` 是指针类型，返回其所指对象的引用（加 const 或不加 const，取决于参数）。
  - 如果 `f` 是非指针类型，返回其自身的引用（加 const 或不加 const，取决于参数）。

## 实现细节

- 使用 `boost::enable_if` 和 `boost::mpl` 进行类型萃取和 SFINAE 限制。
- 对于指针类型，使用 `boost::remove_pointer` 获取实际类型，并返回引用。
- 对于非指针类型，直接返回引用。
- 通过 `is_callable` 判断对象是否为可调用对象。

## 典型用法

```cpp
void foo(int) {}
auto f1 = &foo;
auto& callable1 = yggr::caller::gen_callable_object(f1); // 返回 foo 的引用

auto lambda = [](int x) { return x + 1; };
auto& callable2 = yggr::caller::gen_callable_object(lambda); // 返回 lambda 的引用
```

## 依赖

- yggrdef.h
- is_callable.hpp
- Boost.TypeTraits、Boost.MPL、Boost.Utility

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法或扩展说明，请参考源代码注释和 yggdrasil 项目文档。

