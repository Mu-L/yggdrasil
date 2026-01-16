**tags.hpp 文档**

简介：
- `tags.hpp` 定义了一组空结构体（tag types），用于在编译期对网络相关类型进行分类标记（例如包类型、传输层协议、角色等）。这些标签仅作为类型占位符，用于类型分派、重载选择或模板特化。

标签说明：
- 包（packet）相关：
  - `tag_pak_static`：表示固定长度/静态包（静态大小或固定格式）。
  - `tag_pak_dynamic`：表示动态包（长度可变或基于头部信息动态解析）。

- 传输/协议相关：
  - `tag_tcp`：表示基于 TCP 的传输类型/套接字。
  - `tag_udp`：表示基于 UDP 的传输类型/套接字。

- 角色相关：
  - `tag_server`：表示服务器端类型/角色。
  - `tag_client`：表示客户端类型/角色。

用途与示例：
- 在模板元编程或策略选择中，使用 `socket_type_checker`、`enable_if`、或函数重载基于标签区分行为：

```cpp
// 假设有 socket_type_checker 已将 MyTcpSocket 映射到 tag_tcp
using tag_t = yggr::network::type_traits::socket_type_checker<MyTcpSocket>::tag;

// 在重载或分派处根据 tag_t 进行选择
template<typename Socket, typename Tag = typename socket_type_checker<Socket>::tag>
void handle_socket(Socket& s, Tag);

void handle_socket(MyTcpSocket& s, yggr::network::type_traits::tag_tcp) { /* TCP-specific */ }
void handle_socket(MyUdpSocket& s, yggr::network::type_traits::tag_udp) { /* UDP-specific */ }
```

注意事项：
- 标签仅为类型标识，不包含运行时数据；选择/分派逻辑需在其它模板或实现文件中完成。
- 保持标签命名清晰以便在大型代码库中快速识别意图（例如 `tag_pak_*`、`tag_*` 前缀区分不同类别）。

相关文件：
- [yggr/network/type_traits/tags.hpp](tags.hpp)
