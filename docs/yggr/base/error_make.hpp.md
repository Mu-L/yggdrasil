---
# error_make.hpp 文档

## 文件简介

error_make.hpp 提供了一套用于快速定义错误码枚举和错误消息生成器的宏工具，简化错误码管理和错误信息构造流程。通过这些宏，可以方便地为类或模块批量定义错误码、错误消息，并自动生成统一的错误对象，提升代码一致性和可维护性。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- `<yggr/base/yggrdef.h>`
- `<yggr/base/error.hpp>`

---

## 主要内容

### 1. 错误码定义相关宏

- `ERROR_CODE_DEF(__code__)`  
  定义单个错误码枚举项。

- `ERROR_CODE_KEY_VAL_DEF(__key__, __val__)`  
  定义带指定值的错误码枚举项。

- `ERROR_CODE_DEF_BEGIN(__s_code__)`  
  错误码枚举定义起始，指定起始值。

- `ERROR_CODE_DEF_NON_CODE_BEGIN()`  
  错误码枚举定义起始（无起始值）。

- `ERROR_CODE_DEF_END(__e_code__)`  
  错误码枚举定义结束，指定结束值。

- `ERROR_CODE_DEF_NON_CODE_END()`  
  错误码枚举定义结束（无结束值）。

### 2. 错误消息生成相关宏

- `ERROR_CODE_MSG(__code__, __msg__)`  
  为指定错误码添加错误消息分支。

- `ERROR_CODE_MSG_BEGIN()`  
  错误消息生成函数定义起始，自动生成 `make_error` 静态方法。

- `ERROR_CODE_MSG_END()`  
  错误消息生成函数定义结束，处理未知错误码。

### 3. 错误生成器类宏

- `ERROR_MAKER_BEGIN(__class_name__)`  
  错误生成器类定义起始，指定类名。

- `ERROR_MAKER_END()`  
  错误生成器类定义结束。

- `ERROR_MAKE_NON(__class_name__)`  
  定义一个无错误码的默认错误生成器。

---

## 用法示例

````cpp
class MyClass {
    ERROR_MAKER_BEGIN("MyClass")
        ERROR_CODE_DEF_BEGIN(1000)
            ERROR_CODE_DEF(E_error1)
            ERROR_CODE_KEY_VAL_DEF(E_error2, 1002)
        ERROR_CODE_DEF_END(1999)
        ERROR_CODE_MSG_BEGIN()
            ERROR_CODE_MSG(E_error1, "错误1描述")
            ERROR_CODE_MSG(E_error2, "错误2描述")
        ERROR_CODE_MSG_END()
    ERROR_MAKER_END()
};
````

- 这样会自动生成错误码枚举和 `make_error` 静态方法，可用于统一创建带有详细消息的错误对象。

---

## 注意事项

- 错误码枚举项需在 `ERROR_CODE_DEF_BEGIN` 和 `ERROR_CODE_DEF_END` 之间定义。
- 错误消息分支需在 `ERROR_CODE_MSG_BEGIN` 和 `ERROR_CODE_MSG_END` 之间定义。
- 推荐每个模块或类单独定义一套错误码和错误生成器，便于定位和维护。

---

 

