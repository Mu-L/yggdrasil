# basic_bson_inner_data.hpp

概述
- 本文件通过预处理宏将基础 C++ 原生类型与容器类型映射到 BSON 类型 ID（用于内部 BSON 序列化/类型识别）。
- 主要由宏 `YGGR_PP_BSON_TYPEID_IMPL` 和 `YGGR_PP_CONTAINER_BSON_TYPEID_IMPL` 完成注册工作。

映射要点
- 布尔类型：
  - `bool` -> `E_BSON_TYPE_BOOL`

- 整数/字符相关（大部分映射到 INT32）：
  - `s8`, `char`, `wchar_t`（若启用）, `c8`, `c16`, `c32`（视编译器特性）
  - `u8`, `s16`, `u16`, `s32`, `u32` -> `E_BSON_TYPE_INT32`

- 64 位整数：
  - `s64`, `u64` -> `E_BSON_TYPE_INT64`

- 浮点：
  - `f32`, `f64` -> `E_BSON_TYPE_DOUBLE`

- 字符串与字符容器：
  - `std::basic_string<...>`, `boost::container::basic_string<...>`, `charset::utf8_string_impl<...>` 等 -> `E_BSON_TYPE_UTF8`
  - `charset::string_charset_helper`（2 参数宏）也映射为 `E_BSON_TYPE_UTF8`
  - `charset::utf8_char_impl`（utf8_char 类型容器） -> `E_BSON_TYPE_UTF8`

实现/兼容性细节
- 对 wchar_t、char8/16/32 等类型的注册使用条件编译（例如 `YGGR_NO_CWCHAR`、`YGGR_NO_CHAR8_T` 等宏），以兼容不同编译器与标准库特性。
- 多数字类型被映射为 INT32（注意潜在的截断/范围问题），仅显式将 64 位类型映射为 INT64。
- 字符串类使用 `YGGR_PP_CONTAINER_BSON_TYPEID_IMPL`（带参数个数宏）注册，表明支持不同容器模板签名（3 参数或 2 参数的容器宏）。

注意事项
- 本文件本身仅包含映射注册宏的调用；实际宏实现与 BSON 行为在 `bson_typeid.hpp` 或宏定义处实现，需查看宏定义以了解具体注册逻辑。
- 使用这些映射时请确认：
  - 目标类型的取值范围是否适合被映射到 INT32（避免意外截断）。
  - 宏拼接/参数（如模板参数个数）与工程中的字符串/字符编码设置一致。

相关文件
- 源文件：`basic_bson_inner_data.hpp`（位于 `yggr/nsql_database_system`）。
- 参考：`bson_typeid.hpp`（定义 `bson_typeid_def` 与宏实现）。

----

