---
# string_view.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了**字符串视图类型的统一接口与适配**，包括 `basic_string_view` 及其常用别名（如 `string_view`、`wstring_view` 等），并实现了与标准输出流的兼容。它是 yggdrasil 字符串视图体系的入口文件，适用于高性能、零拷贝的字符串处理场景。

---

## 主要内容

- **命名空间**：`yggr::charset`、yggr
- **核心类型**：
  - `basic_string_view<CharT, Traits>`
  - 类型别名：`string_view`、`wstring_view`、`u8string_view`、`u16string_view`、`u32string_view`
- **输出流重载**：支持将 string_view 直接输出到 `std::ostream`/`std::wostream` 等流对象
- **依赖**：
  - `string_decl.hpp`：字符串类型声明
  - `charset_foo.hpp`：字符集转换工具
  - `string_view_impl.hpp`：string_view 实现

---

## 主要功能

### 1. 输出流重载

```cpp
template <typename CharT_OS, typename Traits_OS, typename CharT, typename Traits>
std::basic_ostream<CharT_OS, Traits_OS>&
operator<<(std::basic_ostream<CharT_OS, Traits_OS>& os, const basic_string_view<CharT, Traits>& s);
```
- **功能**：支持将任意字符类型的 `basic_string_view` 输出到任意字符类型的输出流（如 `std::ostream`、`std::wostream`）。
- **实现机制**：自动进行字符集转换（如 UTF-8 到 UTF-16），保证输出内容正确。
- **适用场景**：跨编码输出、日志打印、调试等。

### 2. 字符串视图类型别名

- `string_view`：`basic_string_view<char>`
- `wstring_view`：`basic_string_view<wchar_t>`
- `u8string_view`：`basic_string_view<yggr::c8>`
- `u16string_view`：`basic_string_view<yggr::c16>`
- `u32string_view`：`basic_string_view<yggr::c32>`

> 注：各类型别名的可用性由宏（如 `YGGR_NO_CWCHAR`、`YGGR_NO_CHAR8_T` 等）控制，自动适配平台和编译器特性。

### 3. 全局 using 导出

- 在 yggr 命名空间下导出常用 string_view 类型，便于全局统一访问。

---

## 设计说明

- **类型兼容**：支持多字符类型、多 traits，适合多编码、多平台环境。
- **零拷贝**：string_view 仅保存指针和长度，不拷贝底层数据，效率高。
- **自动编码适配**：输出流重载自动处理字符集转换，保证跨平台输出一致性。
- **泛型友好**：所有接口均为模板，适合泛型编程和大规模工程。

---

## 用法示例

```cpp
#include <yggr/charset/string_view.hpp>
#include <iostream>

yggr::string_view sv = "hello world";
std::cout << sv << std::endl; // 自动输出

yggr::charset::wstring_view wsv = L"你好";
std::wcout << wsv << std::endl; // 自动输出
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符类型、traits 或与其他字符串类型的互操作，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

