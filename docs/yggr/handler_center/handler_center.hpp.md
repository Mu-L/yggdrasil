# handler_center.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 头文件包含
- 引入了 Yggdrasil 框架的基础定义、异常、类型萃取、参数包装、智能指针、线程安全容器等。
- 支持 Boost 相关库（如线程、类型萃取、MPL、智能指针等）。

## 3. 命名空间结构
- 主要内容位于 `yggr::handler_center` 命名空间下，部分细节实现位于 `yggr::handler_center::detail`。

## 4. 主要类型与功能

### 4.1 invoke_out
- 用于标记 handler 调用结果的结构体，包含一个布尔成员 `bret`，并重载了显式 bool 运算符。

### 4.2 basic_handler_container
- 抽象基类，定义了 handler 容器的统一接口，支持变参模板或预处理器展开的 `invoke` 方法。
- `pro_invoke` 为纯虚函数，由子类实现具体的 handler 调用逻辑。

### 4.3 handler_container
- 模板类，继承自 `basic_handler_container`，用于包装具体的 handler。
- 利用类型萃取（`foo_t_info`）自动推导 handler 的参数和返回值类型。
- 内部通过 `handler_container_detail_invoke_helper` 实现参数解包和 handler 调用。
- 支持返回值和无返回值的 handler。

### 4.4 handler_center
- 模板类，核心的“处理器中心”容器，支持线程安全。
- 主要成员：
  - `_map`：线程安全的 `safe_unordered_map`，用于存储 key-handler 映射。
- 主要功能：
  - 支持拷贝、移动、赋值、swap 等操作。
  - `register_handler`：注册 handler 到中心。
  - `unregister_handler`：注销 handler。
  - `call`：根据 key 和参数调用对应 handler，支持返回值和无返回值两种形式。
  - 支持对象批量注册/注销（如带有 `register_handler`/`unregister_handler` 方法的对象）。
  - 支持变参模板和预处理器展开两种参数传递方式，兼容 C++11 及更早版本。

### 4.5 swap 支持
- 提供了 `swap_support` 命名空间和 `swap` 函数模板，支持不同互斥类型下的 handler_center 交换。
- 将 swap 导入到 `std` 和 `boost` 命名空间，方便标准库和 Boost 生态下的使用。

### 4.6 宏定义
- 提供了 handler 名称相关的宏（如 `YGGR_PP_HANDLER_NAME`），用于将 handler 名称转换为字符串，便于调试和日志。

---

## 5. 主要用途

- **统一管理**：集中注册和管理各种 handler（如回调、事件处理函数等）。
- **线程安全**：内部使用线程安全容器，适合多线程环境。
- **泛型调用**：支持任意参数类型和数量的 handler，自动参数打包与解包。
- **灵活扩展**：支持对象批量注册、handler 对象的多种生命周期管理。
- **易于集成**：swap、拷贝、移动等接口完善，便于与其他容器或系统集成。

---

## 6. 典型用法

```cpp
using namespace yggr::handler_center;

// 定义 handler_center，key 为 int
handler_center<int> center;

// 注册 handler
center.register_handler(1, [](int a, int b) { return a + b; });

// 调用 handler
int result = 0;
center.call(result, yggr::utility::args_anchor<int>(1), 2, 3); // result = 5

// 注销 handler
center.unregister_handler(1);
```

---

## 7. 总结

本文件为 Yggdrasil 框架提供了高效、灵活、线程安全的 handler 注册与调用中心，适用于事件驱动、回调管理、消息分发等多种场景。其设计充分利用了 C++ 模板元编程和类型萃取技术，兼容 Boost 和标准库，易于扩展和集成。

