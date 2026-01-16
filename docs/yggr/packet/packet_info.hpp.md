# packet_info_vtpl.hpp

概述
- 定义并实现变参模板 `packet_info<...>`，作为一组参数的类型-安全容器与适配器，用于网络包的元信息描述与传递。
- 依赖 C++11 可变参数模板（文件在无 variadic 支持时会报错），并与 `yggr::tuple` / `boost::tuple` 互操作。

模板与类型
- `template<typename ...Val> class packet_info`：
  - 将 `Val...` 过滤掉尾部的 `yggr::tuples::null_type`，通过 Boost.MPL 计算有效参数列表 `vt_t_type`。
  - `E_length`：参数个数（size_type）。
  - `params_type` / `value_type` / `base_type`：内部使用的 MPL 列表、`yggr::tuple` 类型和基类类型（通过 conv_to_yggr_tuple）。
  - 提供 `arg<N>`、`t_arg<T>`、`t_arg<T,idx>` 等元信息访问模板，用于索引/按类型查找参数索引。

构造/赋值/交换
- 支持多种构造：直接传参数、从 `boost::tuple` / `yggr::tuple` / 其他 `packet_info` 迁移或拷贝构造。
- 赋值运算符支持从上述类型进行移动或复制赋值，内部用 `copy_or_move_or_swap` 兼容移动语义。
- `swap` 提供多种重载以与 `boost::tuple`、`yggr::tuple`、其它 `packet_info` 互换数据。

元素访问
- `get<N>()`：按索引获取元素。
- `get<T>()`：按类型获取元素（需要能在参数列表中唯一定位类型，或提供 `t_arg` 模板明确索引）。
- `arg_get<Arg>()` / `t_arg_get<T_Arg>()`：按元信息类型获取元素引用。
- `element_size()` 返回参数个数。
- `clear()` 将内部 tuple 重置为默认值。

比较与转换
- `compare` / `compare_eq`：与 `boost::tuple`、`yggr::tuple`、以及其他 `packet_info` 互相比较，使用基类 tuple 的比较运算。
- 提供 `operator==` / `operator!=` 的非成员全套重载，支持跨类型比较（任意组合的 `boost::tuple` / `yggr::tuple` / `packet_info`）。
- `operator<<` / `operator>>` 支持流式 IO（输出显示 `packet_info` 与内部 tuple）。
- `make_packet_info(args...)`：静态工厂函数，构造并返回 `packet_info`。

哈希与 STL 兼容
- 提供 `hash_value` 与 `std::hash`（当支持时）特化，使用 `boost::hash` 对内部 `value_type` 进行哈希，便于放入 unordered 容器。

辅助工具 `packet_info_op`
- `packet_info_op`（不可创建的工具类）提供：
  - `compare<Idx...>(pak_info, args...)`：按索引列表比较 `pak_info` 的对应元素与 `args...`。
  - `compare<Idx...>(handler, pak_info, args...)`：接受 handler（可调用）进行自定义比较/处理，返回 handler 的返回值。
  - `get_sub_infos<Idx...>(info)`：按索引返回 `yggr::tuple` 子集。
  - `get_sub_packet_info<Idx...>(info)`：生成并返回一个新的 `packet_info`，包含所选索引的元素。

兼容性与实现细节
- 使用 Boost.MPL 进行参数列表处理并删除尾部的 `null_type`。
- 与 `yggr::tuple`/`boost::tuple` 无缝互操作（构造、赋值、比较、swap）。
- 在泛型比较中支持将 handler 做为可调用对象，要求 `func::foo_t_info<Handler>::is_callable_type::value` 为真。

示例（伪代码）

```cpp
typedef packet_info<int, std::string, float> pkt_info_t;
pkt_info_t info(1, "hello", 3.14f);
int x = info.get<0>();
std::string s = info.get<std::string>();

if(packet_info_op::compare<0,2>(info, 1, 3.14f)) { /* match */ }

auto sub = packet_info_op::get_sub_packet_info<1>(info); // packet_info<std::string>
```

文件
- 源文件：`packet_info_vtpl.hpp`（位于 `yggr/packet/detail`）。
- 相关：`packet_info.hpp`（公共头），`reference_trans`，`mplex::conv_to_yggr_tuple` 等。

----
自动生成：基于 yggr/packet/detail/packet_info_vtpl.hpp 的概要文档。