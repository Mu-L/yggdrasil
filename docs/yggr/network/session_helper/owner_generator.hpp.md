**owner_generator.hpp 文档**

简介：
- `owner_generator` 是一个模板化的小工具，用于根据 `OwnerInfo` 类型生成该类型的实例。它封装了构造参数的转发逻辑，支持 C++11 可变参数转发以及在不支持可变模板时使用预处理器展开的兼容实现。

模板参数：
- `OwnerInfo`：表示“所有者信息”的类型，要求提供 `owner_id_type` 等内部类型别名（若需要）。

主要类型别名：
- `owner_info_type`：等同于 `OwnerInfo`。
- `id_type`：等同于 `owner_info_type::owner_id_type`。

主要接口：
- `operator()(Args... args) -> owner_info_type`：根据传入的参数构造并返回一个 `owner_info_type` 实例。
  - 在支持 C++11 可变模板的环境下，使用完美转发（`boost::forward`）将参数转给 `owner_info_type` 的构造函数。
  - 在不支持可变模板的环境下，使用预处理器宏生成多重重载以支持不同数量的参数（通过 `YGGR_PP_FOO_*` 系列宏）。

行为与兼容性说明：
- 可变参数实现（现代编译器）：
  - 使用 `template<typename ...Args>` 和 `BOOST_FWD_REF(Args)...`，将参数完美转发给 `OwnerInfo` 的构造器。
- 预处理器回退（旧编译器）：
  - 提供默认的无参构造 `operator()()`，以及通过 `BOOST_PP_LOCAL_ITERATE` 展开的一系列 `operator()` 重载来支持 N 个参数的情况。

示例：

```cpp
struct MyOwnerInfo {
    using owner_id_type = std::uint64_t;
    MyOwnerInfo() {}
    MyOwnerInfo(int a, std::string b) {}
};

owner_generator<MyOwnerInfo> gen;
auto o1 = gen(); // 默认构造
auto o2 = gen(42, std::string("abc")); // 转发到 MyOwnerInfo(int, string)
```

注意事项：
- `OwnerInfo` 需要提供与 `operator()` 中期望的构造器匹配的构造函数。否则编译会失败。
- 如果使用旧的编译器回退路径，支持的最大参数个数受 `YGGR_PP_FOO_DEFAULT_PARAMS_LEN`（或相关宏）限制。

文件： [yggr/network/session_helper/owner_generator.hpp](owner_generator.hpp)
