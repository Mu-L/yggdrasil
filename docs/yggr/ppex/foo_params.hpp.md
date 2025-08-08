# foo_params.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了一套基于 Boost.Preprocessor 的宏工具，用于自动生成各种形式的函数参数列表、参数类型、参数转发、默认参数等代码。它支持 C++11 右值引用和 Boost 移动语义，适用于模板函数、泛型工厂、回调包装等场景。

## 3. 主要宏定义

### 3.1 参数类型与名称生成
- `YGGR_PP_FOO_TYPES_DEF(__count__)`：生成 `typename T0, typename T1, ...` 类型列表。
- `YGGR_PP_FOO_TYPES_GROUP(__count__)`：生成 `T0, T1, ...` 类型列表。
- `YGGR_PP_FOO_ARG(__n__)`：生成参数名，如 `arg0`。
- `YGGR_PP_FOO_PARAMS_DEF(__count__, __macro__)`：根据指定宏批量生成参数声明。

### 3.2 参数声明宏（支持多种引用/转发方式）
- `YGGR_PP_FOO_ANYREF_PARAMS`：生成通用引用参数（支持右值引用或 Boost.FWD_REF）。
- `YGGR_PP_FOO_RVREF_PARAMS`：生成右值引用参数（C++11）或 Boost.RV_REF。
- `YGGR_PP_FOO_CREF_PARAMS`：生成 const 引用参数。
- `YGGR_PP_FOO_REF_PARAMS`：生成左值引用参数。
- `YGGR_PP_FOO_VAR_PARAMS`：生成值传递参数。
- `YGGR_PP_FOO_CUSTOM_*`：支持自定义类型参数的生成。

### 3.3 参数操作宏
- `YGGR_PP_FOO_PARAMS_OP(__count__, __op__)`：批量生成参数操作（如逗号分隔的参数名）。
- `YGGR_PP_FOO_PARAMS_OP_STD_FORWARD`、`YGGR_PP_FOO_PARAMS_OP_BOOST_FORWARD`：批量生成 std::forward 或 boost::forward 代码。
- `YGGR_PP_FOO_PARAMS_OP_STD_MOVE`、`YGGR_PP_FOO_PARAMS_OP_BOOST_MOVE`：批量生成 std::move 或 boost::move 代码。
- `YGGR_PP_FOO_PARAMS_OP_BOOST_REF`、`YGGR_PP_FOO_PARAMS_OP_BOOST_CREF`：批量生成 boost::ref 或 boost::cref 代码。

### 3.4 默认参数与转发
- `YGGR_PP_FOO_PARAM_AND_DEFAULT_VALUE(__count__, __class_name__)`：生成带默认值的参数声明。
- `YGGR_PP_FOO_ARGS_FWD_REF(__class_name__)`：根据是否支持右值引用，生成参数转发类型。

### 3.5 其他辅助宏
- 支持参数名自定义、参数展开、参数分隔符等。

## 4. 典型用法

```cpp
// 生成一个带任意参数的模板函数
#define BOOST_PP_LOCAL_MACRO(__n__) \
template<YGGR_PP_FOO_TYPES_DEF(__n__)> \
void foo(YGGR_PP_FOO_PARAMS_DEF(__n__, YGGR_PP_FOO_ANYREF_PARAMS)) { /* ... */ }

#define BOOST_PP_LOCAL_LIMITS (1, 5)
#include BOOST_PP_LOCAL_ITERATE()
```

## 5. 设计说明

- **兼容性强**：自动适配 C++11 右值引用或 Boost 移动语义。
- **灵活扩展**：支持自定义参数类型、参数名、参数操作等。
- **高效开发**：极大减少模板和泛型代码的重复劳动，提升代码可维护性。
- **与 Boost.Preprocessor 深度集成**：利用其枚举、重复、条件等特性实现批量代码生成。

## 6. 注意事项

- 仅作为头文件宏工具使用，不包含实际实现代码。
- 需要配合 Boost.Preprocessor 使用。
- 具体参数名需通过 `YGGR_PP_FOO_ARG_NAME` 宏自定义。

---

## 7. 总结

本文件为 Yggdrasil 框架提供了强大的函数参数宏生成工具，适用于泛型工厂、回调包装、模板库等需要批量生成参数列表和参数操作的场景。通过这些宏，可以大幅提升 C++ 模板元编程的开发效率和代码可读性。

