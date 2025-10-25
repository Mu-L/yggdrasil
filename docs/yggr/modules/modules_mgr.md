# `modules_mgr.hpp` 文档

## 概述

`yggr/modules/modules_mgr.hpp` 提供了一个线程安全的动态模块（动态库/插件）集中管理器 `yggr::modules::modules_mgr`，用于统一加载、缓存、查找、卸载和符号获取多个动态库。该类适合插件系统、模块化应用等需要动态扩展的场景。

## 文件位置

- 源文件：`yggr/modules/modules_mgr.hpp`
- 本文档：`docs/modules_mgr.md`

## 主要类型与接口

### 1. 类型定义
- `module_type`：模块对象类型（即 `yggr::modules::module`）。
- `module_ptr_type`：模块智能指针类型（`shared_ptr<module_type>`）。
- 内部容器：`safe_unordered_map<yggr::string, module_ptr_type>`，保证线程安全。

### 2. 构造与析构
- `modules_mgr()`：构造函数，初始化模块管理容器。
- `~modules_mgr()`：析构函数，自动清理所有已加载模块。

### 3. 模块管理接口
- `module_ptr_type get_module(const yggr::string& name, int mode = 1)`
  - 获取指定名称的模块，若未加载则自动加载并缓存。
  - 线程安全，内部使用 `safe_unordered_map` 的 find+handler 机制。
- `module_ptr_type get_exists_module(const yggr::string& name)`
  - 获取已存在的模块（不自动加载）。
- `this_type& erase_module(const yggr::string& name)`
  - 卸载并移除指定模块。
- `this_type& clear()`
  - 卸载并清空所有模块。

### 4. 符号查找接口
- `void* get_entry(const yggr::string& module_name, const yggr::string& entry_name)`
  - 获取指定模块的符号（如函数指针），自动加载模块。
- `template<typename FOO_PTR> FOO_PTR get_entry(const yggr::string& module_name, const yggr::string& entry_name)`
  - 类型安全的符号查找。
- `void* get_exists_entry(const yggr::string& module_name, const yggr::string& entry_name)`
  - 仅在模块已加载时查找符号。
- `template<typename FOO_PTR> FOO_PTR get_exists_entry(const yggr::string& module_name, const yggr::string& entry_name)`
  - 类型安全，仅查找已加载模块。

### 5. 内部机制
- 所有加载、查找、卸载操作均为线程安全。
- 自动缓存已加载模块，避免重复加载。
- 支持通过 `modules_accesser::error_type` 捕获底层加载/查找异常。

## 用法示例

```cpp
#include <yggr/modules/modules_mgr.hpp>

using namespace yggr::modules;

int main() {
    modules_mgr mgr;
    // 自动加载并缓存模块
    auto mod_ptr = mgr.get_module("myplugin.dll");
    if (mod_ptr) {
        using func_ptr = int(*)(int);
        func_ptr foo = mgr.get_entry<func_ptr>("myplugin.dll", "foo_func");
        if (foo) {
            int result = foo(42);
        }
    }
    // 卸载单个模块
    mgr.erase_module("myplugin.dll");
    // 清空所有模块
    mgr.clear();
    return 0;
}
```

## 注意事项

1. **线程安全**：
   - 内部使用 `safe_unordered_map`，可在多线程环境下安全加载/查找/卸载模块。
2. **异常处理**：
   - 加载和查找符号时可能抛出 `modules_accesser::error_type` 异常，建议用 try-catch 包裹调用。
3. **自动缓存**：
   - `get_module` 会自动缓存已加载模块，避免重复加载。
4. **资源释放**：
   - `erase_module` 和 `clear` 会自动卸载模块并释放资源。
5. **类型安全**：
   - 建议优先使用模板版本的 `get_entry`，可获得类型安全的函数指针。
6. **仅查找已加载模块**：
   - `get_exists_module` 和 `get_exists_entry` 只操作已存在的模块，不会自动加载。

## 建议测试用例

- 多线程并发加载、查找、卸载模块。
- 验证自动缓存与重复加载行为。
- 验证异常捕获与错误处理。
- 验证类型安全查找与普通查找的行为。

## 结语

`modules_mgr.hpp` 是 yggdrasil 框架插件/模块系统的核心管理器，适合需要动态扩展和高并发场景。