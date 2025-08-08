---
# to_params_caller.hpp

该头文件属于 yggdrasil 项目，是参数展开调用工具的统一入口。它通过包含多个相关头文件，提供了将常见容器（如数组、pair、tuple、packet_info）内容作为独立参数传递给可调用对象（如函数、函数对象、lambda 等）的能力。

## 主要功能

- 统一包含并导出以下参数展开调用工具：
  - `array_to_params_caller.hpp`：支持数组（`std::array`、`boost::array`）的参数展开调用。
  - `pair_to_params_caller.hpp`：支持 `std::pair` 的参数展开调用。
  - `tuple_to_params_caller.hpp`：支持元组（`std::tuple`、`boost::tuple`）的参数展开调用。
  - `packet_info_to_params_caller.hpp`：支持 `packet::packet_info` 的参数展开调用。
- 用户只需包含本头文件，即可获得上述所有参数展开调用能力。

## 用法示例

```cpp
#include <yggr/caller/to_params_caller.hpp>

std::tuple<int, double> t(1, 2.5);
auto handler = [](int a, double b) { /* ... */ };
yggr::caller::to_params_call(handler, t); // handler(1, 2.5)
```

## 依赖

- array_to_params_caller.hpp
- pair_to_params_caller.hpp
- tuple_to_params_caller.hpp
- packet_info_to_params_caller.hpp

## 版权声明

```
Copyright (c) 2010-2024 yggdrasil
MIT License
```

---

如需详细用法或扩展说明，请参考各子模块头文件和 yggdrasil 项目文档。

