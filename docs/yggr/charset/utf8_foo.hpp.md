---
# utf8_foo.hpp 文档

该头文件定义了 yggdrasil 框架字符集模块中的 UTF-8 工具类 `utf8_foo`，为 UTF-8 字符和字符串的**编码、解码、长度计算、比较、查找、转换等底层操作**提供了高效、类型安全的静态工具方法。它是 UTF-8 字符串体系的核心基础设施，适用于多字符集、多容器环境下的高性能 UTF-8 字符串处理。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`utf8_foo`（不可实例化，仅静态方法）
- **主要常量**：
  - `E_char_max_size`：单个 UTF-8 字符最大字节数（4 或 6，取决于宏）
  - `E_char_max_num`：支持的最大 Unicode 码点
  - `E_char_max_range`：支持的最大码点范围
  - `npos`：无效位置常量

---

## 主要功能

### 1. UTF-8 字符与数值互转

- `char_to_number`  
  将 UTF-8 字符（字节序列、指针、字符串、迭代器等）转换为 Unicode 码点（s32）。
- `number_to_char`  
  将 Unicode 码点转换为 UTF-8 字符（字节序列），支持不同缓冲区和类型。

### 2. UTF-8 字符长度与字符串长度

- `charlen`  
  计算单个 UTF-8 字符的字节长度，支持 char、指针、字符串、迭代器等多种类型。
- `strlen`  
  计算 UTF-8 字符串的字符数（utf8 长度），支持 C 字符串、标准字符串、字符串视图、迭代器区间等。
- `strnlen`  
  计算 UTF-8 字符串在指定字节数内的字符数。
- `strlen_both` / `strnlen_both`  
  同时返回 UTF-8 字符数和字节数。

### 3. UTF-8 字符串有效性判断

- `is_utf8_string`  
  判断给定字符串是否为有效 UTF-8 字符串，支持多种类型。

### 4. 字符集名称获取

- `get_charset_name` / `get_str_charset_name`  
  根据字符串内容自动判断并返回对应的字符集名称（如 "utf-8" 或默认编码）。

### 5. 字符串比较与查找

- `charcmp` / `charcmp_eq`  
  比较两个 UTF-8 字符是否相等或大小关系。
- `strcmp` / `strcmp_eq`  
  比较两个 UTF-8 字符串是否相等或大小关系，支持多种类型和长度参数。
- `find`  
  查找单个 UTF-8 字符在字符串中的位置。
- `search`  
  查找子串在字符串中的位置，支持多种类型和长度参数。
- `search_n`  
  查找连续 n 个相同 UTF-8 字符的起始位置。

### 6. 字节长度与迭代器支持

- `utf8_length_to_byte_size`  
  将 UTF-8 字符数转换为字节数。
- `byte_distance`  
  计算任意迭代器区间的字节距离，适配普通和 UTF-8 字符串迭代器。

### 7. 其他辅助

- `negative_number`  
  计算负向码点（用于某些算法）。
- `format_number_step`  
  格式化步进值，保证在合法码点范围内。

---

## 设计说明

- **类型泛化**：所有接口均为模板，支持 char、wchar_t、字符串、字符串视图、迭代器等多种类型。
- **高效实现**：底层直接操作字节序列，零拷贝，效率极高。
- **类型安全**：大量使用 SFINAE、traits、静态断言，防止类型误用。
- **异常安全**：带断言和参数检查，防止越界和非法输入。
- **与 yggdrasil 框架深度集成**：依赖于框架的字符串类型、traits、编码工具、容器特性等。

---

## 用法示例

```cpp
#include <yggr/charset/utf8_foo.hpp>
#include <string>

using yggr::charset::utf8_foo;

// 字符转码点
const char* c = u8"你";
int code = utf8_foo::char_to_number(c);

// 码点转字符
char buf[8] = {};
size_t used = 0;
utf8_foo::number_to_char(buf, code, sizeof(buf), used);

// 计算字符串长度
std::string s = u8"你好世界";
size_t len = utf8_foo::strlen(s);

// 比较字符串
bool eq = utf8_foo::strcmp_eq(s.c_str(), u8"你好世界");

// 查找字符
size_t pos = utf8_foo::find(s, u8"世");
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型、分配器或与其他字符串类型的互操作，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

