# yggr/lua_wrap/wrap_base_t.hpp 文档

## 文件概述

`wrap_base_t.hpp` 提供了一个通用的C++基础数据类型包装器模板 `wrap_base_t<T>`，用于在 Lua/C++ 交互中安全、统一地处理LUA不支持的基础数据类型（如 `u64`、`s64`），并支持丰富的算术、逻辑、位运算和比较操作。该包装器可无缝与原生整型和其他包装器混合运算，便于在 Lua 脚本中安全地操作大整数。

## 命名空间结构

- `yggr`
  - `lua_wrap`
    - `detail`
    - `swap_support`

## 主要内容

### 1. 模板类 `wrap_base_t<Val>`
- **功能**：包装 LUA 不支持的 C++ 基础数据类型，提供标准算术、逻辑、位运算、比较等接口，支持与原生类型和其他包装器混合运算。
- **主要成员类型**：
  - `value_type`、`half_type`、`signed_value_type`、`unsigned_value_type`
- **主要成员函数**：
  - 构造/拷贝/析构，支持从字符串、半宽高位等多种方式构造
  - `unwrap()`/`value()`/`set_value()`/`get_value()`/`to_boolean()`/`copy()`
  - `plus`/`minus`/`multiplies`/`divides`/`modulus` 及对应的 set 版本
  - `logic_and`/`logic_or`/`logic_not`/`compare_eq`/`compare`
  - `bitwise_left_shift`/`bitwise_right_shift`/`bitwise_and`/`bitwise_or`/`bitwise_xor`/`bitwise_not` 及对应的 set 版本
  - `swap` 支持与原生类型和包装器互换
- **类型安全**：
  - 静态断言保证模板参数为 64 位整型

### 2. 类型萃取与特化
- `detail::is_wrap_base_t<T>`：类型萃取工具，用于判断类型是否为 `wrap_base_t` 实例

### 3. 全局操作符重载
- 支持与原生整型、其他包装器的 +, -, *, /, %, &, |, ^, <<, >> 及其复合赋值、比较等操作
- 支持流输出（`operator<<`）
- 支持 `swap`（std/boost/自定义）

## 依赖关系
- `yggr/type_traits/half_types.hpp`、`operator_result.hpp`
- `yggr/math/modulus.hpp`
- `yggr/lua_wrap/wrap_base_t_maker.hpp`
- Boost（类型萃取、enable_if、addressof 等）

## 用法示例

```cpp
#include <yggr/lua_wrap/wrap_base_t.hpp>
using yggr::lua_wrap::wrap_base_t;

wrap_base_t<u64> a(1234567890123456789ULL);
wrap_base_t<u64> b("9876543210987654321");
a += b;
if (a > b) { /* ... */ }
```

## 特别说明

1、非64位整数 LUA 均可支持。  
2、64位整数在不同的LUA版本下可能可以支持（通过自己编译LUA或者直接支持），但数据范围和C++的不同。  
3、在支持64位数据的LUA版本下并且C++的64位数据能满足LUA的64位数据的有效范围时，C++可直接传递64位数据给LUA。  
4、是否使用wrap_base_t 传递数据需要结合项目具体需求来进行选择。  

## 许可证

本文件遵循 yggdrasil 项目的开源许可证。
