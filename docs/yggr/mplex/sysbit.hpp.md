# `yggr::mplex::sysbit`（文件：`yggr/mplex/sysbit.hpp`）

## 概要
- **目的**：提供一个编译期的、以字节为单位转换到位（bit）的轻量模板封装，以及基于 `sizeof(T)` 的位数计算别名。
- **位置**：`yggr/mplex/sysbit.hpp`（仓库路径：`yggr/mplex/sysbit.hpp`）
- **适用场景**：需要在编译期获取某个类型或给定字节数对应位数（bits），或在模板元编程中以类型别名引用该信息。

## 主要定义与说明
- `template<std::size_t ByteSize> struct sysbit`
  - 用途：将字节数 `ByteSize` 转换为位数（bits）。
  - 成员：
    - `typedef sysbit type;` —— 类型别名，用于统一风格（例如 `sizeof_bit<T>::type` 的继承链）。
    - `YGGR_STATIC_CONSTANT(std::size_t, value = (ByteSize << 3));` —— 编译期常量，等于 `ByteSize * 8`（左移 3 位实现）。
  - 备注：`YGGR_STATIC_CONSTANT` 在项目其他头文件（如 `yggr/base/static_constant.hpp`）中定义，通常用于兼容不同编译器的 `static const` 或 `constexpr` 写法。

- `template<typename T> struct sizeof_bit : public sysbit<sizeof(T)>`
  - 用途：对任意类型 `T`，提供 `sizeof(T)`（字节）对应的位数信息。
  - 使用方式：`sizeof_bit<T>::value` 或 `sizeof_bit<T>::type::value`。

- 常用别名（typedefs）：
  - `typedef sysbit<1> sysbit_8;`      // 8 bits
  - `typedef sysbit<2> sysbit_16;`     // 16 bits
  - `typedef sysbit<4> sysbit_32;`     // 32 bits
  - `typedef sysbit<8> sysbit_64;`     // 64 bits
  - `typedef sysbit<16> sysbit_128;`   // 128 bits
  - `typedef sysbit<32> sysbit_256;`   // 256 bits

- 平台/特殊别名：
  - `typedef sizeof_bit<void*>::type sysbit_now;` —— 当前平台指针大小对应的位宽（例如在 64 位平台通常为 64）。
  - `typedef sizeof_bit<double>::type sysbit_max;` —— `double` 类型对应的位宽（通常用于表示某个浮点或宽度上界的参考）。

## 使用示例
```cpp
#include <iostream>
#include <yggr/mplex/sysbit.hpp>

int main() {
    // 直接使用字节数模板
    std::cout << "sysbit<4>::value = " << yggr::mplex::sysbit<4>::value << " bits\n"; // 32

    // 使用 sizeof_bit 获取类型的位宽
    std::cout << "sizeof_bit<int>::value = " << yggr::mplex::sizeof_bit<int>::value << " bits\n";

    // 使用预定义别名
    std::cout << "sysbit_64::value = " << yggr::mplex::sysbit_64::value << " bits\n";

    // 平台指针位宽
    std::cout << "sysbit_now::value = " << yggr::mplex::sysbit_now::value << " bits\n";
}
```

## 注意事项与实现细节
- `value` 的实现是 `(ByteSize << 3)`，等价于 `ByteSize * 8`。若 `ByteSize` 很大导致左移运算超出 `std::size_t` 范围，应注意溢出风险，但在常见用途（字节数小且合理）下没有问题。
- `YGGR_STATIC_CONSTANT` 是项目中用于统一声明静态常量的宏，可能在不同编译器下展开为 `static const` 或 `static constexpr`，请参考 `yggr/base/static_constant.hpp`。
- `sizeof_bit<T>` 继承自 `sysbit<sizeof(T)>`，因此既可以使用 `sizeof_bit<T>::value`，也可以使用 `sizeof_bit<T>::type::value`（两者等价）。
