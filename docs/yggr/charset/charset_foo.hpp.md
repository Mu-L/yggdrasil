---
# charset_foo.hpp 文档

该头文件定义了 yggdrasil 框架字符集模块的核心工具类 `yggr::charset::charset_foo`，用于不同字符串类型、不同字符类型、不同编码之间的高效转换和拷贝。它为字符串编码转换、容器间数据迁移等场景提供了统一、泛型且类型安全的接口。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`charset_foo`（不可实例化，仅提供静态方法）

---

## 主要功能

### 1. 同构字符串类型转换

- 支持同一编码下不同字符串容器（如 `std::string`、`std::wstring`、`boost::container::string` 等）之间的数据拷贝和转换。
- 支持原生字符数组、字符串视图与容器类型的互转。
- 支持带分配器（Allocator）的容器构造。

### 2. 编码转换（跨字符集转换）

- 支持指定源编码和目标编码（如 UTF-8、GBK、UTF-16 等），自动调用 `charset_converter` 进行底层转换。
- 支持不同容器类型、不同字符类型之间的编码转换。
- 若源编码与目标编码一致，则直接进行类型转换或拷贝，无需实际转换。
- 若转换失败，抛出统一的错误码（`E_charset_conver_failed`）。

### 3. 支持多种输入输出形式

- 支持原生指针、长度指定的数组、字符串对象、字符串视图等多种输入形式。
- 支持输出到新对象或原有对象（in-place 替换）。
- 支持分配器自定义。

### 4. 类型安全与静态断言

- 使用 Boost MPL 和 SFINAE 技术，保证只有合适的类型组合才能通过编译。
- 静态断言容器必须为随机访问迭代器，保证高效操作。

### 5. 内部实现机制

- 内部通过 `detail::charset_foo_call_t` 及其特化，自动判断是否为同构字符串类型，选择最优的拷贝或 reinterpret_cast 策略。
- 对于不同编码，统一通过 `charset_converter` 调用 iconv 进行底层转换。

---

## 用法示例

```cpp
#include <yggr/charset/charset_foo.hpp>
#include <string>

// 同编码类型转换
std::wstring ws = L"你好";
std::vector<wchar_t> wvec = yggr::charset::charset_foo::s_xchg<std::vector<wchar_t>>(ws);

// 跨编码转换
std::string utf8_str = u"你好";
std::wstring wide_str = yggr::charset::charset_foo::s_xchg<std::wstring>(
    utf8_str, "UTF-8", "UTF-16"
);

// 原地转换
std::string dst;
yggr::charset::charset_foo::s_xchg(dst, ws, "UTF-16", "UTF-8");
```

---

## 设计说明

- **泛型与高扩展性**：支持任意容器、字符类型、分配器和字符串视图。
- **类型安全**：大量使用 SFINAE、MPL、静态断言，防止类型误用。
- **高效实现**：同构类型直接 reinterpret_cast 或 memcpy，异构类型自动编码转换。
- **异常安全**：转换失败时抛出统一错误码，便于上层捕获和处理。
- **与 yggdrasil 框架深度集成**：依赖于框架的类型 traits、异常体系、分配器等。

---

## 版权声明

MIT License，详见文件头部注释。

---

如需详细 API 说明和扩展用法，请查阅每个静态方法的源码实现与注释。

