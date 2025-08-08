---
# hex_converter.hpp 文档

该头文件定义了 `yggr::charset::hex_converter` 类，为字节数据与十六进制字符串之间的**高级批量转换**提供了泛型静态工具方法。支持多种容器类型、字符类型、分配器和编码，适用于高效的批量十六进制编码/解码、数据序列化、调试输出等场景。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`hex_converter`（继承自 `hex_basic_converter`，仅静态方法）
- **内部实现**：通过 detail 命名空间下的辅助模板类实现批量处理

---

## 主要功能

### 1. 单字符十六进制转换

- `s_char_to_hex`  
  支持多种 UTF-8 字符类型（如 `utf8_char_impl`、`basic_utf8_char_view` 等）转为单字节数值。
- 继承自 `hex_basic_converter` 的 `s_char_to_hex`，支持基本字符类型。

### 2. 字符串转字节数组（十六进制解码）

- `s_string_to_hex(HexBuf& buf, const Char* p, size_type n, const string& src_charset_name)`  
  将十六进制字符串（如 "1A2B"）解码为字节容器，支持指定源字符集。
- 支持多种字符串类型（如 `std::basic_string`、`utf8_string_impl`、`basic_string_view` 等）与容器类型的泛型转换。
- 自动适配不同字符集编码，必要时先转为 UTF-8 再解码。

### 3. 字节数组转十六进制字符串（十六进制编码）

- `s_hex_to_string(String& str, const HexBuf& hex_buf, u32 mode, const string& dst_charset_name)`  
  将字节容器批量编码为十六进制字符串，支持大小写模式和目标字符集。
- 支持多种容器类型、字符串类型、分配器和迭代器区间。
- 自动适配不同字符集编码，必要时先转为 UTF-8 再转换为目标编码。

### 4. 分配器与泛型支持

- 支持自定义分配器的字符串构造，适合高性能和特殊内存管理场景。
- 支持任意容器、字符串、字符串视图、迭代器等类型的泛型批量转换。

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
#include <yggr/charset/hex_converter.hpp>
#include <vector>
#include <string>

// 字节数组转十六进制字符串
std::vector<uint8_t> data = {0x12, 0x34, 0xAB};
std::string hexstr = yggr::charset::hex_converter::s_hex_to_string<std::string>(data);

// 十六进制字符串转字节数组
std::vector<uint8_t> out;
yggr::charset::hex_converter::s_string_to_hex(out, hexstr.c_str(), hexstr.size());
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义分隔符、字符类型或容器类型，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

