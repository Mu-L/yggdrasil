---
# pragma_message.hpp 文档

## 文件简介

pragma_message.hpp 提供了跨平台、跨编译器的编译期消息输出宏 `YGGR_PRAGMA_MESSAGE`，用于在编译过程中输出自定义提示、警告或信息。该文件自动适配 Boost 版本和主流编译器，保证在不同环境下都能安全、统一地输出编译期消息，便于调试和配置提示。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<boost/version.hpp>`
- Boost 1.67.0 及以上：`<boost/config/pragma_message.hpp>`

---

## 主要内容

### 1. 宏定义与适配

- **YGGR_DISABLE_PRAGMA_MESSAGE**  
  若 Boost 禁用 `PRAGMA_MESSAGE`，则同步禁用 Yggdrasil 的消息宏。

- **YGGR_PRAGMA_MESSAGE(x)**  
  编译期消息输出宏。根据 Boost 版本和编译器自动适配：
  - Boost 1.67.0 及以上：直接使用 `BOOST_PRAGMA_MESSAGE`
  - Boost 1.67.0 以下：根据编译器分别实现
    - MSVC/Intel：`__pragma(message(...))`
    - GCC：`_Pragma("message(...)")`
    - 其他：空操作

- **YGGR_TMP_STRINGIZE(X)**  
  辅助宏，将参数转为字符串，用于拼接消息内容。

### 2. 用法说明

- 在代码中插入 `YGGR_PRAGMA_MESSAGE("你的提示信息")`，即可在编译时输出自定义信息。
- 支持输出当前文件名和行号（MSVC/Intel）。

---

## 用法示例

````cpp
#include <yggr/base/pragma_message.hpp>

YGGR_PRAGMA_MESSAGE("编译到此处，检查配置！")
````

编译时会在输出窗口看到类似：
```
e:\path\to\file.hpp(42): note: 编译到此处，检查配置！
```

---

## 注意事项

- 若定义了 `BOOST_DISABLE_PRAGMA_MESSAGE` 或 `YGGR_DISABLE_PRAGMA_MESSAGE`，则该宏为空操作。
- 推荐用于配置检测、特性提示、弃用警告等场景。

---

 

