# `yggr::network::adapter_helper::io_converter`（文件：`io_converter.hpp`）

## 概要
- **目的**：在网络适配器（adapter）与任务中心（task center）之间转换数据格式。`io_converter` 是一个轻量级的模板工具，用于：
  - 将任务中的真实数据提取并封装为发送用的数据（conv_to_send）；
  - 从接收到的任务数据恢复为外部可用的接收数据类型（conv_from_recv）。
- **位置**：`yggr/network/adapter_helper/io_converter.hpp`
- **适用场景**：网络层的发送/接收适配器需要将任务（Task）中的真实数据与网络发送格式互相转换时使用。

## 类型别名说明
在模板 `io_converter<Send_Data, Task, Recv_Data>` 中定义了若干便捷别名：
- `send_data_type` —— 模板参数 `Send_Data`，表示发送端使用的数据封装类型。
- `task_type` —— 模板参数 `Task`，表示任务中心的任务类型。
- `recv_data_type` —— 模板参数 `Recv_Data`，表示从任务/网络接收后要构造的数据类型。

- `conv_to_send_result_type` —— `bool`，表示 `conv_to_send` 的返回结果类型（成功/失败）。
- `conv_to_send_arg_data_type` —— `const send_data_type&`，`conv_to_send` 的数据参数类型。

- `conv_from_recv_result_type` —— `recv_data_type`，`conv_from_recv` 的返回类型。
- `conv_from_recv_arg_data_type` —— `const task_type&`，`conv_from_recv` 的参数类型。

内部工具类型：
- `task_real_data_getter_type` —— `task_center::support::task_real_data_getter<task_type>`，用于从 `task_type` 中取得真实数据指针或引用。

## 成员函数说明
### conv_to_send
原型（模板成员）：
```cpp
template<typename Real_Data_Type, typename Src>
static conv_to_send_result_type conv_to_send(Src& src, conv_to_send_arg_data_type data);
```
行为：
- 通过 `data.load(rdata)` 提取 `Real_Data_Type rdata`；如果 `load` 返回 false，表示数据不可用或加载失败，函数返回 `false`。
- 若加载成功，调用 `src.template send<yggr::task_center::type_traits::mark_saver_condition>(data.net_info(), rdata);` 将真实数据通过 `src` 发送出去（`mark_saver_condition` 是发送时使用的标记/策略）。
- 成功时返回 `true`。

注意：调用方需要保证传入的 `Real_Data_Type` 与 `data.load()` 能匹配并正确反序列化/提取。

### conv_from_recv
原型（模板成员）：
```cpp
template<typename Real_Data_Type>
static conv_from_recv_result_type conv_from_recv(conv_from_recv_arg_data_type tk);
```
行为：
- 使用 `task_real_data_getter_type getter` 从任务 `tk` 中取得 `Real_Data_Type` 的指针。
- 代码中对 MSVC 与编译器版本做了条件处理：
  - 在某些 MSVC 早期环境（`_MSC_VER` 且 `YGGR_CPP_VERSION < YGGR_CPP_VER_20`）下，调用 `getter.operator()<Real_Data_Type>(tk)`；
  - 其他环境使用 `getter.template operator()<Real_Data_Type>(tk)`（正确使用 `template` 关键字来调用模板成员函数）。
- 对取得的指针做 `assert(pval)` 检查；若为空则返回默认构造的 `recv_data_type()`。
- 若非空，则返回 `recv_data_type(tk.owner_info(), *pval)`（构造带有所有者信息和真实数据的接收类型）。

## 依赖与外部约定
- 头文件依赖：
  - `yggr/task_center/support/task_real_data_getter.hpp`（用于从 `Task` 中获得真实数据）。
  - `yggr/task_center/type_traits/tags.hpp`（包含 `mark_saver_condition` 等网络/序列化相关标签）。
- `send` 方法契约：`src` 必须提供模板 `send<Tag>(net_info, real_data)` 的接口，且 `mark_saver_condition` 为有效的 Tag。
- `send_data_type` 需要提供 `load(Real_Data_Type&)` 成员函数和 `net_info()` 成员以获取网络信息。
- `recv_data_type` 需要提供构造函数 `recv_data_type(owner_info, Real_Data_Type)`，或至少能以该形式被构造。

## 示例（示意）
```cpp
// 伪代码示例：展示如何使用 io_converter
struct MySendData {
    bool load(MyRealData &out) const { /* 从内部序列化缓冲解包到 out */ }
    NetInfo net_info() const { /* 返回目的网络信息 */ }
};

struct MyTask { /* task 类型，task_real_data_getter 能从中取出真实数据 */ };

struct MyRecvData {
    MyRecvData(const OwnerInfo &owner, const MyRealData &d) : owner(owner), data(d) {}
    OwnerInfo owner; MyRealData data;
};

using conv = yggr::network::adapter_helper::io_converter<MySendData, MyTask, MyRecvData>;

// 发送路径（在适配器中）
MySendData send_wrapper = /* ... */;
AdapterSrc adapter_src = /* 提供 send<Tag> 接口 的 对象 */;
if(!conv::conv_to_send<MyRealData>(adapter_src, send_wrapper)) {
    // 发送失败：无法从 send_wrapper 中加载真实数据
}

// 接收路径（从 task 中恢复）
MyTask task = /* 从网络或任务中心得到 */;
MyRecvData recv = conv::conv_from_recv<MyRealData>(task);
// recv 包含 owner_info 与真实数据
```

## 实现细节与注意事项
- MSVC 模板成员调用差异：
  - 在少数老编译器/旧标准（例如老版 MSVC）下，直接调用模板成员函数可能不需要 `template` 关键字；而在符合 C++ 标准的编译器中调用模板成员函数需写作 `getter.template operator()<T>(tk)`。为了兼容，这里用条件编译切换。
- `assert(pval)`：生产代码中请注意断言可能被禁用（NDEBUG），因此实际运行应对 `pval` 为 `nullptr` 的情况做稳健处理；当前实现在空指针时返回默认构造的 `recv_data_type()`。
- 线程安全：`io_converter` 只是纯静态元/工具，不持有状态；实际并发行为取决于 `src`, `data` 与 `task` 的并发安全语义。
