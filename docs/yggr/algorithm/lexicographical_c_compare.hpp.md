---
# lexicographical_c_compare.hpp 文档

该头文件实现了泛型的字典序比较（lexicographical compare）算法，支持高效的内存块比较和自定义比较器。适用于二进制数据、容器、指针等多种场景，兼容 C++98/03/11。

---

## 命名空间

- **yggr::algorithm**  
  算法实现主命名空间。
- **yggr::algorithm::detail**  
  内部实现细节。
- **yggr**  
  通过 using 声明将主要类型和函数引入全局命名空间。

---

## 主要类型与结构体

- **c_cmp**  
  默认比较器，返回 -1/0/1，分别表示小于/等于/大于。
- **c_hex_cmp**  
  以无符号类型进行比较，适合十六进制或字节数据。
- **c_mem_cmp**  
  标记类型，用于内存块比较。
- **memcmpable**  
  类型萃取结构体，判断两种迭代器类型是否可以直接用 memcmp 比较。

---

## 主要函数

### lexicographical_c_compare

#### 作用

对两个区间进行字典序比较，返回：
- 0：区间内容相等
- -1：第一个区间小于第二个区间
- 1：第一个区间大于第二个区间

#### 重载

- `lexicographical_c_compare(iter1_s, iter1_e, iter2_s, iter2_e)`  
  使用默认比较器 `c_cmp`。
- `lexicographical_c_compare(iter1_s, iter1_e, iter2_s, iter2_e, cmp)`  
  使用自定义比较器。

#### 内部机制

- 对于可直接内存比较的区间（如指针、无符号类型、随机访问迭代器），自动调用 `memcmp`，大幅提升效率。
- 对于不支持内存比较的类型，逐元素调用比较器进行比较。
- 支持自定义比较器（如 `c_hex_cmp`、`c_mem_cmp` 等）。

#### 用法示例

```cpp
#include <yggr/algorithm/lexicographical_c_compare.hpp>
#include <vector>
std::vector<unsigned char> a = {1, 2, 3};
std::vector<unsigned char> b = {1, 2, 4};
int result = yggr::lexicographical_c_compare(a.begin(), a.end(), b.begin(), b.end());
// result == -1
```

---

## 其他说明

- 依赖于 Yggdrasil 框架的类型萃取、字节工具、迭代器工具等。
- 针对不同类型自动选择最优比较方式，兼容性和性能兼顾。
- 支持 boost 的类型萃取和 enable_if/disable_if 技术。

---

## 版权声明

MIT License，详见文件头部注释。

---

## 适用场景

- 二进制数据、字节流的高效比较。
- 容器、指针等多种类型的泛型字典序比较。
- 需要自定义比较规则的场景。

---

如需进一步了解具体用法，请参考相关的 Yggdrasil 框架文档或示例代码。

