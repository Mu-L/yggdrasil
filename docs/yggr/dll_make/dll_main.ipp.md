---
dll_main.ipp 文档

---

# 文件：dll_main.ipp

## 简介

该文件为 yggdrasil 项目提供了动态库（DLL/SO）入口函数的实现模板，主要用于 Windows 平台下的 DLL 主入口 `DllMain` 的定义，并对 Linux 和 macOS 平台做了适配提示。此文件便于跨平台动态库开发时统一入口处理。

## 主要内容

### 版权声明

- 版权：2010-2024 yggdrasil
- 许可协议：MIT License

### 平台支持

- **Windows**  
  实现了标准的 `DllMain` 函数，处理 DLL 加载、线程附加/分离、进程分离等事件。  
  - 在 Debug 模式下，会输出当前事件类型到标准输出，便于调试。
  - 在 Release 模式下，仅做事件分发，无输出。

- **Linux / Darwin (macOS)**  
  明确标注“不需要定义入口”，即动态库无需特殊入口函数。

- **其他平台**  
  编译时报错，提示需自行实现入口代码。

### 依赖

- `<yggr/network/socket_conflict_fixer.hpp>`
- `<windows.h>`
- `<iostream>`（仅 Debug 模式）

## 用法说明

- 适用于需要自定义 DLL 入口行为的 Windows 动态库项目。
- 直接包含本文件即可获得标准的 DLL 入口实现。
- 非 Windows 平台无需特殊处理，或可根据提示自行扩展。

## 适用场景

- 跨平台动态库开发
- 需要统一管理 DLL 生命周期事件（如资源初始化/释放、调试输出等）

---


