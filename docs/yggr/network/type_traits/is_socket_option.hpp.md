**is_socket_option.hpp 文档**

简介：
- `is_socket_option.hpp` 提供了用于检测“套接字选项（socket option）”类型的类型特征（type traits）。它通过检查类型是否包含标准的 socket option 成员或匹配 Boost.Asio 内部的 socket_option 特化，来判断某个类型是否可作为套接字选项使用。

主要内容：
- 成员检测宏：
  - 使用 `YGGR_PP_HAS_MEMBER_FOO` 系列宏生成对成员 `level`、`name`、`data`、`size` 的检测模板（即 `YGGR_PP_HAS_ANY_MEMBER_FOO_DEF(so_level, level)` 等）。
- `is_socket_option_impl<T>` 模板：
  - 默认实现：使用 `boost::mpl::and_` 判断类型 `T` 是否同时具有 `level`、`name`、`data`、`size` 这四个成员，若都存在则为 true。（适用于自定义的 socket option 类型）
  - 为 `boost::asio::detail::socket_option::boolean/integer/linger<Level, Name>` 提供了显式偏特化，直接将判定设为 true。
- 别名模板（包装）：
  - `is_settable_socket_option<T>`、`is_gettable_socket_option<T>`、`is_socket_option<T>`：均继承自 `is_socket_option_impl<T>`，作为公共的类型特征接口使用。

宏：
- `YGGR_PP_NETWORK_IS_SETTABLE_SOCKET_OPTION_IMPL_DEF(__type__)`：
  - 可用来为特定类型显式生成 `is_socket_option_impl<__type__>` 的 true 特化（此宏只在文件顶部定义，并可在其它地方使用以注册可设置的 socket option 类型）。

用法示例：

```cpp
// 假设 MySocketOption 定义了 level/name/data/size 成员
static_assert(yggr::network::type_traits::is_socket_option<MySocketOption>::value, "MySocketOption must be socket option");

// 对 boost::asio 内部的类型，库已提供偏特化
static_assert(yggr::network::type_traits::is_socket_option< ::boost::asio::detail::socket_option::integer<1,2> >::value, "true");
```

注意事项：
- 成员检测依赖于预处理宏 `YGGR_PP_HAS_MEMBER_FOO_*`，检查的是成员名是否存在；对于不同命名或接口的第三方 socket option，需要提供适配或显式特化。
- `boost::asio::detail::socket_option` 属于 Boost.Asio 的内部实现细节，不同 Boost 版本可能有所差异；对可移植性要求高的项目，慎用对内部类型的依赖或在不同 Boost 版本上增加适配。

相关文件：
- [yggr/network/type_traits/is_socket_option.hpp](is_socket_option.hpp)
