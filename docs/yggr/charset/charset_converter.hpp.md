---
# charset_converter.hpp 文档

该头文件定义了 `yggr::charset::charset_converter` 类，用于不同字符集（编码）之间的字符串转换，底层基于 iconv 库实现。支持多种字符串类型和字符类型的高效转换，适用于 UTF-8、GBK、UTF-16、UCS-2 等常见编码的互转。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`charset_converter`（禁止拷贝和移动）

---

## 主要功能

### 1. 构造与初始化

- 支持以 C 字符串或自定义字符串类型指定源字符集和目标字符集。
- 构造时自动初始化 iconv 句柄，若初始化失败则断言。

### 2. 字符集转换接口

- **全量转换**  
  支持如下调用方式，若转换失败返回 `false`，成功则输出结果到 `output`：
  - `operator()(const Char* input, OutString& output) const`
  - `operator()(const Char* input, std::size_t n, OutString& output) const`
  - `operator()(const InString& input, OutString& output) const`
- **支持不完整转换**  
  可用于分块转换大数据，需手动检查输入输出字节数：
  - `operator()(const InString& input, std::size_t& ilen_byte, OutString& output, std::size_t& olen_byte) const`
  - `operator()(const char* input, std::size_t& ilen_byte, char* output, std::size_t& olen_byte) const`

### 3. 校验与状态

- `is_validate()`  
  检查 iconv 句柄是否有效。

---

## 设计说明

- **类型泛化**：支持多种字符串类型（如 std::string、std::wstring、boost::container::string 等）和字符类型（char、wchar_t、char16_t、char32_t）。
- **内存安全**：自动分配和回收输出缓冲区，防止溢出。
- **高效实现**：利用 iconv 库进行底层转换，支持大部分主流字符集。
- **异常安全**：转换失败时输出清空，保证调用方安全。
- **不可拷贝/移动**：防止 iconv 句柄误用。

---

## 用法示例

```cpp
#include <yggr/charset/charset_converter.hpp>
#include <string>

yggr::charset::charset_converter conv("UTF-8", "GBK");
std::string utf8_str = "你好";
std::string gbk_str;
if (conv(utf8_str, gbk_str)) {
    // gbk_str 现在是 GBK 编码
}
```

---

## 注意事项

- 依赖 iconv 库，需在编译和链接时确保 iconv 可用。
- 若转换失败，输出字符串会被清空。
- 若需分块处理大数据，可使用带字节数参数的接口。

---

## 版权声明

MIT License，详见文件头部注释。

---

如需详细 API 说明，请查阅每个函数的源码实现与注释。

