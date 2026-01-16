**address_helper.hpp 文档**

简介：
- `address_helper.hpp` 提供将任意字符宽度的字符串（例如 `char`、`wchar_t`、`char16_t`、`char32_t` 等）转换为 `boost::asio::ip::address` 的实用工具 `address_helper`，以及内部实现细节的适配器（`detail::address_from_string_impl`）。该工具解决了不同字符宽度与字符编码之间的转换问题。

设计要点：
- 对于单字节字符（sizeof(Char) == 1），直接使用 `boost::asio::ip::address::from_string(const char*, error_code)` 来解析字符串地址；若解析失败（error_code 非 0），返回默认构造的 `address`（空地址）。
- 对于多字节字符（如 `wchar_t` 等），先使用 `yggr::charset::string_converter::s_conv` 将字符串转换为 `yggr::basic_string<char>`，再交由单字节实现解析。
- 通过模板特化 `address_from_string_impl<Char, N>` 将两种策略统一封装，并为 `Char` 大小为 1 的情况做偏特化以优化路径。

主要接口：
- `static address_type address_from_string(const Char* str_addr)`：解析 C 风格字符串，返回 `boost::asio::ip::address`。
- `static address_type address_from_string(const Basic_String<Char, Traits, Alloc>& str_addr)`：解析 C++ 字符串模板（项目中的 `basic_string` 或 std::basic_string），支持不同字符类型。

用法示例：

```cpp
// char*
auto a1 = yggr::network::address_helper::address_from_string("127.0.0.1");

// wchar_t*
std::wstring waddr = L"127.0.0.1";
auto a2 = yggr::network::address_helper::address_from_string(waddr);
```

注意事项：
- 当 `boost::asio::ip::address::from_string` 因格式错误而设置 `error_code` 时，函数会返回默认构造的 `address`；调用方如需区分错误情况，应在转换前验证字符串或使用自定义解析流程。
- 字符串转换使用 `yggr::charset::string_converter`，请确保相应的字符集转换器在目标平台/配置下可用并正确工作。

相关文件：
- [yggr/network/address_helper.hpp](address_helper.hpp)
- [yggr/charset/string_converter.hpp](../charset/string_converter.hpp)
