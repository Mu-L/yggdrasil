# 文件：pointer_int.hpp 文档

路径：`yggr/mplex/pointer_int.hpp`

## 概要
`pointer_int.hpp` 提供了在编译期与平台相关的“指针宽度”到整数类型的映射工具，方便在元编程或运行时需要根据指针尺寸选择合适整型表示时统一使用。

主要导出：
- `pointer_size`：表示 `sizeof(void*)` 的编译期常量类型（`boost::mpl::size_t`）。
- `pointer_int`：根据平台当前指针位宽选择一个带符号整数类型（如 `s8/s16/s32/s64`），或在未知/不可支持的位宽情形下映射为 `void`（表示不可用/失败）。
- `pointer_uint`：对应 `pointer_int::type` 的无符号版本（通过 `boost::make_unsigned` 得到）。

该头通过引用库中定义的 `sysbit_8/16/32/64/...` 与运行时/编译期的 `sysbit_now` 键值，使用 `boost::mpl::map` + `boost::mpl::at` 把当前系统位宽映射到具体 integer 类型。


## 依赖
- `yggr/base/yggrdef.h`：定义了项目级整型别名（如 `s8/s16/s32/s64`、`u32` 等）。
- `yggr/mplex/sysbit.hpp`：定义 `sysbit_8/16/32/64/128/256` 等类型标签以及表示当前系统/编译目标的 `sysbit_now`（该文件决定映射的关键）。
- Boost.TypeTraits / MPL：`boost::type_traits/make_unsigned.hpp`、`boost/mpl/size_t.hpp`、`boost/mpl/map.hpp`、`boost/mpl/at.hpp`。


## 命名空间
位于 `yggr::mplex` 命名空间。


## API 说明

- `struct pointer_size`
  - 继承自 `boost::mpl::size_t<sizeof(void*)>`。
  - 可以通过 `pointer_size::value` 在编译期获得指针大小（以字节为单位）。

- `struct pointer_int`
  - 继承自 `boost::mpl::at< mapping_map, sysbit_now >`，其中 `mapping_map` 将不同的 `sysbit_*` 标签映射到具体 `s8/s16/s32/s64` 等类型。
  - 要获得实际类型，使用 `pointer_int::type`（比如 `using ptr_int_t = pointer_int::type;`）。当当前 `sysbit_now` 对应的映射值为 `void` 时表示该位宽未被映射/不支持。

- `struct pointer_uint`
  - 继承自 `boost::make_unsigned<pointer_int::type>`，即得到 `pointer_int::type` 的无符号对应类型。
  - 注意：若 `pointer_int::type` 为 `void`，对 `boost::make_unsigned<void>` 可能不适用或导致编译错误；使用前应确保 `pointer_int::type` 是有效整型。


## 实现细节

文件关键实现逻辑：
- 通过 `pointer_size` 得到 `sizeof(void*)`（字节）信息作为一个编译期常量。
- 使用一个 `boost::mpl::map`，把系统位宽标签（例如 `sysbit_32`）映射为相应的带符号整型（`s32` 等）：
  - map 列表示例：
    - `sysbit_8`  -> `s8`
    - `sysbit_16` -> `s16`
    - `sysbit_32` -> `s32`
    - `sysbit_64` -> `s64`
    - `sysbit_128`/`sysbit_256` -> `void`（占位，表示当前实现没有为这些位宽提供对应整型）
- 通过 `boost::mpl::at< map, sysbit_now >` 按当前 `sysbit_now` 选择对应类型（该表达式是一个 MPL 元函数，最终结果可通过 `::type` 访问）。
- `pointer_uint` 使用 `boost::make_unsigned<pointer_int::type>` 将带符号类型转换为其无符号等价。


## 使用示例

```cpp
#include <yggr/mplex/pointer_int.hpp>
#include <type_traits>

// 获取指针大小（字节）
static_assert(yggr::mplex::pointer_size::value == sizeof(void*));

// 获取指针整数类型
using signed_ptr_t = yggr::mplex::pointer_int::type; // 例如 s32 或 s64
using unsigned_ptr_t = yggr::mplex::pointer_uint::type;

// 在使用前最好检查是否为 void（表示未映射）
static_assert(!std::is_same<signed_ptr_t, void>::value, "pointer_int::type must be valid integer type");

// 将其用于数组索引或其他需要与指针宽度一致的场景
```

注意：上例中的 `static_assert` 假设当前平台已映射到具体整型；在交叉或特殊平台上 `pointer_int::type` 可能是 `void`，此时需要提供替代实现或扩展映射。


## 安全性与注意事项
- `pointer_int::type` 为 `void` 的情形：源码中对 `sysbit_128/256` 映射为 `void`。若在某个平台 `sysbit_now` 打算为这些更大位宽，调用 `pointer_uint` 或试图使用该类型会导致编译错误。建议在使用前检查 `pointer_int::type` 的有效性，或扩展映射以提供合适类型。
- `boost::make_unsigned` 对某些特殊类型（如 `void`、未定义类型）不适用，可能导致编译失败。调用者应保证 `pointer_int::type` 为具体整型。
- `pointer_size` 返回的是字节大小（sizeof(void*)），若需要按位数使用请乘以 `CHAR_BIT`（通常为 8），或使用 `yggr::mplex::sysbit` 系列的标签/工具。


## 测试建议
- 在常见平台（32 位与 64 位）编译并断言 `pointer_size::value` 与 `sizeof(void*)` 一致。
- 验证 `pointer_int::type` 在目标平台下对应合适的带符号整数（例如在 64 位平台为 `s64`）。
- 验证 `pointer_uint::type` 为 `std::make_unsigned<pointer_int::type>::type` 的等价类型。
- 在特殊或交叉平台上（如 128 位指针平台）测试并决定如何扩展映射以避免 `void` 结果。

