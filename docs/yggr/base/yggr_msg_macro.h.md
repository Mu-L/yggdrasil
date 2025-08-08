---
# yggr_msg_macro.h 文档

## 文件简介

yggr_msg_macro.h 提供了调试环境下的消息输出宏，主要用于输出性能警告和异常信息。该文件通过条件编译，在 Debug 模式下输出详细信息，在 Release 模式下宏为空操作。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`
- `<iostream>`（仅 Debug 模式）
- `<string>`（仅 Debug 模式）

---

## 主要宏定义

### __YGGR_MSG_PCRE_WARNING(__msg__)

- **作用**：在 Debug 模式下，将 `__msg__` 作为 PCRE 警告信息输出到标准错误流（`std::cerr`）。
- **Release 模式下**：为空操作。

### __YGGR_MSG_EXCEPTION(__msg__)

- **作用**：在 Debug 模式下，将 `__msg__` 作为异常信息输出到标准错误流（`std::cerr`）。
- **Release 模式下**：为空操作。

### YGGR_MSG_PCRE_WARNING

- **作用**：对 `__YGGR_MSG_PCRE_WARNING` 的别名，便于统一调用。

---

## 用法示例

````cpp
#include <yggr/base/yggr_msg_macro.h>

void foo() {
    YGGR_MSG_PCRE_WARNING("性能警告示例");
    __YGGR_MSG_EXCEPTION("异常信息示例");
}
````

- 在 Debug 模式下，以上代码会输出警告和异常信息到标准错误流。
- 在 Release 模式下，宏不会产生任何输出。

---

## 注意事项

- 仅在 `_DEBUG` 宏定义时（即 Debug 编译）宏才会输出信息。
- 推荐仅用于调试和开发阶段，避免在生产环境依赖这些宏进行日志输出。

---

 

