---
# constexpr_cfg.hpp 文档

## 文件简介

constexpr_cfg.hpp 负责根据 Boost 版本、C++ 标准版本和编译器能力，自动检测并定义一组与 `constexpr` 相关的宏。通过这些宏，可以在 Yggdrasil 工程中跨平台、跨标准地安全使用 `constexpr`，并兼容不同 C++ 版本的特性。

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

### 2. constexpr 支持检测与宏定义

- 根据 Boost 版本和 `BOOST_NO_CONSTEXPR`，自动检测是否支持 `constexpr`。
- 若不支持，则定义 `YGGR_NO_CONSTEXPR`，并将所有相关宏降级为 `inline`、`const` 或 `static`。
- 若支持，则根据 Boost 或标准定义，自动适配 `constexpr` 相关宏。

#### 主要宏

- `YGGR_CONSTEXPR`  
  标记为 `constexpr` 或降级为 `inline`。

- `YGGR_CONSTEXPR_OR_INLINE`  
  支持 `constexpr` 时为 `constexpr`，否则为 `inline`。

- `YGGR_STATIC_CONSTEXPR_OR_INLINE_STATIC`  
  支持 `constexpr` 时为 `static constexpr`，否则为 `inline static`。

- `YGGR_CONSTEXPR_OR_CONST`  
  支持 `constexpr` 时为 `constexpr`，否则为 `const`。

- `YGGR_CONSTEXPR_OR_STATIC`  
  支持 `constexpr` 时为 `constexpr`，否则为 `static`。

- `YGGR_CONSTEXPR_OR_STATIC_CONST`  
  支持 `constexpr` 时为 `constexpr`，否则为 `static const`。

### 3. 针对不同 C++ 标准的 constexpr 宏

- 针对 C++11、C++14、C++17、C++20、C++23，分别定义了对应的 `YGGR_CXX??_CONSTEXPR` 及其变体宏。
- 若当前标准支持，则为 `constexpr`，否则降级为 `inline`、`const`、`static` 等。
- 对于 C++20/C++23，若支持 `__cpp_lib_constexpr_dynamic_alloc` 且非 Clang，则可用 `constexpr`，否则降级。

---

## 用法示例

````cpp
#include <yggr/base/constexpr_cfg.hpp>

YGGR_CONSTEXPR int foo(int x) { return x + 1; }

struct Bar {
    YGGR_STATIC_CONSTEXPR_OR_INLINE_STATIC int value = 42;
};
````

---

## 注意事项

- 需先包含 `<yggr/base/yggrdef.h>`，否则编译报错。
- 推荐使用这些宏替代直接写 `constexpr`，以保证跨平台和跨标准兼容性。
- 宏会根据实际编译环境自动适配，避免因标准或 Boost 版本不支持而导致的编译错误。

---

 

