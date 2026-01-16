# ex_linker.hpp 文档

## 概述
- **文件**: [yggr/network/ex_linker.hpp](yggr/network/ex_linker.hpp#L1-L200)
- **目的**: 提供 `ex_linker` 轻量封装，用于在底层 `Linker`（默认 `tcp_linker` 或可替换为 `udp_linker`）基础上自动调用 service 的 `ex()` 和 `unex()` 扩展方法，从而在构造时进入扩展状态，关闭时退出扩展状态。
- **作者/版权**: 文件头包含 yggdrasil 项目版权与 MIT 风格许可。

## 模板与继承
- `template<typename Config, template<typename _Config> class Linker = tcp_linker>`
  - `Config`：配置类型，传递给底层 `Linker`。
  - `Linker`：模板模板参数，默认为 `tcp_linker`，也可使用 `udp_linker` 或其它满足接口的链路器。
- `ex_linker` 公开继承自 `Linker<Config>`（记作 `base_type`）。

## 重要类型别名
来自 `base_type` 的常用别名在 `ex_linker` 中重新导出：
- `protocol_tag_type`
- `service_type`
- `protocol_type`
- `socket_type`
- `link_address_type`
- `deadline_timer_type`
- `link_init_type`
- `link_type`

这些类型取决于所使用的 `Linker`（如 `tcp_linker`/`udp_linker`）。

## 构造函数
- 在支持 C++11 可变模板参数的情况下：

```cpp
template<typename ...Args>
ex_linker(link_init_type& init, BOOST_FWD_REF(Args)... args)
    : base_type(init, boost::forward<Args>(args)...) {
    base_type::get_service().ex();
}
```

- 对于不支持可变模板（使用预处理宏生成多重重载）的环境，文件使用一组宏（`YGGR_PP_FOO_*` / `BOOST_PP_LOCAL_ITERATE`）生成对应参数数量的构造函数。

行为：构造时先调用 `base_type` 的构造，再调用 `base_type::get_service().ex()`，将服务置为“扩展/ex”状态。

## 析构函数
- 默认析构：`~ex_linker()`（不包含特殊逻辑）。

## 成员函数
- `inline void close(void)`
  - 实现：

```cpp
inline void close(void) {
    base_type::get_service().unex();
    base_type::close();
}
```

  - 作用：先调用 `unex()` 退出服务扩展状态，再调用基类 `close()` 完成链路关闭。

## 使用说明与示例
- 典型用途：当需要临时将服务设置为“扩展”模式（例如改变服务处理逻辑或启用某些功能）时，使用 `ex_linker` 在生命周期内自动管理 `ex()`/`unex()`。

示例：

```cpp
// 假设存在 config_type 与 link_init_type 定义，并使用默认 tcp_linker
link_init_type init = /* ... */;
ex_linker<config_type> linker(init, /* 其它构造参数 */);
// 构造后, base_type::get_service().ex() 已被调用

// 使用链路...

linker.close(); // 会先调用 unex() 然后关闭
```

- 如果需要使用 UDP：

```cpp
ex_linker<config_type, udp_linker> udp_ex_linker(init, ...);
```

## 依赖关系
- 包含头文件：
  - `yggr/ppex/foo_params.hpp`（用于在无可变模板时生成参数列表）
  - `yggr/network/tcp_linker.hpp`
  - `yggr/network/udp_linker.hpp`
- 依赖宏/库：Boost（用于 `BOOST_FWD_REF`, `boost::forward`，以及 Boost.Preprocessor 宏展开）。

## 注意事项
- `ex_linker` 假定基类 `Linker<Config>` 提供：
  - `get_service()` 返回一个具有 `ex()` 与 `unex()` 方法的服务对象；
  - 合适的构造函数签名以接受 `link_init_type` 与其余参数；
  - `close()` 成员函数用于关闭链路。
- 在多线程/异步环境下，`ex()`/`unex()` 的语义应保证线程安全或由调用方确保正确的同步。

## 参考
- 源代码： [yggr/network/ex_linker.hpp](yggr/network/ex_linker.hpp#L1-L200)

---
