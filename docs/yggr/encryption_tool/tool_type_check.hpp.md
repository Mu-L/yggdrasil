---
tool_type_check.hpp 文档

---

# tool_type_check.hpp 文档

## 概述

tool_type_check.hpp 提供了加密工具类型特性萃取模板 `is_reductionable_tool`，用于在模板元编程中判断某类型是否为“可还原工具”（如支持加解密、签名/验签等）。该机制便于在泛型代码中进行类型约束和静态断言。

## 主要内容

### 命名空间

- `yggr::encryption_tool`：加密工具相关代码的命名空间。

### 主要模板

#### `template<typename T> struct is_reductionable_tool`

- 默认继承自 `boost::mpl::false_`，即所有类型默认都不是“可还原工具”。
- 具体加密工具类型可通过特化该模板，将其设为 `boost::mpl::true_`，以便在模板代码中进行类型判断和静态断言。

## 适用场景

适用于需要在模板代码中区分加密工具类型特性、进行类型约束和静态断言的 C++ 项目，尤其是泛型加密、解密、签名等场景。

---
