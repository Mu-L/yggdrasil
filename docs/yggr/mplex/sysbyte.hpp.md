# `yggr::mplex::sysbyte`（文件：`yggr/mplex/sysbyte.hpp`）

## 概要
- **目的**：提供一个编译期的、以字节（byte）为单位的轻量模板封装，以及基于 `sizeof(T)` 的字节数别名，便于在模板元编程中引用类型的字节宽度。
- **位置**：`yggr/mplex/sysbyte.hpp`（与该文档同目录）
- **适用场景**：需要在编译期获取某个类型或给定字节数的字节宽度，或在模板元编程中以类型别名引用该信息。

## 主要定义与说明
- `template<std::size_t ByteSize> struct sysbyte`
  - 用途：将字节数 `ByteSize` 封装为一个类型，提供编译期常量 `value` 等于 `ByteSize`。
  - 成员：
    - `typedef sysbyte type;` —— 类型别名，便于链式继承和统一访问（例如 `sizeof_byte<T>::type`）。
    - `YGGR_STATIC_CONSTANT(std::size_t, value = ByteSize);` —— 编译期常量，等于模板参数 `ByteSize`。`
  - 备注：`YGGR_STATIC_CONSTANT` 在项目中定义（`yggr/base/static_constant.hpp`），用于兼容不同编译器对静态常量的支持。

- `template<typename T> struct sizeof_byte : public sysbyte<sizeof(T)>`
  - 用途：对任意类型 `T`，提供 `sizeof(T)`（以字节为单位）对应的别名与常量。
  - 使用方式：`sizeof_byte<T>::value` 或 `sizeof_byte<T>::type::value`。

- 常用别名（typedefs）：
  - `typedef sysbyte<1> sysbyte_1;`
  - `typedef sysbyte<2> sysbyte_2;`
  - `typedef sysbyte<4> sysbyte_4;`
  - `typedef sysbyte<8> sysbyte_8;`
  - `typedef sysbyte<16> sysbyte_16;`
  - `typedef sysbyte<32> sysbyte_32;`

- 平台/特殊别名：
  - `typedef sizeof_byte<void*>::type sysbyte_now;` —— 当前平台指针大小对应的字节数（例如 8 表示 64 位指针）。
  - `typedef sizeof_byte<double>::type sysbyte_max;` —— `double` 类型对应的字节数（常用于作为某类宽度参考）。

## 使用示例
```cpp
#include <iostream>
#include <yggr/mplex/sysbyte.hpp>

int main() {
    // 直接使用字节数模板
    std::cout << "sysbyte<4>::value = " << yggr::mplex::sysbyte<4>::value << " bytes\n"; // 4

    // 使用 sizeof_byte 获取类型的字节宽
    std::cout << "sizeof_byte<int>::value = " << yggr::mplex::sizeof_byte<int>::value << " bytes\n";

    // 使用预定义别名
    std::cout << "sysbyte_8::value = " << yggr::mplex::sysbyte_8::value << " bytes\n";

    // 平台指针字节宽
    std::cout << "sysbyte_now::value = " << yggr::mplex::sysbyte_now::value << " bytes\n";
}
```

## 注意事项与实现细节
- `sysbyte` 的 `value` 直接等于模板参数 `ByteSize`，不会涉及位移运算，因此在常规用途中没有溢出风险。
- `YGGR_STATIC_CONSTANT` 是项目内用于统一声明静态常量的宏，可能在不同编译器或标准下展开为 `static const` 或 `static constexpr`。如需严格的 `constexpr` 行为，可在支持的编译器中替换或更新宏定义（参考 `yggr/base/static_constant.hpp`）。
- `sizeof_byte<T>` 继承自 `sysbyte<sizeof(T)>`，因此可以使用 `sizeof_byte<T>::value` 或 `sizeof_byte<T>::type::value`。
