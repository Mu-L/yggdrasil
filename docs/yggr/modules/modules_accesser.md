# `modules_accesser.hpp` 文档

## 概述

`yggr/modules/modules_accesser.hpp` 提供了跨平台动态模块（动态库/插件）加载、卸载和符号查找的静态工具类接口。核心为 `yggr::modules::modules_accesser`，它以静态成员函数形式封装了动态库的加载、释放、符号获取及错误处理，适配 Windows、Linux、macOS 等主流平台。

该类禁止实例化（继承自 `nonable::noncreateable`），所有接口均为 static。

## 文件位置

- 源文件：`yggr/modules/modules_accesser.hpp`
- 本文档：`docs/modules_accesser.md`

## 主要类型与接口

### 1. 错误处理
- 内嵌错误码定义（`ERROR_MAKER_BEGIN` 宏）：
  - `E_invalid_module`：无效模块。
  - `E_invalid_module_entry`：无效模块符号。
- 错误码与消息可通过 `error_type` 获取。

### 2. 静态接口

#### 模块加载与释放
- `static module_handle_type load_module(const yggr::string& module_name, int mode = 1);`
  - 加载指定名称的动态库，返回句柄。
- `static module_handle_type load_module(error_type& e, const yggr::string& module_name, int mode = 1);`
  - 带错误码返回的加载。
- `static void free_module(module_handle_type handle);`
  - 释放动态库。

#### 符号查找
- `static void* get_entry(module_handle_type handle, const yggr::string& entry_name);`
  - 查找符号（如函数指针），失败时抛出异常。
- `static void* get_entry(error_type& e, module_handle_type handle, const yggr::string& entry_name);`
  - 查找符号，失败时通过 error_type 返回错误。
- `template<typename FOO_PTR> static FOO_PTR get_entry(module_handle_type handle, const yggr::string& entry_name);`
  - 类型安全的符号查找，失败时抛出异常。
- `template<typename FOO_PTR> static FOO_PTR get_entry(error_type& e, module_handle_type handle, const yggr::string& entry_name);`
  - 类型安全查找，失败时通过 error_type 返回错误。

#### 平台适配
- Windows 下使用 `LoadLibraryA`/`FreeLibrary`/`GetProcAddress`。
- Linux/macOS 下使用 `dlopen`/`dlclose`/`dlsym`。
- 错误处理分别获取系统错误码与消息。

## 用法示例

```cpp
#include <yggr/modules/modules_accesser.hpp>

using namespace yggr::modules;

int main() {
    module_handle_type handle = modules_accesser::load_module("myplugin.dll");
    if (handle) {
        using func_ptr = int(*)(int);
        func_ptr foo = modules_accesser::get_entry<func_ptr>(handle, "foo_func");
        if (foo) {
            int result = foo(42);
        }
        modules_accesser::free_module(handle);
    }
    return 0;
}
```

## 注意事项

1. **禁止实例化**：
   - `modules_accesser` 仅提供静态接口，不能被实例化。
2. **异常与错误码**：
   - 查找符号失败时可选择抛出异常或通过 error_type 返回错误，建议根据业务场景选择。
3. **平台兼容性**：
   - 需保证 `defmodules.h`、相关平台头文件和宏定义正确。
   - 其他平台需补充适配代码。
4. **符号查找安全**：
   - 建议优先使用模板版本 `get_entry<FOO_PTR>`，可获得类型安全的函数指针。
5. **资源管理**：
   - 加载后需及时调用 `free_module` 释放资源。
6. **错误信息**：
   - Windows 下通过 `GetLastError` 和 `FormatMessage` 获取详细错误信息。
   - Linux/macOS 下通过 `dlerror` 获取错误信息。

## 建议测试用例

- 加载/卸载不同平台下的动态库，查找符号并调用。
- 验证异常与 error_type 错误码的正确性。
- 测试类型安全查找与普通查找的行为。
- 验证错误信息的准确性。

## 结语

`modules_accesser.hpp` 是 yggdrasil 框架跨平台动态库操作的底层工具类。