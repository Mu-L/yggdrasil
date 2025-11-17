# `yggr::network::io::io_error_def`（文件：`io_error_def.hpp`）

## 概要
- **目的**：定义网络 I/O 模块（`network::io`）相关的错误码集合与对应的错误消息，通过项目中统一的错误码生成宏进行声明。
- **位置**：`yggr/network/io/io_error_def.hpp`（与该文档同目录）。
- **适用场景**：在网络 I/O 层检测到接收/解析错误时使用这些错误码进行异常抛出或记录。

## 文件主要内容（要点）
- 文件使用宏 `YGGR_PP_NETWORK_IO_ERROR_DEF(__io_name__)` 来声明一组错误码、错误码范围及错误消息：

```cpp
#define YGGR_PP_NETWORK_IO_ERROR_DEF( __io_name__ ) \
    ERROR_MAKER_BEGIN( __io_name__ ) \
        ERROR_CODE_DEF_BEGIN(exception::exception_sort::E_code_start_17) \
            ERROR_CODE_DEF(E_invalid_recv_size) \
            ERROR_CODE_DEF(E_invalid_recv_head) \
            ERROR_CODE_DEF(E_invalid_recv_data) \
        ERROR_CODE_DEF_END(exception::exception_sort::E_code_end_17) \
    \
        ERROR_CODE_MSG_BEGIN() \
            ERROR_CODE_MSG(E_invalid_recv_size, "invalid recv size") \
            ERROR_CODE_MSG(E_invalid_recv_head, "invalid recv head") \
            ERROR_CODE_MSG(E_invalid_recv_data, "invalid recv data") \
        ERROR_CODE_MSG_END() \
    ERROR_MAKER_END()
```

- 该宏依赖于项目范围内的一组错误/异常工具宏：`ERROR_MAKER_BEGIN` / `ERROR_CODE_DEF_BEGIN` / `ERROR_CODE_DEF` / `ERROR_CODE_MSG` / `ERROR_MAKER_END`，以及 `exception::exception_sort::E_code_start_17` 等常量。

## 定义的错误码（语义）
- `E_invalid_recv_size` — 接收的数据长度不符合预期（例如头部声明长度与实际接收长度不一致）。
- `E_invalid_recv_head` — 接收的数据包头解析失败或头部字段非法。
- `E_invalid_recv_data` — 接收的数据体解析失败或内容非法（例如校验错误或结构不匹配）。

每个错误码在宏中同时注册了文本消息：
- `"invalid recv size"`
- `"invalid recv head"`
- `"invalid recv data"`

## 用法示例
- 在某个 I/O 模块源文件中展开该宏以定义对应模块的错误集合：
```cpp
// 假设在 io 模块入口处：
YGGR_PP_NETWORK_IO_ERROR_DEF(network_io)
```
- 之后，项目的错误/异常设施会基于该宏生成枚举值、错误码与消息映射，供抛出或记录使用。例如：
```cpp
throw yggr::exception::make_error(network_io::E_invalid_recv_head);
```
（具体 API 取决于项目中 `ERROR_MAKER` 宏家族的实现）

## 依赖项与注意事项
- 该头文件依赖：
  - `yggr/exception/exception.hpp`（异常与错误类型定义）
  - `yggr/base/error_make.hpp`（错误码生成/宏定义）
- 宏 `ERROR_MAKER_*` 的具体定义位于项目的错误/异常工具头中，使用前需确保这些宏可用并理解它们如何展开（枚举、字符串表、工厂函数等）。
- `exception::exception_sort::E_code_start_17` 与 `E_code_end_17` 指定了该错误码所属的范围编号，避免不同模块间错误码冲突。

