---
# third_party_issues_config.hpp 文档

## 文件简介

third_party_issues_config.hpp 用于集中管理 Yggdrasil 工程中与第三方库（主要是 Boost）兼容性相关的问题修正和配置。该文件通过宏定义和条件编译，修复旧版本 Boost 在特定平台或 C++ 标准下的已知问题，并为后续扩展预留了接口。

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

### 1. Boost 旧版本兼容性修正

- 定义宏 `YGGR_BOOST_OLD_VERSION_COMPATIBILITY_FIXED`，用于标记已修复 Boost 1.53 及以下版本在 `interprocess`、`win32_api.hpp`、`get_wmi_class_attribute`、`wchar_variant` 等模块中的兼容性问题。
- 该宏可用于条件编译，屏蔽或修正相关代码。

### 2. C++ 标准与 Boost 版本兼容性提示

- 根据当前 C++ 标准版本（C++98/03、C++11、C++14、C++17、C++20、C++23）进行条件分支，为后续不同标准下的第三方库兼容性修正预留扩展点。
- 对于 C++17，如果 Boost 版本小于 1.64.0，给出注释性警告（未启用强制报错），提示 Boost 1.64 及以下版本不支持 C++17 及以上标准，尤其是 `boost/functional/hash.hpp` 和 `std::unary_function` 相关问题。

---

## 用法说明

- 本文件会在工程编译初期自动定义兼容性修正宏，供后续代码条件编译使用。
- 推荐所有涉及 Boost 旧版本兼容性修正的代码均通过 `YGGR_BOOST_OLD_VERSION_COMPATIBILITY_FIXED` 宏进行条件编译。

````cpp
#ifdef YGGR_BOOST_OLD_VERSION_COMPATIBILITY_FIXED
// 兼容性修正代码
#endif
````

---

## 注意事项

- 必须先包含 `<yggr/base/yggrdef.h>`，否则会编译报错。
- 该文件为第三方库兼容性修正的集中入口，便于后续维护和扩展。
- 若需针对不同 C++ 标准或 Boost 版本做更多兼容性处理，可在对应分支内扩展。

---

 

