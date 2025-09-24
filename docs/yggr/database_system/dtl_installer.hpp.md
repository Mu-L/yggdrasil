---
`dtl_installer.hpp` 文档

# 文件概述

该头文件定义了 `yggr::database_system::dtl_installer` 工具类，用于管理 DTL（Database Template Library）全局环境和连接的初始化与释放。该类为数据库系统提供了统一的 DTL 安装与卸载接口，便于资源管理和生命周期控制。

---

## 命名空间

- `yggr::database_system`

---

## 主要类

### `dtl_installer`

- 禁止创建实例（继承自 `nonable::noncreateable`）。
- 仅提供静态方法。

#### 主要静态方法

- `install()`  
  DTL 安装入口。

- `uninstall()`  
  DTL 卸载入口。释放 DTL 全局默认连接和环境，防止资源泄漏。

---

## 技术要点

- **全局资源管理**：通过静态方法统一管理 DTL 全局资源的初始化与释放。
- **安全性**：`uninstall()` 确保 DTL 全局连接和环境被正确释放，避免内存泄漏。
- **兼容性**：`install()` 和mongodb初始化拥有同样的形式，为模板函数的包装提供兼容。

---

## 适用场景

- 需要在应用程序启动和关闭时统一管理 DTL 全局资源的项目。
- 需要防止 DTL 相关资源泄漏、提升系统健壮性的数据库应用。

---

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法，请参考 `install()` 和 `uninstall()` 静态方法的调用方式。