# packet_info_caster.hpp

概述
- `packet_info_caster<T>` 是对内部实现 `detail::detail_packet_info_caster<T>` 的轻量别名/封装。
- 该头文件只是将 `detail` 层的实现向外暴露，并不包含实质逻辑；实际行为和 API 定义在 `yggr/packet/detail/detail_packet_info_caster.hpp` 中。

用途
- 作为公共接口类型转发器（type alias wrapper），便于用户代码引用 `packet_info_caster<T>` 而无需包含 detail 目录头。
- 保留模板参数 `T` 并继承 detail 实现以实现完全相同行为。

注意事项
- 若需要查看具体的转换/提取规则，请打开并阅读 `yggr/packet/detail/detail_packet_info_caster.hpp`。
- 该文件设计为轻量头文件，便于在不暴露 detail 命名空间实现细节的情况下提供类型别名。

文件
- 源文件：packet_info_caster.hpp（位于同目录）。
- 相关实现：[yggr/packet/detail/detail_packet_info_caster.hpp](yggr/packet/detail/detail_packet_info_caster.hpp)

----
自动生成：基于 yggr/packet/packet_info_caster.hpp 的概要文档。