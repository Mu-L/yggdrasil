---
# hex_basic_converter.hpp 文档

该头文件定义了 `yggr::charset::hex_basic_converter` 类，为字节与十六进制字符串之间的转换提供了静态工具方法。支持多字符类型（char、wchar_t、char16_t、char32_t 等），适用于通用的十六进制编码/解码场景，如数据序列化、转义、调试输出等。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`hex_basic_converter`（仅静态方法）

---

## 主要功能

### 1. 十六进制字符与数值互转

- `s_char_to_hex(char val)`  
  将单个十六进制字符（'0'-'9', 'a'-'f', 'A'-'F'）转换为对应的数值（0-15），非法字符返回 0xFF。
- `s_char_to_hex<Char>(Char ch_val)`  
  泛型版本，支持任意可转换为字符的类型。

### 2. 数值转十六进制字符

- `s_hex_to_char(char* pstr, u8 val, u32 mode = E_Mode_Default)`  
  将单字节 val 转为两个十六进制字符，写入 pstr，mode 控制大小写。
- `s_hex_to_char<Char>(Char* pstr, u8 val, u32 mode = E_Mode_Default)`  
  泛型版本，支持任意字符类型。

### 3. 十六进制字符串转字节数组

- `s_string_to_hex(u8* phex, const char* pstr, size_type size)`  
  将十六进制字符串（如 "1A2B"）转换为字节数组，size 必须为偶数。
- `s_string_to_hex<Char>(u8* phex, const Char* pstr, size_type size)`  
  泛型版本，支持任意字符类型。

### 4. 字节数组转十六进制字符串

- `s_hex_to_string(char* pstr, const u8* phex, size_type size, u32 mode = E_Mode_Default)`  
  将字节数组转换为十六进制字符串，mode 控制大小写。
- `s_hex_to_string<Char>(Char* pstr, const u8* phex, size_type size, u32 mode = E_Mode_Default)`  
  泛型版本，支持任意字符类型。

### 5. 十六进制模式常量

- `E_Mode_Low`、`E_Mode_Upper`、`E_Mode_Default`  
  控制十六进制字符串中字母的大小写。

---

## 设计说明

- **泛型支持**：所有接口均为模板，支持多种字符类型。
- **高效实现**：批量转换采用指针操作和循环，效率高。
- **安全性**：带断言和参数检查，防止越界和空指针。
- **与 hex_converter_config 配合**：依赖 hex_converter_config 提供的字符映射表。

---

## 用法示例

```cpp
#include <yggr/charset/hex_basic_converter.hpp>
#include <cstdint>

char buf[3] = {};
yggr::charset::hex_basic_converter::s_hex_to_char(buf, 0xAB);
// buf == "AB"

uint8_t data[2] = {0x12, 0x34};
char hexstr[5] = {};
yggr::charset::hex_basic_converter::s_hex_to_string(hexstr, data, 2);
// hexstr == "1234"

uint8_t out[2] = {};
yggr::charset::hex_basic_converter::s_string_to_hex(out, hexstr, 4);
// out == {0x12, 0x34}
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符类型，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

