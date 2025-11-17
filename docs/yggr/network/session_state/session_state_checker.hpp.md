# `yggr::network::session_state::session_state_checker`（文件：`session_state_checker.hpp`）

## 概述
- 目的：封装会话状态检查器的模板适配层，允许将具体的 checker 类型作为策略注入到会话管理逻辑中；提供一个默认的别名 `default_session_state_checker_type`，便于在不提供自定义 checker 时使用。
- 位置：`yggr/network/session_state/session_state_checker.hpp`（本文档与源文件同目录）。
- 适用场景：作为会话状态检查的策略容器，用户可以传入自定义的 Checker 类型（如定期清理、超时检查或统计收集），也可以使用默认的 `default_checker` 占位实现。

## 模板定义
```cpp
template<typename Def, typename Checker>
class session_state_checker
{
public:
    typedef Def def_type;
    typedef Checker checker_type;

    template<typename Session_Container>
    void operator()(Session_Container& cont) const
    {
        checker_type checker;
        checker(cont);
    }
};
```

- `Def`：状态定义类型（通常来自 `session_state_def`），用于标识检查所属的状态或提供状态相关常量。
- `Checker`：实际的检查器类型，需实现 `template<typename Session_Container> void operator()(Session_Container& cont) const`，用于对会话容器执行检查/维护操作。

## 默认别名
- 文件内提供了一个默认类型别名：
```cpp
typedef session_state_checker<
    session_state_def<tag_def::E_session_state_online>,
    default_checker
> default_session_state_checker_type;
```
- 含义：针对在线状态（`E_session_state_online`）使用 `default_checker` 作为检查策略，`default_checker` 为占位实现（其 operator() 默认断言失败，见 `default_checker.hpp`）。

## 行为说明
- `session_state_checker` 本身是一个薄包装：它在被调用时会创建一个 `checker_type` 实例并对传入的 `Session_Container` 调用该实例的 `operator()`。
- 该设计把 checker 的生命周期与调用点耦合：每次检查都会构造一个新的 checker 实例，若 checker 有昂贵的构造成本或需要持久状态，建议把 checker 封装在外层并传入合适的持久实例或使用不同策略。

## 使用示例（伪代码）
```cpp
// 自定义 checker（示例：移除过期会话）
struct my_checker {
    template<typename Session_Container>
    void operator()(Session_Container& cont) const {
        // 遍历 cont，移除过期或标记为关闭的会话
    }
};

using my_state_checker = yggr::network::session_state::session_state_checker<MyDef, my_checker>;

my_state_checker checker;
checker(session_container);
```

- 若希望复用同一个 checker 实例以避免重复构造：
```cpp
my_checker ck;
// 通过 lambda /适配器调用 ck(cont) 来代替每次构造
```

## 注意事项与建议
- 构造成本：`session_state_checker::operator()` 每次调用都会构造 `checker_type`，若 `checker_type` 构造昂贵或需要保持状态，请改为外部持有 checker 实例并直接调用其 `operator()`。
- `default_session_state_checker_type` 使用 `default_checker`（会在调试模式下断言），请在生产环境用合适的实现替换默认别名，以避免意外行为被忽略。
- Checker 的 `operator()` 应保证异常安全：若在检查过程中抛出异常，外层调用者应有适当的捕获/回退策略以避免影响整体会话管理循环。

