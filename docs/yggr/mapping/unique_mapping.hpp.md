# unique_mapping.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了一个多字段唯一映射容器 `unique_mapping`，支持通过多个字段（主键）唯一索引和高效查找。内部基于线程安全的多索引容器（safe_multi_index_container），可用于多主键唯一性的数据管理、映射、同步等场景。

## 3. 主要类型与功能

### 3.1 unique_mapping 模板类

#### 模板参数
- 多个字段类型（Val1, Val2, ...），支持变长模板参数或预处理器展开。
- Mutex：可选的互斥类型，用于线程安全。

#### 主要类型定义
- `value_type`：内部数据类型，通常为 `packet_info` 的多字段组合。
- `midx_cont_type`：底层线程安全多索引容器类型，支持多字段唯一索引。

#### 主要成员函数
- **构造与赋值**
  - 支持默认、拷贝、移动构造与赋值。
  - 支持 swap 操作（与同类型对象交换内容）。
- **基本操作**
  - `clear()`：清空容器。
  - `size()`：获取元素数量。
  - `empty()`：判断容器是否为空。
  - `mapping_value_size()`：获取映射值字段数量。
- **插入与强制插入**
  - `append()`：插入新元素，支持右值、左值和参数展开。
  - `compulsory_append()`：强制插入（如已存在则覆盖）。
  - `compulsory_exchange()`：强制交换（如已存在则交换）。
- **删除**
  - `remove()`：按指定字段删除元素，支持字段类型或索引。
- **查找**
  - `is_exists()`：判断指定字段值是否存在。
- **修改与交换**
  - `modify()`：根据一个字段查找并修改其它字段值，支持参数展开。
  - `exchange()`：根据一个字段查找并交换其它字段值，支持参数展开。
- **映射查询**
  - `mapping_value()`：根据一个字段查找另一个字段的值。
  - `mapping_other_values()`：查找除指定字段外的其它字段值，支持输出到容器。

#### 内部实现要点
- 利用 Boost.MultiIndex 和 safe_multi_index_container 实现多字段唯一索引。
- 支持变参模板和预处理器宏，兼容 C++11 及更早版本。
- 通过 `packet_info` 统一封装多字段数据。
- 支持回滚、强制修改、交换等高级操作，保证数据一致性。

### 3.2 swap 支持
- 提供 `swap_support::swap`，支持 unique_mapping 对象的高效交换。
- 将 swap 导入到 std、boost 命名空间，兼容标准库和 Boost 生态。

---

## 4. 典型用法

```cpp
#include <yggr/mapping/unique_mapping.hpp>

// 定义一个三字段唯一映射
typedef yggr::mapping::unique_mapping<int, std::string, double> my_mapping;

my_mapping map;
map.append(1, "hello", 3.14);
bool exists = map.is_exists<0>(1); // 按第一个字段查找
auto val = map.mapping_value<0, 1>(1); // 按第一个字段查找第二个字段的值
map.modify<0, 2>(1, 2.71); // 修改第三个字段
```

---

## 5. 设计要点

- **多主键唯一性**：支持多个字段作为唯一索引，适合多主键场景。
- **线程安全**：底层采用 safe_multi_index_container，适合多线程环境。
- **高效操作**：支持高效的查找、插入、修改、交换等操作。
- **灵活接口**：兼容变参模板和宏展开，适应不同 C++ 标准。
- **易于集成**：swap 支持标准库和 Boost，便于与其他容器协作。

---

## 6. 注意事项

- 字段类型和数量需在模板参数中指定，不能动态变更。
- 强制插入、交换等操作需确保数据一致性。
- 变参模板接口需 C++11 支持，老版本通过宏展开兼容。

---

## 7. 总结

本文件为 Yggdrasil 框架提供了功能强大的多字段唯一映射容器，适合多主键唯一性、高并发、高效查找与修改等复杂数据管理场景。其灵活的接口和高性能实现，适合在大型 C++ 项目中作为核心数据结构使用。

---

