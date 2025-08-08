# safe_multi_index_container.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了线程安全的多索引容器（safe multi-index container）的声明和适配。它通过包含 safe_multi_index_container.hpp 实现具体功能，并可根据宏定义启用或禁用优化配置。

## 3. 重要警告
文件内包含显著警告，强调安全容器的使用注意事项：
- **线程安全限制**：所有 safe container 仅保证容器操作的线程安全，但不能保证容器对象本身的创建和销毁在多线程下安全。如果需要在不同线程中创建和销毁 safe container，请使用 swap 机制处理。
- **迭代器限制**：严禁通过回调函数将 safe_container 内部的“迭代器引用或指针”传递到容器外部并保存或使用，否则会导致未定义行为和线程安全隐患。

## 4. 头文件包含
- optimization_config.hpp：安全容器优化配置。
- safe_multi_index_container.hpp：实际的线程安全多索引容器实现。

## 5. 宏定义
- `YGGR_NOT_USE_SAFE_CONTAINER_OPTIMIZATION`：可通过该宏控制是否启用安全容器的优化特性。

## 6. 典型用途

```cpp
#include <yggr/safe_container/safe_multi_index_container.hpp>

// 定义并使用线程安全的多索引容器
// 具体接口和用法见 multi_index/safe_multi_index_container.hpp
```

## 7. 总结

本文件为 Yggdrasil 框架的线程安全多索引容器提供了统一的入口和配置点。它强调了容器对象的生命周期管理和迭代器使用的安全边界，适用于需要多索引和线程安全的数据结构场景。具体功能和接口需参考 safe_multi_index_container.hpp 实现文件。

---

