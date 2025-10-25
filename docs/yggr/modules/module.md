# `module.hpp` 文档

## 概述

`yggr/modules/module.hpp` 提供了跨平台动态模块（动态库/插件）加载与管理的面向对象封装。核心为 `yggr::modules::module` 类，负责动态库的加载、卸载、符号查找、资源管理与句柄封装。

该类适配 Windows、Linux、macOS 等主流平台，底层依赖 `defmodules.h` 统一句柄类型，并通过 `modules_accesser` 进行实际的动态库操作。

## 文件位置

- 源文件：`yggr/modules/module.hpp`
- 本文档：`docs/module.md`

## 主要类型与接口

### 1. `yggr::modules::module` 类

#### 主要成员
- `yggr::string _name;`：模块名（动态库文件名）。
- `module_handle_type _handle;`：动态库句柄（平台相关类型）。

#### 构造与析构
- `module()`：默认构造，未加载任何模块。
- `module(const yggr::string& module_name, int mode = 1)`：指定模块名与加载模式构造并尝试加载。
- 移动构造/拷贝构造均支持。
- 析构时自动释放已加载模块。

#### 赋值与 swap
- 移动赋值、拷贝赋值均支持。
- `swap()`：与另一个 `module` 实例交换资源。

#### 加载与卸载
- `bool load(const yggr::string& module_name, int mode = 1)`：加载指定模块。
- `void close()`：卸载当前模块。

#### 查询与符号查找
- `bool empty() const`：模块是否未加载。
- `void* get_entry(const yggr::string& name) const`：查找符号（如函数指针）。
- `template<typename FOO_PTR> FOO_PTR get_entry(const yggr::string& name) const`：类型安全的符号查找。

#### 比较
- `bool compare_eq(const yggr::string& name) const`：与模块名比较。
- `bool compare_eq(const module& right) const`：与另一个模块对象比较。
- 非成员重载：`==`/`!=` 支持与字符串、模块对象的比较。

### 2. swap 支持
- 提供 `swap(module&, module&)`，并通过 ADL 导出到 `std`、`boost` 命名空间。

## 用法示例

```cpp
#include <yggr/modules/module.hpp>

using namespace yggr::modules;

int main() {
    module mod;
    if (mod.load("myplugin.dll")) {
        using func_ptr = int(*)(int);
        func_ptr foo = mod.get_entry<func_ptr>("foo_func");
        if (foo) {
            int result = foo(42);
        }
        mod.close();
    }
    return 0;
}
```

## 注意事项

1. **资源管理**：
   - 析构时自动释放模块句柄，但建议显式调用 `close()` 以便及时释放资源。
2. **平台兼容性**：
   - 依赖 `defmodules.h` 统一句柄类型，实际加载/卸载/查找由 `modules_accesser` 实现，需保证相关实现已适配目标平台。
3. **符号查找安全**：
   - `get_entry` 支持类型安全模板重载，建议优先使用模板版本。
4. **拷贝/移动语义**：
   - 支持拷贝与移动，但注意模块句柄的所有权与生命周期。
5. **比较操作**：
   - `==`/`!=` 支持与字符串和模块对象的比较，便于容器查找与判等。

## 建议测试用例

- 加载/卸载不同平台下的动态库，查找符号并调用。
- 验证拷贝/移动构造与赋值后资源管理是否正确。
- 多模块对象 swap 后句柄与名称是否正确交换。
- 比较操作与容器查找。

## 结语

`module.hpp` 是 yggdrasil 框架跨平台动态库管理的核心封装。