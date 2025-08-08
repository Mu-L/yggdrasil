---
# if_constexpr_cfg.hpp 文档

## 文件简介

if_constexpr_cfg.hpp 用于自动检测当前编译环境是否支持 C++17 的 `if constexpr` 语法，并定义一组兼容性宏。通过这些宏，Yggdrasil 工程可以在不同 C++ 标准下安全地使用条件编译，保证代码既能利用新标准特性，也能兼容旧标准。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- 必须先包含 `<yggr/base/yggrdef.h>`
- `<boost/config.hpp>`
- `<yggr/base/yggr_cpp_ver_config.hpp>`

---

## 主要内容

### 1. 头文件包含保护

- 若未先包含 `yggrdef.h`，则编译报错，确保类型和基础配置一致。

### 2. if constexpr 兼容性宏定义

- 检测当前 C++ 标准版本和 Boost 能力，若支持 C++17 的 `if constexpr`，则定义：
  - `YGGR_IF_CONSTEXPR` 为 `if constexpr`
  - `YGGR_CPP17_IF_CONSTEXPR` 为 `if constexpr`
- 否则，降级为普通 `if`，保证旧标准下代码可编译。

### 3. 针对 C++20/C++23 的 if constexpr 宏

- `YGGR_CPP20_IF_CONSTEXPR`  
  - C++20 及以上为 `if constexpr`，否则为 `if`
- `YGGR_CPP23_IF_CONSTEXPR`  
  - C++23 及以上为 `if constexpr`，否则为 `if`

---

## 用法示例

````cpp
#include <yggr/base/if_constexpr_cfg.hpp>

template<typename T>
void foo(const T& val) {
    YGGR_IF_CONSTEXPR (std::is_integral<T>::value) {
        // 编译期分支：T为整型
    } else {
        // 其他类型
    }
}
````

---

## 注意事项

- 推荐所有需要 `if constexpr` 的代码均通过这些宏进行条件编译，保证跨平台和跨标准兼容性。
- 宏会根据实际编译环境自动适配，无需手动干预。

---

 

