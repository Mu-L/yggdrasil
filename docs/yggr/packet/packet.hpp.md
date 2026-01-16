# packet.hpp

概述
- 包含 `packet<Archive_Partner>` 与 `ref_packet<Archive_Partner>` 两个模板类，用于序列化/反序列化数据到缓冲、在网络传输中封装原始字节缓冲，以及与各种 archive helper 互操作。
- `Archive_Partner` 应提供 `archive_type`（指示是 save/load）、`archive_helper_type`（提供缓冲操作辅助，如 `buf_type`、`buf_copy`、`save`、`load`、`buf_size` 等）。

关键类型
- `archive_partner_type`, `archive_type`, `archive_helper_type`。
- `buf_type`, `buf_val_type`, `buf_real_val_type`：底层缓冲容器与元素类型。

主要功能（`packet`）
- 构造：从缓冲迭代器、缓冲对象、或其他 `packet`/`ref_packet`（不同 `Archive_Partner` 但相同 `buf_type`）构造。
- 赋值/swap：支持从缓冲及其它 `packet`/`ref_packet` 赋值与互换，使用 `archive_helper_type::buf_copy` / `buf_swap` 以兼容不同缓冲策略与移动语义。
- save/load：
  - `save<T>(const T&)` 将对象序列化到内部缓冲；要求 `archive_type::is_loading()` 为 false。
  - `load<T>(T&)` 将内部缓冲反序列化为对象；要求 `archive_type::is_saving()` 为 false。
- 缓冲操作：`empty()`, `size()`, `resize()`, `size_buf()`, `buf()`, `val_buf()` 等，均委托给 `archive_helper_type`。
- 比较：`compare_eq` 与各种重载的非成员 `operator==/!=`，基于缓冲比较。
- `cypher(handler)`：执行自定义加密/解密回调，传入 `_buf` 的引用。

主要功能（`ref_packet`）
- `ref_packet` 是对外部缓冲的引用封装（`buf_ref_type`），用于避免拷贝场景：构造时接收 `const buf_type&` 并保存为非 const 引用（`const_cast`）。
- 提供与 `packet` 类似的赋值、swap、save/load、缓冲访问与比较 API，但操作的是引用缓冲。

实现细节与注意事项
- 错误码：使用 `ERROR_MAKER_BEGIN(