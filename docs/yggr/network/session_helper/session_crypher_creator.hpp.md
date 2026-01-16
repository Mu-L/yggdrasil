**session_crypher_creator.hpp 文档**

简介：
- `session_crypher_creator` 提供宏与模板声明，用于为不同的 `Start_Data` 类型注册并生成对应的会话加密/加密器（crypher）实例。通过宏特化模板，用户可以简洁地定义如何根据启动数据构造 `crypher_type`。

文件要点：
- 声明了模板 `session_crypher_creator<Start_Data>` 的前向声明；实际特化通过配对宏创建：
  - `YGGR_PP_REGISTER_SESSION_CRYPHER_CREATOR_BEGIN(__start_data_type__, __start_data_name__, __crypher_type__)`
  - `YGGR_PP_REGISTER_SESSION_CRYPHER_CREATOR_END()`

宏用法示例：

```cpp
YGGR_PP_REGISTER_SESSION_CRYPHER_CREATOR_BEGIN(MyStartData, start, MyCrypher)
    start.key, start.iv // 填写构造函数需要的参数表达式列表
YGGR_PP_REGISTER_SESSION_CRYPHER_CREATOR_END()
```

展开结果说明：
- 上述宏将生成 `session_crypher_creator<MyStartData>` 的完全特化，包含：
  - 类型别名：`start_data_type`、`crypher_type`、`crypher_ptr_type`、`result_type`（均为 `::yggr::shared_ptr<crypher_type>`）。
  - `operator()(const start_data_type& start)`：返回 `shared_ptr<crypher_type>`，内部使用 `construct_shared<crypher_type>(yggr_nothrow_new crypher_type(...))` 创建实例。

设计说明：
- 该宏机制把构造 crypher 的细节集中在宏注册处，便于在项目中按不同 `Start_Data` 类型注册不同的加密器构造逻辑。
- 在宏的注释区域（`mid write start_data_init_param_list`）应填写用于构造 `crypher_type` 的参数列表，通常通过访问 `__start_data_name__` 的成员来传递。

注意事项：
- 确保所填参数表达式与 `crypher_type` 的构造函数签名匹配；参数表达式会直接插入到 `yggr_nothrow_new crypher_type(...)` 调用中。
- 此头文件仅提供宏与模板声明；请在项目的实现/注册文件中使用宏进行实际注册。
- 源码注释处文件名拼写为 `session_checket_creator.hpp`，但实际宏与 include guard 使用 `session_crypher_creator`。

扩展建议：
- 为方便维护，建议在注册宏处同时添加注释或在文档中生成已注册映射表，便于追踪 `Start_Data` 到 `Crypher` 的关系。

文件： [yggr/network/session_helper/session_crypher_creator.hpp](session_crypher_creator.hpp)
