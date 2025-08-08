---
# script_python_cfg.hpp 文档

## 文件简介

script_python_cfg.hpp 用于为 Yggdrasil 工程中的 Python 脚本集成预留配置入口。该文件目前主要用于头文件包含保护和依赖检测，便于后续扩展 Python 相关的兼容性宏或配置项。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- 必须先包含 `<yggr/base/yggrdef.h>`，否则编译报错。

---

## 主要内容

### 1. 头文件包含保护

- 防止重复包含，定义了 `__YGGR_BASE_SCRIP_TPYTHON_CFG_HPP__` 宏。

### 2. 依赖检测

- 若未先包含 `yggrdef.h`，则编译报错，确保类型和基础配置一致。

### 3. 预留扩展

- 当前未定义具体的 Python 兼容性宏或配置项，便于后续根据实际需求扩展。

---

## 用法说明

- 推荐在所有 Python 脚本集成相关代码之前包含本文件，便于后续统一管理 Python 相关配置。

````cpp
#include <yggr/base/script_python_cfg.hpp>
#include <Python.h>
````

---

## 注意事项

- 必须先包含 `<yggr/base/yggrdef.h>`，否则会编译报错。
- 该文件为扩展预留，后续可根据 Python 版本或集成需求添加宏定义。

---

 

