---
# string_hash.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 Boost.Container 字符串类型的哈希支持，便于在基于哈希的容器（如 `std::unordered_map`、`std::unordered_set`）中直接使用 `boost::container::basic_string` 作为键。它通过适配标准库的 `std::hash`，实现了与 STL 字符串一致的哈希行为。

---

## 主要内容

- **命名空间**：`std`
- **核心模板**：`std::hash<boost::container::basic_string<Char, Traits, Alloc>>`
- **依赖**：
  - string_decl.hpp：字符串类型声明
  - `boost/functional/hash.hpp`：Boost 哈希实现

---

## 主要功能

### 1. std::hash 特化

```cpp
template<typename Char, typename Traits, typename Alloc>
struct hash<boost::container::basic_string<Char, Traits, Alloc>>
{
    typedef boost::container::basic_string<Char, Traits, Alloc> type;

    inline std::size_t operator()(const type& str) const 
    {
        boost::hash<type> hasher; 
        return hasher(str); 
    }
};
```

- **功能**：为 `boost::container::basic_string` 提供标准哈希接口，允许其作为哈希容器的键。
- **实现机制**：内部调用 `boost::hash`，保证哈希行为与 Boost 一致。
- **启用条件**：仅在定义了 `YGGR_HAS_CXX11_STD_HASH` 宏时生效（即 C++11 及以上，且支持 `std::hash`）。

---

## 设计说明

- **兼容性**：解决 Boost 字符串类型在标准哈希容器中无法直接作为键的问题。
- **高效实现**：复用 Boost 的高效哈希算法，无需额外实现。
- **类型安全**：仅对 `boost::container::basic_string` 及其特化类型生效，不影响其他类型。

---

## 用法示例

```cpp
#include <yggr/charset/string_hash.hpp>
#include <boost/container/string.hpp>
#include <unordered_map>

std::unordered_map<boost::container::string, int> my_map;
my_map["hello"] = 42;
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型的哈希，请特化 `std::hash` 并实现对应哈希算法。详细用法和扩展方式请查阅源码与注释。

