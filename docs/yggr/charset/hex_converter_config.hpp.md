---
# hex_converter_config.hpp 文档

该头文件为 yggdrasil 框架的字符集模块提供了十六进制转换的配置工具，主要用于控制十六进制字符串的大小写格式，并提供十六进制字符查找表。常用于字节与十六进制字符串互转的场景，如数据序列化、转义、调试输出等。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心结构体**：`hex_converter_config`

---

## 主要功能

### 1. 十六进制模式常量

- `E_Mode_Low`  
  小写十六进制模式（如 "abcdef"）。
- `E_Mode_Upper`  
  大写十六进制模式（如 "ABCDEF"）。
- `E_Mode_Default`  
  默认十六进制模式。若未定义 `YGGR_HEX_CONV_DEFAULT_MODE` 或其值非法，则为小写模式。

### 2. 十六进制字符查找表

- `s_hex_to_char_table(u32 mode = E_Mode_Default)`  
  返回指定模式下的十六进制字符查找表指针：
  - `mode == E_Mode_Low` 返回 "0123456789abcdef"
  - `mode == E_Mode_Upper` 返回 "0123456789ABCDEF"
- 支持编译期 constexpr 或内联，效率高。
- 内部断言 mode 必须小于 2，防止越界。

---

## 设计说明

- **高效实现**：查找表为静态常量数组，查找速度快。
- **灵活配置**：可通过宏定义切换默认大小写模式，适应不同编码风格。
- **类型安全**：所有模式常量均为 u32 类型，便于模板和泛型编程。
- **与 hex_basic_converter 配合**：通常与 `hex_basic_converter` 等工具类联合使用，实现字节与十六进制字符串的高效互转。

---

## 用法示例

```cpp
#include <yggr/charset/hex_converter_config.hpp>

const char* low_tab = yggr::charset::hex_converter_config::s_hex_to_char_table(); // "0123456789abcdef"
const char* up_tab = yggr::charset::hex_converter_config::s_hex_to_char_table(yggr::charset::hex_converter_config::E_Mode_Upper); // "0123456789ABCDEF"
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义十六进制格式，请参考结构体实现方式。详细用法和扩展方式请查阅源码与注释。

