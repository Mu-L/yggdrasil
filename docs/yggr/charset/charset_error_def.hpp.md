---
# charset_error_def.hpp 文档

该头文件为 yggdrasil 框架的字符集模块定义了字符集相关的错误码与错误信息，便于在字符集转换等操作中进行统一的异常处理和错误报告。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心结构体**：`charset_error_def`

---

## 主要功能

### 1. 错误码定义

通过宏定义机制，声明了字符集相关的错误码，便于在程序中进行错误判断和处理。

- **E_charset_conver_failed**  
  表示字符集转换失败。

错误码的数值区间由 `exception::exception_sort::E_code_start_22` 到 `exception::exception_sort::E_code_end_22` 控制，确保与其他模块的错误码不冲突。

### 2. 错误信息定义

为每个错误码定义了对应的错误消息字符串，便于日志记录和用户提示。

- **E_charset_conver_failed**  
  错误消息为 `"charset_convter_failed"`。

---

## 设计说明

- **统一管理**：通过 `charset_error_def` 结构体集中管理字符集相关错误码和消息。
- **可扩展性**：可在该结构体内继续添加更多字符集相关的错误码和消息。
- **与 yggdrasil 框架集成**：依赖于 error.hpp 和 exception_sort.hpp，与框架的异常处理体系无缝对接。

---

## 用法示例

```cpp
#include <yggr/charset/charset_error_def.hpp>

int err_code = yggr::charset::charset_error_def::E_charset_conver_failed;
std::string err_msg = yggr::charset::charset_error_def::get_error_msg(err_code);
// err_msg == "charset_convter_failed"
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展错误码或获取详细用法，请查阅相关宏定义和 yggdrasil 框架的异常处理文档。

