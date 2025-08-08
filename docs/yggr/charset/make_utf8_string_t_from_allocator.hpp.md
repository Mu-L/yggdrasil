---
# make_utf8_string_t_from_allocator.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了根据分配器类型（Allocator）自动推导 UTF-8 字符串类型的工具模板。它可根据传入的分配器类型，自动生成合适的 `yggr::charset::utf8_string_impl` 类型，便于泛型编程和自定义内存管理场景下的 UTF-8 字符串类型适配。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心模板**：`make_utf8_string_t_from_allocator`

---

## 主要功能

### 1. make_utf8_string_t_from_allocator

```cpp
template<typename Alloc>
struct make_utf8_string_t_from_allocator;
```

- **功能**：根据分配器类型 `Alloc`，推导出合适的 UTF-8 字符串类型。
- **实现机制**：
  - 若 `Alloc` 满足 `container_ex::is_allocator<Alloc>::value == true`，则生成
    ```cpp
    yggr::charset::utf8_string_impl<
        value_type,
        traits_type,
        Alloc
    >
    ```
    其中 `value_type` 由 `allocator_traits<Alloc>::value_type` 推导，`traits_type` 由 `basic_string<value_type>::traits_type` 推导。
  - 若 `Alloc` 不是分配器类型，则默认类型为 `yggr::charset::utf8_string`。

### 2. 内部实现

- 通过 `detail::_make_utf8_string_t_from_allocator` 辅助模板实现 SFINAE 分派，保证类型安全和泛型兼容。

---

## 用法示例

```cpp
#include <yggr/charset/make_utf8_string_t_from_allocator.hpp>
#include <memory>

// 使用 std::allocator<char> 推导 UTF-8 字符串类型
typedef yggr::charset::make_utf8_string_t_from_allocator<std::allocator<char>>::type my_utf8_string_t;

// 使用非分配器类型，默认为 yggr::charset::utf8_string
typedef yggr::charset::make_utf8_string_t_from_allocator<int>::type default_utf8_string_t;
```

---

## 设计说明

- **类型安全**：通过 SFINAE 和 traits 保证只有分配器类型才会生成带自定义分配器的 UTF-8 字符串类型。
- **泛型友好**：便于在模板代码中根据分配器自动适配 UTF-8 字符串类型，支持自定义内存管理。
- **与 yggr 框架深度集成**：依赖于 `yggr::charset::utf8_string_impl`、`container_ex::allocator_traits` 等工具。

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义分配器或字符串类型，请特化相关 traits 或模板。详细用法和扩展方式请查阅源码与注释。

