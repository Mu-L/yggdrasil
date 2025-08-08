# args_holder.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了一组参数持有器类（args_holder、args_holder_ref_wrap），用于安全、统一地封装和传递参数。支持值类型、引用类型、void 类型，并提供类型安全的转换和检查接口，适合泛型编程、回调机制、事件系统等场景。

## 3. 主要类型与功能

### 3.1 bad_args_holder_cast
- 继承自 `std::bad_cast`，用于参数持有器类型转换失败时抛出异常。

### 3.2 basic_args_holder
- 参数持有器基类，所有参数持有器的公共基类，含虚析构函数，支持多态。

### 3.3 args_holder_ref_wrap<T>
- 用于封装类型为 T 的引用参数，继承自 `basic_args_holder` 和 `boost::reference_wrapper<T>`。
- 提供 `get_pointer()` 方法获取被引用对象的指针。
- 特化版本 `args_holder_ref_wrap<void>` 用于 void 类型。

### 3.4 args_holder<T>
- 用于封装类型为 T 的值参数，继承自 `basic_args_holder`。
- 支持拷贝、移动构造和赋值。
- 提供 `get_pointer()` 方法获取内部值的指针。
- 特化版本 `args_holder<void>` 用于 void 类型。

### 3.5 类型转换与检查工具
- `args_holder_trans`：将具体参数持有器安全转换为基类引用。
- `args_holder_ref_wrap_dynamic_cast`：动态转换为指定类型的引用持有器，并获取指针。
- `args_holder_ref_wrap_dynamic_cast_throw_if_nil`：如转换失败则抛出异常。
- `args_holder_ref_wrap_check`：检查基类引用是否为指定类型的引用持有器。
- `args_holder_ref_wrap_static_cast`：静态转换为指定类型的引用持有器，并获取指针。
- `args_holder_dynamic_cast`：动态转换为指定类型的值持有器，并获取指针。
- `args_holder_dynamic_cast_throw_if_nil`：如转换失败则抛出异常。
- `args_holder_check`：检查基类引用是否为指定类型的值持有器。
- `args_holder_static_cast`：静态转换为指定类型的值持有器，并获取指针。

## 4. 设计要点

- **多态支持**：通过虚析构函数和 RTTI，支持类型安全的多态转换。
- **类型安全**：通过 dynamic_cast、断言和异常，确保类型转换安全。
- **支持引用和值**：分别用 ref_wrap 和普通持有器封装引用和值，适应不同参数传递需求。
- **void 特化**：对 void 类型做特殊处理，保证接口一致性。
- **Boost 支持**：依赖 Boost.Ref、Boost.Move 等库，兼容 C++98/03/11。

## 5. 典型用法

```cpp
#include <yggr/utility/args_holder.hpp>

int x = 42;
yggr::utility::args_holder_ref_wrap<int> ref_holder(x);
int* px = ref_holder.get_pointer(); // px 指向 x

yggr::utility::args_holder<std::string> val_holder(std::string("hello"));
std::string* ps = val_holder.get_pointer(); // ps 指向内部字符串

// 类型安全转换
yggr::utility::basic_args_holder& base = val_holder;
std::string* ps2 = yggr::utility::args_holder_dynamic_cast<std::string>(base);
```

## 6. 注意事项

- **不要跨线程保存持有器指针**，以免悬挂指针或未定义行为。
- **void 特化仅用于接口兼容，不持有实际数据。**
- **类型转换失败时会抛出 bad_args_holder_cast 异常或断言失败。**

## 7. 总结

本文件为 Yggdrasil 框架提供了高效、类型安全的参数封装与传递工具，适合泛型回调、事件分发、参数转发等多种场景。其多态与类型安全设计，便于在复杂 C++ 工程中安全管理和传递任意类型参数。

---

