---
# clear.hpp 文档

## 概述

`clear.hpp` 是 yggdrasil 项目中用于统一容器清空操作的适配头文件。该文件通过泛型 `clear` 函数，结合内部 `clear_helper` 机制，为各种容器类型（包括标准容器、自定义容器等）提供统一的清空接口，简化容器操作并提升代码可移植性和泛型编程能力。

## 版权声明


- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改、分发和商业化，但需保留版权声明和许可声明。

## 主要内容


- 包含 clear_helper.hpp，用于实现具体的清空策略。
- 在 `yggr::container` 命名空间下定义泛型 `clear` 函数模板，自动选择合适的清空方式。
- 将 `container::clear` 提升到 yggr 命名空间，便于全局统一调用。

## 主要接口

```cpp
template<typename C>
void clear(C& c);
```
- 自动根据容器类型选择合适的清空实现（如调用 `c.clear()` 或其他自定义清空逻辑）。

## 适用场景

- 需要对不同类型容器（标准容器、boost容器、自定义容器等）统一进行清空操作时。
- 泛型算法、模板编程中对 clear 操作的统一适配需求。

## 使用示例

```cpp
#include <yggr/container/clear.hpp>

std::vector<int> v = {1, 2, 3};
yggr::clear(v); // 清空 vector

MyCustomContainer c;
yggr::clear(c); // 清空自定义容器（需有 clear_helper 支持）
```

---

如需扩展支持自定义容器，请实现对应的 `clear_helper` 特化。

