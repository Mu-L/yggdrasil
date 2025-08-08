# typename_replaceor.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了类型替换工具 `typename_replaceor`，用于在模板元编程中对类型参数包进行批量替换、条件替换或类型映射。该工具可用于类型萃取、类型变换、泛型编程等场景，极大提升模板代码的灵活性和可维护性。

## 3. 兼容性设计

- **C++11 及以上**：如果支持变参模板（variadic templates），则包含 `typename_replaceor_vtpl.hpp`，使用变参模板实现类型替换。
- **C++03 及以下**：如果不支持变参模板，则包含 `typename_replaceor_vmacro.hpp`，使用宏展开实现类型替换。

## 4. 主要功能

- **类型批量替换**：可对类型参数包中的指定类型进行批量替换（如将所有 T 替换为 U）。
- **条件类型替换**：支持根据条件对类型参数进行有选择的替换。
- **类型映射**：可实现类型列表的映射与变换，适合复杂的模板元编程场景。
- **自动适配**：根据编译器支持自动选择最佳实现方式，保证兼容性和效率。

## 5. 典型用法

```cpp
#include <yggr/mplex/typename_replaceor.hpp>

// 假设有如下类型列表
typedef boost::mpl::vector<int, float, double> types;

// 使用 typename_replaceor 将 float 替换为 long
typedef yggr::mplex::typename_replaceor<types, float, long>::type replaced_types;
```

> 实际接口和用法请参考 `detail/typename_replaceor_vtpl.hpp` 或 `detail/typename_replaceor_vmacro.hpp` 的具体实现。

## 6. 设计要点

- **高扩展性**：支持任意数量和类型的参数替换，适合复杂模板元编程。
- **零运行时开销**：所有替换和变换均在编译期完成。
- **易于集成**：可与 Boost.MPL、标准库类型列表等配合使用。

## 7. 总结

本文件为 Yggdrasil 框架提供了强大的类型参数替换工具，兼容 C++03/11，适合泛型编程、类型萃取、类型变换等高级模板元编程场景。通过自动适配不同编译器特性，保证了代码的可移植性和高效性。

---

