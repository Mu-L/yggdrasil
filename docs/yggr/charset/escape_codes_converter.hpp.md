---
# escape_codes_converter.hpp 文档

该头文件定义了 `yggr::charset::escape_codes_converter` 类，为字节数据与转义字符串（如 URL 编码、字符串字面量编码等）之间的**高级批量转换**提供了泛型静态工具方法。支持多种容器类型、字符类型和分配器，适用于高效的批量转义/反转义场景，且可自动处理字符集编码转换。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`escape_codes_converter`（继承自 `escape_codes_basic_converter`，仅静态方法）
- **内部实现**：通过 detail 命名空间下的辅助模板类实现批量处理

---

## 主要功能

### 1. 单字节转义

- `s_escape_byte(String& str, u8 val, Char sep, u32 mode, const string& dst_charset_name)`  
  将单字节 val 转为转义字符串（如 `%AB`），写入指定字符串类型 str，支持指定分隔符、十六进制大小写、目标字符集。
- `s_escape_byte(u8 val, Char sep, ...)`  
  返回转义后的字符串对象，支持分配器自定义。

### 2. 批量字节转义

- `s_escape_bytes(String& str, const HexBuf& hex_buf, Char sep, u32 mode, const string& dst_charset_name)`  
  将字节容器 hex_buf 批量转为转义字符串，写入 str，支持字符集转换。
- `s_escape_bytes(const HexBuf& hex_buf, Char sep, ...)`  
  返回转义后的字符串对象，支持分配器自定义。

### 3. 单字节反转义

- `s_unescape_byte(const String& str)`  
  将转义字符串（如 `%AB`）还原为单字节，支持字符串和字符串视图类型。

### 4. 批量字符串反转义为字节

- `s_unescape_bytes(HexBuf& buf, const Char* p, size_type n, Char sep, const string& src_charset_name)`  
  将转义字符串批量还原为字节容器，支持指定字符集。
- 支持多种输入类型：C 字符串、`std::basic_string`、`utf8_string`、`basic_string_view`、`basic_utf8_string_view` 等。

### 5. 字符集自动适配

- 支持源字符串和目标字符串的字符集自动转换（如 UTF-8 与本地编码之间的互转）。
- 若字符集不同，自动进行编码转换，保证数据正确。

### 6. 内部实现机制

- detail 命名空间下的 `escape_bytes_helper` 和 `unescape_bytes_helper` 模板类，自动根据迭代器类型选择最优实现。
- 支持随机访问和非随机访问容器的高效处理。

---

## 设计说明

- **高度泛型**：支持任意容器、字符类型、分配器和字符串视图。
- **类型安全**：大量使用 SFINAE、MPL、静态断言，防止类型误用。
- **高效实现**：同构类型直接批量处理，异构类型自动编码转换。
- **异常安全**：参数检查和断言，防止越界和空指针。
- **与 yggdrasil 框架深度集成**：依赖于框架的类型 traits、分配器、字符串类型等。

---

## 用法示例

```cpp
#include <yggr/charset/escape_codes_converter.hpp>
#include <vector>
#include <string>

// 字节数组转 URL 转义字符串
std::vector<uint8_t> data = {0x12, 0x34, 0xAB};
std::string esc = yggr::charset::escape_codes_converter::s_escape_bytes<std::string>(data, '%');

// 反转义回字节数组
std::vector<uint8_t> out;
yggr::charset::escape_codes_converter::s_unescape_bytes(out, esc, '%');
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义分隔符、字符类型或容器类型，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

