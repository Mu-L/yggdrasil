**session_killer.hpp 文档**

简介：
- `session_killer` 是一个用于销毁/移除会话的简单策略函数对象（functor）。它对会话管理器或连接指针执行清理操作，常用于会话插入/替换流程的回滚或失败处理路径。

模板参数：
- `Session`：会话类型，要求提供类型别名 `conn_ptr_type` 与 `conn_type`。

主要行为：
- 提供两个重载 `operator()`：
  - `operator()(const Key& key, Session_Mgr& smgr)`: 通过 `smgr.remove(key)` 从会话管理器移除会话（按 key）。
  - `operator()(conn_ptr_type pconn, Session_Mgr& smgr)`: 接受连接指针，若非空则调用 `pconn->close()`，用于直接关闭底层连接。

用途与约定：
- 第一个重载通常在需要按键从管理器中删除（撤销）会话条目时使用。
- 第二个重载通常在会话尚未成功插入管理器但需要关闭底层连接时使用（例如在创建会话失败或取消时）。

示例（伪代码）：

```cpp
using killer = yggr::network::session_helper::session_killer<MySession>;
killer k;

// 从 session manager 中移除
k(some_key, session_mgr);

// 直接关闭连接
k(conn_ptr, session_mgr);
```

注意事项：
- `Session_Mgr` 类型需提供 `remove(const Key&)` 方法以配合第一个重载。
- `conn_ptr_type` 的 `close()` 方法应能安全地释放/关闭底层资源。
- 文件中使用了静态断言与类型检查的包含头（`yggr/mplex/static_assert.hpp`、`boost::is_same`），表明在更严格使用场景下可能会对类型兼容性做额外验证。

文件： [yggr/network/session_helper/session_killer.hpp](session_killer.hpp)
