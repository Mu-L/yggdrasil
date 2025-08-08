---
# container_cfg.hpp 文档

## 文件简介

container_cfg.hpp 用于配置和适配 Yggdrasil 工程中容器相关的兼容性宏和内联优化宏。该文件根据编译器、Boost 版本等环境，自动检测并定义容器特性支持情况，以及为容器相关代码提供可控的内联/非内联宏，提升跨平台兼容性和性能调优能力。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- 必须先包含 `<yggr/base/yggrdef.h>`
- 依赖 Boost 相关宏

---

## 主要内容

### 1. 头文件包含保护

- 若未先包含 `yggrdef.h`，则编译报错，确保类型和基础配置一致。

### 2. 容器特性支持检测

- 针对 MSVC 1800（VS2013）以下版本，自动禁用 C++11 标准库的 `unordered_set`、`unordered_map`，并定义：
  - `YGGR_NO_CXX11_HDR_UNORDERED_SET`
  - `YGGR_NO_CXX11_HDR_UNORDERED_MAP`
  - `YGGR_NO_CXX11_STD_UNORDERED`

### 3. 容器内联/非内联宏定义

- 当 Boost 版本大于等于 1.62.0 时，支持如下宏（可通过注释/定义控制）：
  - `YGGR_CONTAINER_FORCEINLINE`  
    控制容器相关函数的强制内联。根据不同编译器和宏定义自动适配为 `inline`、`BOOST_FORCEINLINE` 或空。
  - `YGGR_CONTAINER_CONSTRUCT_FORCEINLINE`  
    构造相关函数的强制内联，等价于 `YGGR_CONTAINER_FORCEINLINE`。
  - `YGGR_CONTAINER_NOINLINE`  
    控制容器相关函数的非内联。可通过 `YGGR_CONTAINER_DISABLE_NOINLINE` 控制，默认等价于 `BOOST_FORCEINLINE` 或空。

- 若 Boost 版本低于 1.62.0，则上述宏均为空。

---

## 用法示例

````cpp
#include <yggr/base/container_cfg.hpp>

class MyContainer {
public:
    YGGR_CONTAINER_FORCEINLINE void fast_func() { /* ... */ }
    YGGR_CONTAINER_NOINLINE void slow_func() { /* ... */ }
};
````

---

## 注意事项

- 推荐在所有自定义容器或与容器相关的性能敏感代码中使用这些宏，便于后续统一调整和跨平台兼容。
- 宏的具体行为会根据编译器、Boost 版本和相关宏定义自动适配，无需手动干预。
- 若需强制禁用/启用内联，可通过定义 `YGGR_CONTAINER_DISABLE_FORCEINLINE` 或 `YGGR_CONTAINER_FORCEINLINE_IS_BOOST_FORCELINE` 等宏实现。

---

 

