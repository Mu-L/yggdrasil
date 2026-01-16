# hn_conv.hpp 文档

## 概述
- **文件**: [yggr/network/hn_conv.hpp](yggr/network/hn_conv.hpp#L1-L470)
- **描述**: 提供主机到网络字节序（hton）和网络到主机字节序（ntoh）的一组重载与模板实现，支持内置整型、浮点、宽字符类型以及自定义类型（通过成员函数 `hton`/`ntoh`）。同时对不同字符宽度的 `Basic_String` 提供逐元素的转换实现。
- **用途**: 在网络序列化/反序列化或跨平台网络通信中统一处理大小端转换。

## 设计要点
- 通过一组宏（`HN_CONV_8/16/32/64/ORG/NATIVE`）为原始标量类型生成 `hton`/`ntoh` 函数。
- 提供 `detail::has_hton` 与 `detail::has_ntoh` 检查，允许对自定义类型启用成员函数式的字节序转换（若类型实现 `T hton()`/`T ntoh()`）。
- 对 `wchar_t`、`c16`、`c32` 等宽字符类型使用专门的 helper（`wchar_t_hn_conv_helper`），根据类型字节宽度（2或4）分别调用 `htons/ntohs` 或 `htonl/ntohl`。
- 对于 `Basic_String` 模板（`char`、`wchar_t`、`c8`、`c16`、`c32`）提供重载，`char`/`c8` 类型直接返回引用（无需转换），`wchar_t`/`c16`/`c32` 则逐元素转换并返回拷贝后的结果。
- 通过 `endian_test` 常量与 `is_little_endian()`/`is_big_endian()` 函数运行时判断主机字节序。

## 主要宏
- `HN_CONV_8(type)`：对 1 字节类型返回原值（无转换）。
- `HN_CONV_16(type)` / `HN_CONV_16_ORG(type)`：对 2 字节类型使用 `htons`/`ntohs`（`_ORG` 直接调用标准函数，`HN_CONV_16` 通过内存 reinterpret 并修改低位）。
- `HN_CONV_32(type)` / `HN_CONV_32_ORG(type)`：对 4 字节类型使用 `htonl`/`ntohl`。
- `HN_CONV_64(type)`：对 8 字节类型，若为小端则对两个 u32 片段分别转换并交换顺序。
- `HN_CONV_NATIVE(type)`：宏指向 `HN_CONV_8`（对浮点在默认禁用转换时使用）。

宏在文件末尾会被 `#undef` 清理。

## 支持的类型（源码中显式声明）
- 1 字节: `char`, `s8`, `u8`, `c8`（可选）
- 2 字节: `s16`, `u16`（注意 `u16` 使用 `_ORG` 版本）
- 4 字节: `s32`, `u32`, `long`（在某些平台有特殊处理）
- 8 字节: `s64`, `u64`
- 浮点: `f32`, `f64`（受宏 `YGGR_NETWORK_FLOAT_POINT_HN_CONV_ENABLE` 控制，开启时按位处理，否则不转换）
- 宽字符: `wchar_t`、`c16`、`c32`（根据 `sizeof` 分别按 2/4 字节处理）
- 字符串模板: `Basic_String<char>`、`Basic_String<wchar_t>`、`Basic_String<c8>`、`Basic_String<c16>`、`Basic_String<c32>`（部分在编译期受宏影响）

## 模板与 SFINAE 行为
- 对于满足 `detail::has_hton<T>`（即有成员函数 `hton`）的类型，`hton(const T&)` 调用 `t.hton()` 并返回 `T`（返回值类型）。
- 对于不满足 `has_hton` 的类型，提供一个 `hton(const T&)` 的禁用版本，直接返回 `const T&`（即不做转换）。同理对 `ntoh` 也适用。

## 字符串转换策略
- `Basic_String<char>` 与 `Basic_String<yggr::c8>`：无需转换，直接返回常量引用。
- `Basic_String<wchar_t>`、`Basic_String<c16>`、`Basic_String<c32>`：对字符串做逐字符转换，返回转换后的拷贝（注意：实现返回为非常量引用或值拷贝，使用时注意语义）。

## 端序检测
- 通过联合常量 `endian_test`（初始化为 0x623f3f6c）和测试其字节 `c[0]` 是否为 `'l'` 或 `'b'` 来判断主机是小端还是大端。
- 提供 `is_little_endian()` 与 `is_big_endian()` 两个接口，兼容有无 `constexpr` 的编译器环境。

## 依赖与包含
- 头文件依赖：
  - `yggr/base/yggrdef.h`
  - `yggr/network/socket_conflict_fixer.hpp`
  - `yggr/utility/swap.hpp`
  - `yggr/mplex/static_assert.hpp`
  - `yggr/ppex/has_member_check.hpp`
  - Boost: `boost/utility/enable_if.hpp`, `boost/asio.hpp`, `boost/mpl/bool.hpp`
- 使用的系统/库函数：`htons`, `ntohs`, `htonl`, `ntohl`（来自 `<arpa/inet.h>` 或平台等价实现，通过包含的 socket fixer 处理平台差异）。

## 示例
```cpp
using yggr::network::hton;
using yggr::network::ntoh;

u32 x = 0x11223344;
u32 xn = hton(x); // 主机->网络顺序
u32 xr = ntoh(xn); // 网络->主机，恢复为 0x11223344

std::string s = "abc";
const std::string& s2 = hton(s); // 对 char 字符串无转换

std::wstring ws = L"测试";
auto ws_net = hton(ws); // 对 wchar_t 每字符调用对应 helper 进行转换，返回拷贝
```

## 注意事项与建议
- `HN_CONV_64` 使用了对 32 位片段的转换并交换顺序，假定 `u32` 分片在内存中按连续两个 32 位展示；这种实现对某些非平凡类型或未对齐数据需谨慎。
- 对自定义类型，如需支持 `hton`/`ntoh`，请在类型中实现对应成员函数并返回转换后的类型（以匹配 SFINAE 策略）。
- 浮点数的按位转换可能产生非可移植行为；默认情况下该库未开启浮点转换，除非定义宏 `YGGR_NETWORK_FLOAT_POINT_HN_CONV_ENABLE`。
- 多线程环境下，对同一缓冲区重复就地转换需确保同步与所有者语义，当前字符串实现返回了拷贝以避免就地破坏原字符串。

## 参考
- 源码： [yggr/network/hn_conv.hpp](yggr/network/hn_conv.hpp#L1-L470)

---
