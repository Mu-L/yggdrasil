---
# basic_string_adp_helper.hpp 文档

该头文件为 `std::basic_string` 和 `boost::container::basic_string` 提供了适配器辅助函数，统一了两者在 assign、insert、replace、find 等操作上的行为，尤其在内存区域重叠时保证语义一致。此文件主要用于解决不同 string 实现（如 STL 与 Boost.Container）在某些边界情况下行为不一致的问题。

---

## 主要内容

### 1. assign 系列函数

- **功能**：为字符串对象赋值，支持多种参数类型（字符、C 字符串、子串、迭代器、initializer_list 等）。
- **适用类型**：`std::basic_string` 和 `boost::container::basic_string`
- **特殊处理**：对于 boost::container::basic_string，若赋值区域与自身重叠，做了特殊内存处理，保证行为与 STL string 一致。

### 2. insert 系列函数

- **功能**：在字符串指定位置插入内容，支持插入字符、C 字符串、子串、迭代器区间、initializer_list 等。
- **适用类型**：`std::basic_string` 和 `boost::container::basic_string`
- **特殊处理**：对于 boost::container::basic_string，插入时若插入内容与自身重叠，采用临时缓冲区和内存移动，防止数据错乱。

### 3. replace 系列函数

- **功能**：替换字符串指定区域内容，支持替换为字符、C 字符串、子串、迭代器区间、initializer_list 等。
- **适用类型**：`std::basic_string` 和 `boost::container::basic_string`
- **特殊处理**：对于 boost::container::basic_string，替换时若内容重叠，采用内存拷贝和移动，保证替换后内容正确。

### 4. find 系列函数

- **功能**：查找字符、C 字符串、子串等在字符串中的位置。
- **适用类型**：`std::basic_string` 和 `boost::container::basic_string`
- **特殊处理**：对空字符串查找的行为做了统一（STL string 查找空串返回 0，Boost string 返回 npos）。

---

## 设计说明

- **统一语义**：为不同 string 实现提供一致的接口和行为，尤其在内存重叠、边界条件下。
- **异常安全**：在越界或非法操作时抛出 `std::out_of_range` 异常。
- **泛型编程**：大量使用模板和 SFINAE，支持多种类型和迭代器。
- **C++11 支持**：部分接口支持 initializer_list（可通过宏控制）。

---

## 典型用法

```cpp
std::string s = "hello";
yggr::charset::basic_string_assign(s, "world"); // s = "world"

boost::container::string bs = "abc";
yggr::charset::basic_string_replace(bs, 1, 1, "xyz", 3); // bs = "axyzc"
```

---

## 注意事项

- 该文件依赖于 yggr 框架的类型定义、工具宏、迭代器 traits 等。
- 仅适用于 `std::basic_string` 和 `boost::container::basic_string`，不适用于其他 string 实现。
- 若使用 C++11 及以上，部分接口可用 initializer_list。

---

## 版权声明

MIT License，详见文件头部注释。

---

如需详细 API 说明，请查阅每个函数的注释或源码实现。

