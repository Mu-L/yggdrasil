# `yggr::network::sender_checker::sender_non_checker`（文件：`sender_non_checker.hpp`）

## 概述
- 目的：提供一个最简单的“发送检查器（sender checker）”实现，始终允许发送（返回 true）。该类型可用于在不需要发送权限检查的场景中作为占位策略，以简化调用方逻辑。
- 位置：`yggr/network/sender_checker/sender_non_checker.hpp`（该文档与源文件同目录）。
- 适用场景：当你希望跳过任何适配器/权限检查，或者在测试/调试时快速替换为“放行”策略时使用。

## 行为说明
- `sender_non_checker` 是一个无状态的工具型结构，提供单一的 callable 接口：`operator()(...)`，对任意参数均返回 `true`。
- 实现细节：
  - 在支持 C++11 可变参数模板的构建（`YGGR_NO_CXX11_VARIADIC_TEMPLATES` 未定义）中，`operator()` 使用 `template<typename ...Args>` 接收任意参数并返回 `true`。
  - 在不支持可变参数模板的环境下，代码采用预处理器生成一系列定长模板重载（使用 `YGGR_PP_FOO_*` 与 `BOOST_PP_LOCAL_ITERATE`），以模拟变参能力；这些重载同样返回 `true`。

## API / 用法
- 直接使用：
```cpp
#include <yggr/network/sender_checker/sender_non_checker.hpp>

yggr::network::sender_checker::sender_non_checker chk;

// 任何参数，结果均为 true
bool ok = chk(pentity, key, netinfo, data, handler);
```
- 因为该类型不关心参数类型或值，它可以作为模板参数或策略注入到需要 checker 的泛型组件中，以达到“跳过检查”的效果。

## 优点与用途
- 简洁：无需依赖 `adapter_mgr`、`id_parser` 等复杂类型即可通过接口契约。
- 可用于测试：在单元测试或集成测试中快速替换真实的检查器，避免在测试环境中构造复杂的实体/适配器管理对象。
- 运行时零开销：`operator()` 直接返回常量 `true`，没有额外逻辑或分配。

## 注意事项
- 仅作“允许发送”的占位实现，不应在需要严格权限控制的生产场景下使用。
- 若上层逻辑依赖 checker 对某些参数的副作用（比如解析 id），使用该实现会跳过这些副作用；在替换为 `sender_non_checker` 前请确认没有隐藏依赖。

