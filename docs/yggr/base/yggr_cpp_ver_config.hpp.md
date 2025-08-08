---
# yggr_cpp_ver_config.hpp 文档

## 文件简介

yggr_cpp_ver_config.hpp 用于自动检测和定义当前编译环境的 C++ 标准版本，并为 Yggdrasil 工程提供统一的 C++ 版本号宏。该文件支持 C++98、03、11、14、17、20、23 等主流标准，便于后续代码根据标准版本进行条件编译和特性适配。

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

### 1. C++ 版本号宏定义

- `YGGR_CPP_VER_98`：98
- `YGGR_CPP_VER_03`：300
- `YGGR_CPP_VER_11`：1100
- `YGGR_CPP_VER_14`：1400
- `YGGR_CPP_VER_17`：1700
- `YGGR_CPP_VER_20`：2000
- `YGGR_CPP_VER_23`：2300

### 2. C++ 标准 __cplusplus 宏值定义

- `YGGR__CPLUSPLUS_ISO_98`：199711
- `YGGR__CPLUSPLUS_ISO_11`：201103
- `YGGR__CPLUSPLUS_ISO_14`：201402
- `YGGR__CPLUSPLUS_ISO_17`：201703
- `YGGR__CPLUSPLUS_ISO_20`：202002

### 3. 当前 C++ 标准检测

- 对于 MSVC，优先使用 `_MSVC_LANG`，否则假定为 200300（VS2010 支持 03）。
- 其他编译器使用 `__cplusplus`。

### 4. YGGR_CPP_VER 和 YGGR_CPP_VERSION 宏

- 根据 `YGGR__CPLUSPLUS` 的值自动推断当前 C++ 版本，并定义 `YGGR_CPP_VER` 和 `YGGR_CPP_VERSION`。
- 支持自动识别 C++98、03、11、14、17、20、23，若更高版本需手动扩展。

### 5. YGGR_USING_CXX?? 宏

- 自动定义当前使用的 C++ 标准宏，如 `YGGR_USING_CXX11`、`YGGR_USING_CXX17` 等。
- 若已手动定义 `YGGR_USING_CXX??`，则同步修正 `YGGR_CPP_VERSION`。

---

## 用法说明

- 通过检测 `YGGR_CPP_VERSION` 或 `YGGR_USING_CXX??` 宏，可在代码中安全判断当前 C++ 标准，进行条件编译或特性适配。

````cpp
#if defined(YGGR_USING_CXX17)
// C++17 特性代码
#endif

#if (YGGR_CPP_VERSION >= YGGR_CPP_VER_14)
// C++14 及以上特性代码
#endif
````

---

## 注意事项

- 必须先包含 `<yggr/base/yggrdef.h>`，否则会编译报错。
- 若需支持更高版本的 C++ 标准，请手动扩展相关宏定义。
- 推荐所有与 C++ 标准相关的条件编译均通过本文件中的宏进行判断。

---

 