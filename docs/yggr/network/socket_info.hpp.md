# socket_info.hpp

概述
- 模板类 `socket_info<Host, Port>` 封装主机地址与端口对，作为网络层的轻量值对象。
- 适用于表示本地或远端地址/端口并在容器、哈希或序列化场景中使用。

模板参数
- `Host`：主机地址类型（例如 `boost::asio::ip::address`、字符串或自定义地址类型）。
- `Port`：端口类型（例如 `u16`、字符串可转换为端口的类型）。

关键成员与构造
- 构造函数：
  - 默认构造：`socket_info()` 初始化 host/port 的默认值。
  - 模板构造：`socket_info(const OHost& ip, const OPort& port)` 支持隐式可转换的 host/port 类型构造。
  - 拷贝/移动构造与赋值都受支持（使用 `BOOST_COPYABLE_AND_MOVABLE` 与 `copy_or_move_or_swap`）。
- 成员访问：`host()` / `port()` 提供读写访问（返回引用或 const 引用）。
- `swap()`：支持成员交换和全局 `swap` 覆盖（在 `swap_support` 中定义并导入到 `std`/`boost` 命名空间）。

比较与排序
- `compare_eq`：比较 host 与 port 是否相等（模板版本允许不同 Host/Port 类型的比较）。
- `compare` / `operator<`：按 host 首先比较，host 相同则比较 port，返回 -1/0/1 或用作 `<`/`<=`/`>`/`>=` 运算。
- 非成员比较运算符：`==, !=, <, <=, >, >=` 都已重载并委托到类内比较函数。

哈希与序列化
- `hash()`：使用 `boost::hash_combine` 对 host 与 port 做哈希，返回 size_t，用于 unordered 容器。
- `hash_value` 与 `std::hash` 特化（若可用）已实现，便于与 Boost/Std 哈希兼容。
- 序列化：使用 `yggr::serialization::access` 与 `YGGR_SERIALIZATION_NVP` 宏序列化 `_host` 与 `_port`。

流输出
- 支持 `operator<<`，按格式 `host:port` 输出到任意字符流（`std::basic_ostream<Char, Traits>&`）。

实现细节与注意
- 对赋值与交换实现使用了 `copy_or_move_or_swap` 辅助以兼容移动语义与无移动环境。
- 模板构造与比较允许 Host/Port 使用不同但可比较/可赋值的类型（例如 string 与 boost::address）。
- `hash()` 使用 `boost::hash_combine`，请确保 `Host` 与 `Port` 类型可被 `boost::hash` 处理或自定义 `hash_value`。
- `operator<` 返回 `s32` 便于在需要三态比较结果的内部逻辑中使用，但非成员 `<` 运算符仍基于 `compare < 0`。

示例（伪代码）

```cpp
#include <boost/asio/ip/address.hpp>
using sock_info = yggr::network::socket_info<boost::asio::ip::address, unsigned short>;

sock_info a(boost::asio::ip::address::from_string("127.0.0.1"), 8080);
sock_info b("127.0.0.1", 8080); // 依赖可转换构造

if(a == b) { /* 相等 */ }

std::unordered_map<sock_info, std::string> mp;
mp[a] = "local"; // 需要 C++11 std::hash 或 boost::hash 支持

std::cout << a << std::endl; // 输出 127.0.0.1:8080
```

文件
- 源文件：socket_info.hpp（位于同目录），建议查看以了解移动语义与序列化细节。

----
