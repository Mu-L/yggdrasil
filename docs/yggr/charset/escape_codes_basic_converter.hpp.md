---
# escape_codes_basic_converter.hpp 文档

该头文件定义了 `yggr::charset::escape_codes_basic_converter` 类，为字节数据与转义字符串（如 URL 编码、字符串字面量编码等）之间的转换提供了静态工具方法。支持多字符类型（char、wchar_t、char16_t、char32_t 等），适用于通用转义/反转义场景。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`escape_codes_basic_converter`（仅静态方法）

---

## 主要功能

### 1. 转义分隔符获取

- `SEPUrl<Char>()`  
  获取 URL 编码的转义分隔符（即 `%`），返回指定字符类型。
- `SEPStringLiteral<Char>()`  
  获取字符串字面量编码的转义分隔符（即 `$`），返回指定字符类型。

### 2. 字节转转义字符串

- `s_escape_byte<Char>(Char* pstr, u8 val, Char sep, u32 mode = E_Mode_Default)`  
  将单字节 val 转为转义字符串（如 `%AB`），写入 pstr，sep 为分隔符，mode 控制十六进制大小写。
- `s_escape_bytes<Char>(Char* pstr, const u8* pdata, size_type size, Char sep, u32 mode = E_Mode_Default)`  
  将 pdata 指向的字节数组批量转为转义字符串，写入 pstr。

### 3. 转义字符串转字节

- `s_unescape_byte<Char>(const Char* pstr)`  
  将转义字符串（如 `%AB`）还原为单字节。
- `s_unescape_bytes(u8* pdata, const Char* pstr, std::size_t size, Char sep)`  
  将转义字符串批量还原为字节数组，支持任意字符类型和分隔符。

### 4. 十六进制模式常量

- `E_Mode_Low`、`E_Mode_Upper`、`E_Mode_Default`  
  控制转义字符串中十六进制字母的大小写。

---

## 设计说明

- **泛型支持**：所有接口均为模板，支持多种字符类型。
- **高效实现**：批量转换采用指针操作和 memcpy，效率高。
- **安全性**：带断言和参数检查，防止越界和空指针。
- **与 hex_basic_converter 配合**：依赖 hex_basic_converter 进行十六进制字符与数值的互转。

---

## 用法示例

```cpp
#include <yggr/charset/escape_codes_basic_converter.hpp>
#include <string>

char buf[4] = {};
yggr::charset::escape_codes_basic_converter::s_escape_byte(buf, 0xAB, '%');
// buf == "%AB"

uint8_t data[2] = {0x12, 0x34};
char esc[7] = {};
yggr::charset::escape_codes_basic_converter::s_escape_bytes(esc, data, 2, '%');
// esc == "%12%34"

uint8_t out[2] = {};
yggr::charset::escape_codes_basic_converter::s_unescape_bytes(out, esc, 6, '%');
// out == {0x12, 0x34}
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义分隔符或字符类型，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

