---
tool_buf_size.hpp 文档

---

# tool_buf_size.hpp 文档

## 概述

tool_buf_size.hpp 提供了加密工具缓冲区大小的类型萃取模板 `tool_buf_size`，以及相关的宏定义，便于为不同加密工具类型统一获取其缓冲区大小（如摘要长度、签名长度等），常用于泛型编程和模板元编程场景。

## 主要内容

### 命名空间

- `yggr::encryption_tool`：加密工具相关代码的命名空间。

### 主要模板与宏

#### `template<typename Tool> struct tool_buf_size`

- 默认继承自 `boost::mpl::integral_c<u32, 0>`，即默认缓冲区大小为0。
- 可通过特化为具体加密工具类型指定实际缓冲区大小。

#### 宏定义

- `YGGR_ENCRYPTION_TOOL_TOOL_BUF_SIZE(__type__, __size__)`
  - 用于为指定类型 `__type__` 显式特化 `tool_buf_size`，缓冲区大小为 `__size__`。
- `YGGR_ENCRYPTION_TOOL_DEFED_TOOL_BUF_SIZE(__type__, __def__)`
  - 用于为指定类型 `__type__` 显式特化 `tool_buf_size`，缓冲区大小取自类型内的静态常量 `__def__`。

## 适用场景

适用于需要在模板代码中统一获取不同加密工具缓冲区大小的 C++ 项目，尤其是泛型加密、摘要、签名等场景。

---

