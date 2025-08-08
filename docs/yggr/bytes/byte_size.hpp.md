# byte_size.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了统一的字节数计算工具接口。通过引入 byte_size_detail.hpp，并将 `detail::byte_size` 导出到 `yggr::bytes` 命名空间和全局 yggr 命名空间，方便用户直接调用。

## 3. 头文件包含
- byte_size_detail.hpp：实际实现字节数计算逻辑的头文件。

## 4. 命名空间结构
- `yggr::bytes`：主命名空间，导出 `byte_size` 工具。
- yggr：全局命名空间，也导出 `byte_size`，便于直接使用。

## 5. 主要功能

- **byte_size**：用于计算对象、类型或数据结构所占用的字节数。具体实现和支持的类型需参考 `detail/byte_size_detail.hpp`，通常支持基础类型、数组、容器等。

## 6. 典型用法

```cpp
#include <yggr/bytes/byte_size.hpp>

int a = 10;
std::size_t size = yggr::byte_size(a); // 计算 int 类型的字节数

std::vector<char> buf(100);
std::size_t buf_size = yggr::byte_size(buf); // 计算 vector 占用的字节数
```

## 7. 总结

本文件为 Yggdrasil 框架提供了统一、简洁的字节数计算接口，便于在序列化、内存管理等场景下快速获取对象的字节大小。实际功能依赖于 `detail/byte_size_detail.hpp` 的实现。

---

alucard-dracula: 为这个模块生成文档

GitHub Copilot: 

# yggr/bytes 模块文档

## 1. 模块简介

bytes 模块为 Yggdrasil 框架提供了统一、灵活的**字节数计算工具**，可用于获取任意对象、数组、容器、模板类型等在内存中的实际占用字节数。该模块支持基础类型、标准容器、数组、pair、tuple 等多种常见类型，并可自动递归计算嵌套结构的字节大小，适用于序列化、内存分析、网络通信等场景。

---

## 2. 主要接口

### 2.1 byte_size

- **定义位置**：byte_size.hpp
- **接口说明**：  
  `byte_size` 是一个通用函数模板，可用于计算任意类型对象的字节数。  
  其实现位于 `yggr::bytes::detail` 命名空间，并通过 `using` 导出到 `yggr::bytes` 及全局 yggr 命名空间，方便直接调用。

- **用法示例**：

    ```cpp
    #include <yggr/bytes/byte_size.hpp>
    int a = 10;
    std::size_t sz = yggr::byte_size(a); // 计算int类型的字节数

    std::vector<double> v(100);
    std::size_t v_sz = yggr::byte_size(v); // 计算vector占用的字节数
    ```

- **支持范围**：
  - 基础类型（int、double、char等）
  - 原生数组、boost::array、std::array
  - STL/Boost 容器（vector、list、map、set等）
  - std::pair、std::tuple
  - 只要类型实现了 `byte_size()` 成员函数或静态成员函数，也可自动适配

---

## 3. 结构与扩展

### 3.1 目录结构

- byte_size.hpp：主接口，导出 `byte_size` 工具
- `byte_size_sp_*.hpp`：为不同类型（如 array、container、tpl、utility、basic）提供特化支持
- `detail/byte_size_detail_*.hpp`：实现细节，包含对基础类型、数组、容器、模板、pair等的递归字节数计算逻辑

### 3.2 实现机制

- 采用模板元编程和类型萃取，自动判断类型特征，递归计算嵌套结构的字节数
- 支持自定义类型通过实现 `byte_size()` 成员函数或静态成员函数参与字节数计算
- 对于容器类型，自动遍历所有元素并累加其字节数
- 对于数组和 pair 等复合类型，递归计算每个成员的字节数

---

## 4. 典型用法

```cpp
#include <yggr/bytes/byte_size.hpp>
#include <vector>
#include <map>
#include <utility>

struct MyStruct {
    int a;
    double b;
    std::vector<char> buf;
    // 可选：实现 byte_size() 成员函数以自定义字节数计算
};

MyStruct s;
std::size_t sz = yggr::byte_size(s);

std::pair<int, std::vector<float>> p;
std::size_t p_sz = yggr::byte_size(p);

std::map<int, std::string> m;
std::size_t m_sz = yggr::byte_size(m);
```

---

## 5. 注意事项

- **递归计算**：对于嵌套容器或复合类型，`byte_size` 会递归计算所有子成员的字节数。
- **自定义类型**：如需自定义字节数计算逻辑，可为类型实现 `byte_size()` 成员函数或静态成员函数。
- **迭代器区间**：支持通过迭代器区间计算一段数据的总字节数。
- **性能**：对于大型容器或深度嵌套结构，递归计算可能带来一定性能开销。

---

## 6. 相关文件

- byte_size.hpp：主接口
- detail/byte_size_detail_basic.hpp：基础类型与递归实现
- detail/byte_size_detail_array.hpp：数组支持
- detail/byte_size_detail_container.hpp：容器支持
- detail/byte_size_detail_tpl.hpp：模板类型支持
- detail/byte_size_detail_utility.hpp：pair等工具类型支持

---

## 7. 总结

bytes 模块为 Yggdrasil 框架提供了强大、灵活的字节数计算能力，支持多种类型和自定义扩展，适合需要精确内存占用分析的各种 C++ 项目。只需包含主头文件，即可一键获取任意对象的字节大小。

