---
dll_make_begin.ipp 文档

---

# 文件：dll_make_begin.ipp

## 简介

该文件为 yggdrasil 项目提供了动态库导出接口的 C 语言链接规范起始声明。主要用于在 C++ 代码中确保后续导出符号采用 C 语言方式链接，避免名称修饰（Name Mangling）问题，便于动态库接口的跨语言调用。

## 主要内容

### 版权声明

- 版权：2010-2024 yggdrasil
- 许可协议：MIT License

### 功能说明

- 检查是否为 C++ 环境，如果是，则插入 `extern "C" {`，为后续接口声明开启 C 语言链接规范。
- 通常与 `dll_make_end.ipp` 文件配合使用，形成完整的 `extern "C" { ... }` 包裹区域。

### 用法示例

```cpp
#include "dll_make_begin.ipp"

// 这里声明的所有函数都将以 C 语言方式导出
void my_exported_func();

#include "dll_make_end.ipp"
```

## 适用场景

- 需要导出 C 接口的 C++ 动态库
- 跨语言调用（如 Python、C#、Java 等调用 C++ 动态库）
- 保证导出符号无 C++ 名称修饰

---


