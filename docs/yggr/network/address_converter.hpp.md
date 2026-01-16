**address_converter.hpp 文档**

简介：
- `address_converter.hpp` 提供了一组轻量的转换器模板，用以在网络地址、端口、端点类型与字符串类型之间进行安全且方便的隐式/显式转换，适用于日志、配置解析和字符串序列化场景。

主要模板：
- `address_converter<Address>`：
  - 构造：`address_converter(const Address& addr)`。
  - 隐式/显式转换：
    - `operator const Address&()` 返回底层 `Address` 引用。
    - `template<typename String> operator String() const`：将 `Address::to_string()` 的结果转换为目标字符串类型（通过 `yggr::charset::string_converter::s_conv`），若 `to_string()` 抛出 `boost::system::error_code`，返回空字符串类型值。

- `port_converter<Port>`：
  - 支持标量端口类型或类类型端口。构造时会根据 `Port` 是否为类类型选择传参方式（引用或按值）。
  - 提供 `operator port_arg_type()` 返回底层端口值，以及 `template<typename String> operator String()` 将端口转为字符串并使用 `s_conv` 做字符集转换。

- `endpoint_converter<EndPoint>`：
  - 封装端点类型，提供 `operator const EndPoint&()` 以及 `template<typename String> operator String()`，后者通过将端点输出到 `std::stringstream`（即 `operator<<`）并转换字符串来实现。

设计要点：
- 三个转换器都为非拷贝非移动类型（继承自 `nonable::noncopyable` 与 `nonable::nonmoveable`），意在作为临时值使用以防误拷贝。
- 字符串转换均基于 `yggr::charset::string_converter::s_conv<To, From>`，确保字符编码在不同字符串类型间正确转换。

用法示例：

```cpp
// Address 假设为 boost::asio::ip::address
boost::asio::ip::address addr = boost::asio::ip::address::from_string("127.0.0.1");
std::wstring ws = yggr::network::address_converter<boost::asio::ip::address>(addr); // 转为 wide string

// 端口
int p = 8080;
std::string ps = yggr::network::port_converter<int>(p);

// 端点（假设 EndPoint 支持 operator<<）
auto ep = /* endpoint */;
std::string s = yggr::network::endpoint_converter<decltype(ep)>(ep);
```

注意事项：
- `address_converter` 的字符串转换依赖 `Address::to_string()`，若底层实现抛出异常（`boost::system::error_code`），函数会捕获并返回空字符串类型；调用方应根据场景判断是否需要额外错误处理。
- `endpoint_converter` 使用 `operator<<` 将端点写入 `stringstream`，因此要求 `EndPoint` 类型支持该操作。
- 三个类型被声明为不可拷贝/不可移动，推荐作为短生命周期的临时对象使用。

相关文件：
- [yggr/network/address_converter.hpp](yggr/network/address_converter.hpp)
- [yggr/charset/string_converter.hpp](yggr/charset/string_converter.hpp)
