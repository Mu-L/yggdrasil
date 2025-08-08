---
# convertible_traits.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了类型转换相关的 traits 工具，主要用于判断类型是否可以安全地转换为字符类型，以及为字符类型选择合适的格式化类型。它在泛型编程和字符串处理场景下，确保类型安全和高效转换。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心内容**：类型转换相关 traits 结构体和辅助宏

---

## 主要功能

### 1. patch_is_integral_c8

- 解决在部分 Boost 版本下 `char8_t`（或自定义 `c8`）类型未被识别为 integral 类型的问题。
- 对 `yggr::c8` 和 `const yggr::c8` 进行特化，映射为 `char` 或 `const char`。

### 2. is_can_be_conv_into_char

- 判断类型 T 是否可以安全地转换为字符类型。
- 满足以下任一条件即为 true：
  - T 是算术类型（如整型、浮点型、char 等）。
  - T 是枚举类型。
- 用于泛型字符串处理时的类型约束。

### 3. is_convertible_char

- 判断类型 T 是否为 integral 类型（整型，包括 char、wchar_t、char8_t、char16_t、char32_t 等）。
- 用于进一步约束只能用于字符的泛型模板。

### 4. format_char_t

- 用于确定类型 T 的格式化类型（通常为 s32 或更小的整型）。
- 通过 `YGGR_PP_INTEGER_T` 宏，保证格式化类型不会超过 s32 的大小。

### 5. 辅助宏

- `YGGR_PP_FORMAT_CHAR_TYPE(__type__)`  
  获取类型 `__type__` 的格式化类型。
- `YGGR_PP_FORMAT_CHAR_TYPE_TPL(__type__)`  
  用于模板上下文下获取格式化类型。

---

## 设计说明

- **兼容性强**：自动适配不同 Boost 版本和 C++ 标准下的 char8_t 支持。
- **类型安全**：通过 traits 保证只有合适的类型才能参与字符相关操作。
- **泛型友好**：便于在模板编程中进行类型分派和静态断言。
- **高效实现**：所有判断均为编译期常量，不影响运行时性能。

---

## 用法示例

```cpp
#include <yggr/charset/convertible_traits.hpp>
#include <type_traits>

static_assert(yggr::charset::is_can_be_conv_into_char<int>::value, "int 可转换为 char");
static_assert(!yggr::charset::is_can_be_conv_into_char<void*>::value, "void* 不可转换为 char");

typedef YGGR_PP_FORMAT_CHAR_TYPE(char16_t) my_fmt_type; // my_fmt_type 通常为 s32
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义类型，请特化对应的 traits 结构体。详细用法和扩展方式请查阅源码实现与注释。

