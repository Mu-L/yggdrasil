**start_data_generator.hpp 文档**

简介：
- `start_data_generator.hpp` 声明了两个用于 start_data 的模板扩展点：`start_data_generator<Start_Data>` 和 `start_data_loader<Start_Data>`。这两个模板通过显式特化由具体的 start_data 类型实现各自的创建与从包加载逻辑。

用途：
- `start_data_generator<Start_Data>`：负责根据给定 ID 或其它参数创建对应的 `Start_Data` 实例（例如生成随机密钥并构造 `encryption_pak_back_id`）。
- `start_data_loader<Start_Data>`：负责从网络包或序列化包中加载并返回 `Start_Data` 实例。

约定与示例：
- 对每个具体的 `Start_Data`，应在相应的实现文件中提供模板特化，例如：

```cpp
template<>
struct start_data_generator<MyStartData>
{
    typedef MyStartData start_data_type;
    typedef typename start_data_type::id_type id_type;

    start_data_type operator()(const id_type& id) const
    {
        return start_data_type(id);
    }
};
```

```cpp
template<>
struct start_data_loader<MyStartData>
{
    typedef MyStartData start_data_type;

    template<typename Packet>
    start_data_type operator()(Packet& pak) const
    {
        start_data_type s;
        pak.load(s);
        return s;
    }
};
```

实现细节：
- 头文件仅提供模板声明与示例注释；具体逻辑由项目中对应的 start_data 类型通过特化实现。
- `start_data_generator` 常用于创建带有随机或派生字段（如密钥）的 start_data。
- `start_data_loader` 常用于网络接收端将原始包转换为 start_data 实例，便于后续会话创建流程使用。

注意事项：
- 特化实现应放在合适的实现/注册文件中，并确保与序列化/版本管理（如 `YGGR_FAST_CAL_TASK_IMPORT_TPL`）协同使用。
- 保持 `start_data_generator` 与 `start_data_loader` 的接口稳定，便于上层调用代码统一使用这些扩展点。

文件： [yggr/network/start_data/start_data_generator.hpp](start_data_generator.hpp)
