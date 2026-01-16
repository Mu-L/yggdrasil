**session_checker_creator.hpp 文档**

简介：
- `session_checker_creator` 提供了一组宏与模板声明，用于为不同的 `Start_Data` 类型注册并生成对应的“检查器（checker）”对象。该机制通过在预处理阶段注册特化模板来简化根据启动数据创建检查器实例的代码。

文件要点：
- 声明了模板 `session_checker_creator<Start_Data>` 的前向声明，实际的特化通过两个宏配对来定义：
  - `YGGR_PP_REGISTER_SESSION_CHECKER_CREATOR_BEGIN(__start_data_type__, __start_data_name__, __checker_type__)`
  - `YGGR_PP_REGISTER_SESSION_CHECKER_CREATOR_END()`

宏用法：
- 使用示例（伪代码）：

```cpp
YGGR_PP_REGISTER_SESSION_CHECKER_CREATOR_BEGIN(MyStartData, start, MyChecker)
    start.member1, start.member2 // 在宏注释提示处补充构造参数列表
YGGR_PP_REGISTER_SESSION_CHECKER_CREATOR_END()
```

这将展开为一个 `session_checker_creator<MyStartData>` 的完全特化，其中 `operator()(const MyStartData& start)` 会返回 `shared_ptr<MyChecker>`，并在内部使用 `construct_shared<checker_type>(yggr_nothrow_new checker_type(...))` 创建 checker 实例。

设计说明：
- 目标是让用户通过宏在单个位置方便地注册针对某种启动数据的检查器构造逻辑，而无需手写模板特化。宏会生成类型别名：
  - `start_data_type`：对应传入的 `__start_data_type__`
  - `checker_type`：对应传入的 `__checker_type__`
  - `checker_ptr_type` 与 `result_type`：都为 `::yggr::shared_ptr<checker_type>`
- `operator()` 的实现位置通过宏拼接，用户需要在 `YGGR_PP_REGISTER_SESSION_CHECKER_CREATOR_BEGIN` 与 `...END` 之间填入 `checker_type` 构造函数所需的参数表达式列表，使用传入的 `__start_data_name__` 对象访问成员。

注意事项：
- 宏会直接生成 `yggr_nothrow_new checker_type(...)` 的调用并通过 `construct_shared` 封装为 `shared_ptr`，因此需要确保传入的参数表达式合法且与 `checker_type` 的构造函数匹配。
- 文件本身只包含模板的声明与宏定义；实际的特化需在项目其他源文件中通过宏进行注册。
- 请注意头文件顶部注释中的文件名拼写：`session_checket_creator.hpp`（源码注释处），但实际宏名与 include guard 使用 `session_checker_creator`。

扩展建议：
- 若需要在文档中集中列出已注册的 `Start_Data` → `Checker` 映射，建议在使用宏注册的位置添加注释或生成一份注册列表文档。

文件： [yggr/network/session_helper/session_checker_creator.hpp](session_checker_creator.hpp)
