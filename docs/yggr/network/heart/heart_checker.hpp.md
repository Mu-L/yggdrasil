# `yggr::network::heart::heart_checker`（文件：`heart_checker.hpp`）

## 概要
- **目的**：提供一个轻量的心跳检查器，用于遍历会话容器并对每个活跃会话触发心跳状态检查。
- **位置**：`yggr/network/heart/heart_checker.hpp`（与该文档同目录）
- **适用场景**：网络服务中周期性地检查/维护会话状态（例如清理超时会话或发送 keep-alive），可与定时器一起使用。

## 代码结构与行为
- 定义：
  ```cpp
  struct heart_checker
  {
      template<typename Session_Container>
      void operator()(Session_Container& cont) const
      {
          typedef Session_Container container_type;
          typedef typename container_type::iterator iter_type;

          for(iter_type i = boost::begin(cont), isize = boost::end(cont); i != isize; ++i)
          {
              if(i->second)
              {
                  i->second->check_state();
              }
          }
      }
  };
  ```

- 行为说明：
  - `operator()` 是一个函数对象模板，接受任意 `Session_Container` 类型的容器（只要支持 `boost::begin` / `boost::end` 与其迭代器，并且容器元素形如 `pair<Key, ValuePtr>`）。
  - 它通过迭代容器，针对 `i->second`（通常为指向会话对象的智能指针或裸指针）非空时调用 `check_state()`。
  - 对象本身不维护状态（无成员变量），是纯无状态的工具类型。

## 对容器与元素的要求
- `Session_Container`：应是可迭代的关联容器（例如 `std::map` / `std::unordered_map`），或任何可以满足 `boost::begin(cont)` / `boost::end(cont)` 的类型。
- 容器元素约定为 `pair` 或等价结构，且 `i->second` 表示会话指针/智能指针：
  - `i->second` 必须可用于 `if(i->second)` 判空测试；
  - 当非空时，表达式 `i->second->check_state()` 必须是有效的（即所指类型提供 `check_state()` 方法）。

## 使用示例
```cpp
#include <map>
#include <memory>
#include <yggr/network/heart/heart_checker.hpp>

struct Session
{
    void check_state() { /* 检查连接、超时、发送心跳等 */ }
};

int main()
{
    std::map<int, std::shared_ptr<Session>> sessions;
    sessions[1] = std::make_shared<Session>();
    sessions[2] = nullptr; // 模拟空会话槽

    yggr::network::heart::heart_checker checker;
    checker(sessions); // 遍历并对 sessions[1] 调用 check_state()
}
```

## 注意事项与建议
- 空指针处理：实现中通过 `if(i->second)` 防止对空指针解引用；如果容器元素类型不同（例如 `std::optional` 或自定义包装），需要确保 `if(i->second)` 判定是合理的。
- 线程安全：
  - `heart_checker` 自身无状态，但遍历容器时若其他线程可能修改容器（插入/删除/替换元素），可能造成未定义行为。建议在并发环境中：
    - 在调用前对容器上锁（mutex），或
    - 使用线程安全的容器，或
    - 在主线程/专门的心跳线程中执行遍历。
- 迭代策略：当前实现对所有元素都进行顺序检查；如需并行化检查可在外部分割容器范围或在循环内部将 `i->second` 的非空对象移动到工作队列再异步处理。
