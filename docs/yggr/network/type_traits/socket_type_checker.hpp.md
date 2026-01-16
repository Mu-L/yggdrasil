**socket_type_checker.hpp 文档**

简介：
- `socket_type_checker.hpp` 提供了用于将具体套接字类型映射到类别标签（tag）的轻量型检查/注册机制。通过对 `socket_type_checker<T>` 进行显式特化，可以在类型层面为套接字类型关联一个 `tag`，便于在编译期进行类型分派或策略选择。

主要内容：

- 宏 `YGGR_PP_SOCKET_TYPE_CHECKER_DEF(__type__, __tag__)`：
  - 快速为某个套接字类型 `__type__` 生成 `socket_type_checker<__type__>` 的特化。
  - 生成的特化包含两个别名：`type`（指向原类型）和 `tag`（指向对应的类别标签类型）。

- 前置声明：
  - 模板 `template<typename Socket> struct socket_type_checker;` 在本文件中声明，但未提供默认实现，意在由用户或库的其它头文件通过宏/显式特化来注册具体类型。

用途与示例：

1) 假设存在类别标签 `stream_socket_tag` 与 `datagram_socket_tag`（在 `tags.hpp` 中定义），为 `my_tcp_socket` 注册标签：

```cpp
YGGR_PP_SOCKET_TYPE_CHECKER_DEF(my_tcp_socket, yggr::network::type_traits::stream_socket_tag)

// 使用处：
typedef yggr::network::type_traits::socket_type_checker<my_tcp_socket>::tag tag_t;
static_assert(std::is_same<tag_t, yggr::network::type_traits::stream_socket_tag>::value, "tag matches");
```

2) 在泛型代码中可以根据 `socket_type_checker<Socket>::tag` 进行重载或选择器分支，从而在编译期为不同类别的 socket 使用不同实现。

注意事项：
- 本文件只定义了声明与宏，实际的特化应在与具体 socket 类型相关的实现文件或适配层中提供。
- 确保 `tags.hpp` 中定义的标签类型在注册时可见。

相关文件：
- [yggr/network/type_traits/socket_type_checker.hpp](socket_type_checker.hpp)
- [yggr/network/type_traits/tags.hpp](tags.hpp)
