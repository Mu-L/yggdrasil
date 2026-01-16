# detail_packet_info_caster.hpp

概述
- `detail::detail_packet_info_caster<Src<Args...>>` 提供从一个模板包类型（`Src<Args...>`）到公共 `packet_info<...>` 类型的映射与别名。
- 这是一个编译期类型转换工具，用于将任意包装的参数列表（可能包含引用/修饰）统一转换为 `packet_info` 所需的参数列表形式。

行为说明
- 对于 `Src<Args...>`（例如 `std::tuple<T1, T2>` 或自定义模板），该模板将生成类型：
  `::yggr::packet::packet_info< typename reference_trans<Args>::type... >`。
- `reference_trans<Arg>::type` 用于去除或转换引用/包装，使传递给 `packet_info` 的类型为适当的值/引用形式（详细行为见 `yggr/type_traits/reference_trans.hpp`）。

兼容性与实现
- 支持两种实现路径：
  - 如果编译器支持 C++11 可变参数模板（`YGGR_NO_CXX11_VARIADIC_TEMPLATES` 未定义），使用单一的变长模板特化实现。
  - 在不支持可变参数模板的编译器上，使用宏与 Boost.Preprocessor 生成 1..N 参数版本的特化实现（基于 `YGGR_PP_TEMPLATE_PARAMS_LEN()` 限定的最大参数数）。

用途示例（伪代码）

```cpp
// 假设有 Src = some_template<Ts...>
typedef detail::detail_packet_info_caster< some_template<int, std::string&> >::type pkt_info_t;
// 等价于:
// ::yggr::packet::packet_info<int, typename reference_trans<std::string&>::type>
```

注意事项
- 该文件仅提供类型映射，不包含运行时逻辑。
- 依赖 `reference_trans` 的具体转换规则以决定引用/指针/包装类型如何传入 `packet_info`。
- 在无 variadic template 的环境下，映射支持的参数个数受预处理器宏配置限制。

文件
- 实现：`detail_packet_info_caster.hpp`（位于 `yggr/packet/detail`）。
- 相关类型：`yggr/packet/packet_info.hpp`、`yggr/type_traits/reference_trans.hpp`。

----
自动生成：基于 yggr/packet/detail/detail_packet_info_caster.hpp 的概要文档。