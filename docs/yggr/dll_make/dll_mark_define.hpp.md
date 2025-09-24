---
dll_mark_define.hpp 文档

---

# 文件：dll_mark_define.hpp

## 简介

该头文件为 yggdrasil 项目提供了跨平台的动态库导出/导入宏定义。通过统一的宏，简化了 Windows、Linux、macOS 等平台下动态库符号的导出与导入声明，便于开发者编写可移植的动态库接口代码。

## 主要内容

### 版权声明

- 版权：2010-2024 yggdrasil
- 许可协议：MIT License

### 依赖

- `<yggr/base/yggrdef.h>`

### 宏定义

- `YGGR_DLL_API`  
  - Windows 平台：根据 `YGGR_DLL_DEF` 宏，自动切换为 `__declspec(dllexport)` 或 `__declspec(dllimport)`。
  - Linux/macOS 平台：GCC 4 及以上使用 `__attribute__ ((visibility("default")))`，否则为空。
  - 其他平台：编译时报错，提示需自行扩展导出代码。

- `YGGR_MODULE_CALL_T()`  
  - 预留调用约定宏，默认为空，便于后续扩展。

### 命名空间

- `yggr::dll_make`  
  预留命名空间，便于后续扩展。

## 用法示例

```cpp
// 导出函数声明
YGGR_DLL_API void my_exported_func();
```

## 适用场景

- 跨平台动态库开发
- 需要统一导出/导入符号声明的项目
- 支持多平台的动态库接口封装

---
