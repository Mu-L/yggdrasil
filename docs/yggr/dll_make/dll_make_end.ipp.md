---
dll_make_end.ipp 文档

---

# 文件：dll_make_end.ipp

## 简介

该文件为 yggdrasil 项目提供了动态库导出接口的 C 语言链接规范结束声明。主要用于在 C++ 代码中关闭 `extern "C"` 区域，与 dll_make_begin.ipp 配合使用，确保导出符号采用 C 语言方式链接，便于动态库接口的跨语言调用。

## 主要内容

### 版权声明

- 版权：2010-2024 yggdrasil
- 许可协议：MIT License

### 功能说明

- 检查是否为 C++ 环境，如果是，则插入 `}`，用于结束 `extern "C" {` 区域。
- 通常与 dll_make_begin.ipp 文件配合使用，形成完整的 `extern "C" { ... }` 包裹区域。

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


