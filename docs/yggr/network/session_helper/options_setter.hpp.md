**options_setter.hpp 文档**

简介：
- `options_setter.hpp` 提供了会话（session）中用于设置或验证可选参数的策略类型。该文件目前包含一个简单的默认实现 `empty_options_setter`，以及一个类型别名 `default_options_setter_type`。

内容摘要：
- `empty_options_setter`：一个可调用的空实现，用于在不需要特殊选项设置/验证时作为占位策略。
  - 模板成员函数 `operator()(const T&) const`：接受任意类型的参数（通常是某种 options/配置对象），始终返回 `true`，表示“接受”或“通过”该选项。
- `default_options_setter_type`：别名，指向 `empty_options_setter`，便于在会话模板或默认参数中使用。

用途与约定：
- 在需要对会话相关选项进行注入或验证的场景中，可以提供自定义的 options_setter：
  - 自定义类型应提供与 `empty_options_setter` 相同的可调用接口，例如 `bool operator()(const OptionsType& opt) const`，并根据需要返回 `true`/`false` 表示是否接受或设置成功。
  - `default_options_setter_type` 可用于作为模板参数的默认值，保证在未提供自定义实现时行为为“通过所有选项”。

示例（伪代码）：

```cpp
// 使用默认（什么都不做）
using opts_t = yggr::network::session_helper::default_options_setter_type;
opts_t setter;
bool ok = setter(my_options); // 总是 true

// 自定义实现
struct my_options_setter
{
    bool operator()(const MyOptions& opt) const
    {
        // 验证或设置逻辑
        return opt.is_valid();
    }
};

// 在会话模板中使用：
// session<MyConn, my_options_setter> 或将其作为构造参数注入
```

注意事项：
- `empty_options_setter` 不做任何检查或修改，仅用于简化默认行为；如果需要实际验证或修改 options，请实现自定义选项设置器。
- 该头文件导出了 `session_helper::default_options_setter_type` 为顶层 `yggr::network` 命名空间下的别名，方便引入。

文件： [yggr/network/session_helper/options_setter.hpp](options_setter.hpp)
