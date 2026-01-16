# plugins_installer.hpp

概述
- 提供 `plugins_installer<Modules_Manager>` 模板类，作为插件模块安装/卸载的便捷封装。
- 依赖 `Modules_Manager` 提供的模块注册/查询/删除接口（如 `get_entry<Ptr>(module_name, entry_name)`、`erase_module`、`clear`、`using_handler` 等）。

模板参数
- `Modules_Manager`：模块管理器类型，必须实现：
  - `template<typename Ptr> get_entry(const yggr::string& module_name, const yggr::string& entry_name)`：返回模块入口的指针/句柄。
  - `erase_module(const yggr::string& module_name)`：移除模块。
  - `clear()`：清除所有模块。
  - `using_handler(Handler)`：对当前所有模块执行 handler（可选重载）。

主要方法
- `install<Ptr, Handler>(module_name, handler)`：使用默认入口名 "module_enrty"（注意拼写）安装单个模块，调用 `handler(get_entry<Ptr>(module_name, entry_name))`。
- `install<Ptr, Handler>(module_name, entry_name, handler)`：按指定入口名安装模块。
- `install<Ptr, Plugin_names, Handler>(names, handler)`：批量安装；`names` 为容器，每个元素应为可用 `yggr::get<0>`/`yggr::get<1>` 访问到 `module_name` 和 `entry_name` 的元组/对。

- `uninstall(module_name)`：直接根据模块名删除模块（不调用 handler）。
- `uninstall<Ptr, Handler>(module_name, handler)`：（实现上调用了 `install<Ptr,Handler>`，似乎是笔误；请注意）
- `uninstall<Ptr, Handler>(module_name, entry_name, handler)`：调用 `handler(get_entry<Ptr>(module_name, entry_name))` 后移除模块。
- `uninstall<Ptr, Plugin_names, Handler>(names, handler)`：批量卸载：对每个名称调用 handler 并移除模块。
- `uninstall_all()`：清空所有模块。
- `uninstall_all(Handler)`：将 handler 用于 `_modules_mgr.using_handler(handler)`（在移除前对所有模块执行回调）。

注意事项与潜在问题
- 默认入口名为字符串字面量 "module_enrty"，该拼写可能为 `module_entry` 的笔误；请确认 `Modules_Manager` 是否使用相同拼写，否则 `install`/`uninstall` 的默认重载将查找失败。
- `uninstall(const yggr::string& module_name, Handler handler)` 的实现调用了 `install<Ptr, Handler>`，这看起来像复制粘贴错误，应当改为调用对应 uninstall 重载或直接执行 handler+erase。
- `install`/`uninstall` 的批量版本期望 `names` 元素是二元结构（例如 `std::pair` 或 `yggr::tuple`），使用 `yggr::get<0>` / `yggr::get<1>` 访问模块名与入口名。
- `Modules_Manager` 的 `get_entry` 模板参数 `Ptr` 用于指定返回的指针/句柄类型，调用者应确保 `Ptr` 与管理器的注册类型一致。

示例（伪代码）

```cpp
typedef my_modules_manager mgr_t;
plugins_installer<mgr_t> installer;

installer.install<std::shared_ptr<MyPlugin>>("my_mod", [](std::shared_ptr<MyPlugin> p){ if(p) p->start(); });

installer.uninstall("my_mod");

// 批量安装
std::vector<std::pair<yggr::string, yggr::string>> names = { {"mod1", "entry"}, {"mod2", "entry"} };
installer.install<std::shared_ptr<MyPlugin>>(names, [](auto p){ /* handle */ });
```

文件
- 源文件：plugins_installer.hpp（位于 `yggr/plugins` 目录）。

----
自动生成：基于 yggr/plugins/plugins_installer.hpp 的概要文档。