---
# charset_base_foo.hpp 文档

该头文件定义了 `yggr::charset::charset_base_foo` 工具类，为字符集相关操作提供基础静态方法，支持多种字符类型（如 char、wchar_t、char8_t、char16_t、char32_t 及自定义类型），并包含大小写无关比较、长度计算、空间扩展等常用功能。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`charset_base_foo`（不可实例化，仅提供静态方法）

---

## 主要功能

### 1. 空间扩展率常量

- `E_space_expansion_rate`  
  控制字符集转换时的空间扩展倍数（默认 4，若定义 `YGGR_USE_UTF8_EX_MODE` 则为 6）。

### 2. 字符串长度与空间计算

- `strlen(const Char* str)`  
  计算以 0 结尾的字符串长度，支持多种字符类型。
- `strnlen(const Char* str, size_type n)`  
  计算最大长度为 n 的字符串长度。
- `xchglen(const Char* str)`  
  计算字符串转换时所需的最大空间（含扩展率）。
- `xchgnlen(const Char* str, size_type n)`  
  计算最大长度为 n 的字符串转换所需空间。
- `xchglen(size_type n)`  
  直接根据长度 n 计算转换所需空间。
- `xchglen(const Basic_String& str)`  
  计算字符串对象转换所需空间。

### 3. 字符串标准化

- `normal_length(Basic_String& str)`  
  移除字符串中首个 0 字符及其后内容，返回标准化后的字符串。

### 4. 大小写无关比较

- `strcmp_case(const char* l, const char* r)`  
  C 风格字符串大小写无关比较。
- `strncmp_case(const char* l, const char* r, size_type len)`  
  C 风格字符串大小写无关比较（指定长度）。
- `strcmp_case(const Char* l, const Char* r)`  
  泛型字符类型大小写无关比较。
- `strncmp_case(const Char* l, const Char* r, size_type len)`  
  泛型字符类型大小写无关比较（指定长度）。

---

## 设计说明

- **泛型支持**：大量使用模板和 SFINAE，支持自定义和标准字符类型。
- **平台兼容**：自动适配 Windows 和 POSIX 下的大小写比较实现。
- **不可实例化**：继承自 `nonable::noncreateable`，仅能静态调用。
- **高效安全**：使用断言和类型 traits 保证类型安全和运行时安全。

---

## 用法示例

```cpp
using namespace yggr::charset;

const char* s = "Hello";
size_t len = charset_base_foo::strlen(s);

std::string str = "abc\0def";
charset_base_foo::normal_length(str); // str 变为 "abc"

int cmp = charset_base_foo::strcmp_case("abc", "ABC"); // cmp == 0
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需详细 API 说明，请查阅每个函数的源码实现与注释。

