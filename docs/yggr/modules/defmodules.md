# `defmodules.h` 文档

## 概述

`yggr/modules/defmodules.h` 主要用于跨平台动态模块（动态库/插件）加载的句柄类型定义。它根据不同操作系统自动选择合适的模块句柄类型，并包含必要的系统头文件。

该文件是 yggdrasil 框架中所有与动态库（如 Windows 的 DLL、Linux 的 so、macOS 的 dylib）交互的基础类型定义入口。

## 文件位置

- 源文件：`yggr/modules/defmodules.h`
- 本文档：`docs/defmodules.md`

## 主要内容

### 1. 平台适配的头文件包含

- Windows 平台（`YGGR_AT_WINDOWS`）：
  - 包含 `<yggr/network/socket_conflict_fixer.hpp>`（用于修正 socket 宏冲突）。
  - 包含 `<windows.h>`（定义 `HINSTANCE` 等 Windows API 类型）。
- Linux/macOS 平台（`YGGR_AT_LINUX` 或 `YGGR_AT_DARWIN`）：
  - 包含 `<dlfcn.h>`（定义 `dlopen`/`dlclose`/`dlsym` 等动态库操作 API）。
- 其他平台：
  - 预处理报错，提示需补充支持。

### 2. 动态模块句柄类型定义

- 命名空间：`yggr::modules`
- 类型别名：
  - Windows 下：`typedef HINSTANCE module_handle_type;`
  - Linux/macOS 下：`typedef void* module_handle_type;`
  - 其他平台：预处理报错。

该类型用于后续所有动态库加载、卸载、符号查找等 API 的句柄参数。

## 用法说明

- 在需要跨平台加载动态库的代码中，统一使用 `yggr::modules::module_handle_type` 作为模块句柄类型。
- 结合平台相关的加载/卸载 API（如 Windows 的 `LoadLibrary`/`FreeLibrary`，Linux/macOS 的 `dlopen`/`dlclose`）进行动态库管理。
- 通过条件编译保证类型安全和平台兼容。

## 示例

```cpp
#include <yggr/modules/defmodules.h>

using namespace yggr::modules;

module_handle_type handle = nullptr;
#if defined(YGGR_AT_WINDOWS)
    handle = ::LoadLibraryA("myplugin.dll");
#elif defined(YGGR_AT_LINUX) || defined(YGGR_AT_DARWIN)
    handle = ::dlopen("./libmyplugin.so", RTLD_LAZY);
#endif

// ... 使用 handle 进行符号查找等操作 ...
```

## 注意事项

1. **平台宏定义**：
   - 需确保在编译前定义了 `YGGR_AT_WINDOWS`、`YGGR_AT_LINUX` 或 `YGGR_AT_DARWIN` 之一，否则会触发编译错误。
2. **头文件依赖**：
   - Windows 下需先包含 `socket_conflict_fixer.hpp` 以避免与 `<windows.h>` 的宏冲突。
3. **类型安全**：
   - 不同平台的 `module_handle_type` 实际类型不同，跨平台代码应避免直接对句柄做平台相关操作。
4. **扩展性**：
   - 若需支持其他操作系统，需在 `#else` 分支中补充相应的头文件和类型定义。

## 建议测试用例

- 在 Windows、Linux、macOS 下分别编译并测试动态库加载、卸载、符号查找流程。
- 验证未定义平台宏时能正确报错。
- 验证 `module_handle_type` 能与平台 API 正确配合。

## 结语

`defmodules.h` 是 yggdrasil 框架跨平台动态库支持的基础类型定义文件。