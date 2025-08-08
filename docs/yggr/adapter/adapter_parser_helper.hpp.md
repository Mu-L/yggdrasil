---
# 文件：adapter_parser_helper.hpp

## 简介

该头文件定义了适配器ID解析相关的辅助模板和宏，主要用于统一管理和解析各种ID类型。适用于 yggdrasil 框架中需要对不同ID解析器进行统一封装和类型校验的场景。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。软件按“原样”提供，不附带任何明示或暗示的担保。

## 依赖

- yggrdef.h
- static_assert.hpp
- ids_parsers.hpp
- Boost.TypeTraits（如 `is_same`, `remove_reference`, `remove_const`）

## 命名空间

- yggr
  - `adapter`

## 主要内容

### 1. 模板结构体：adapter_id_parser_def

```cpp
template<
    typename Reg_Send_ID_Parser,
    typename Reg_Recv_ID_Parser,
    typename Send_ID_Parser,
    typename Task_Send_ID_Parser,
    typename Task_Recv_ID_Parser,
    typename Recv_ID_Parser
>
struct adapter_id_parser_def { ... };
```

- 封装了六种ID解析器类型，并通过类型萃取获得对应的ID类型（去除引用和常量修饰）。
- 使用 `BOOST_MPL_ASSERT` 静态断言，确保相关ID类型一致性（如 `reg_send_id_type` 与 `send_id_type` 必须相同）。

### 2. 宏：YGGR_ADAPTER_ID_PARSER_DEF

用于快速定义与 `adapter_id_parser_def` 类似的结构体，并自动添加类型一致性静态断言。

### 3. 模板结构体：adapter_id_parser

```cpp
template<typename TagSend, typename TagRecv, typename Parser_Def>
struct adapter_id_parser { ... };
```

- 封装了发送和接收的标签类型，以及解析器定义类型。
- 内部定义了 `selector` 模板结构体，根据标签类型（发送/接收）选择不同的ID解析逻辑。
- 提供统一的接口方法：
  - `task_id`：获取任务ID
  - `value_id`：获取值ID
  - `reg_value_id`：获取注册值ID

### 4. selector 内部结构体

- 针对 `tag_send` 和 `tag_recv`，分别实现了对应的ID解析方法，便于在不同上下文下调用合适的解析器。

## 示例用法

```cpp
// 假设已定义相关ID解析器类型
typedef yggr::adapter::adapter_id_parser_def<
    MyRegSendIDParser, MyRegRecvIDParser, MySendIDParser,
    MyTaskSendIDParser, MyTaskRecvIDParser, MyRecvIDParser
> my_parser_def;

typedef yggr::adapter::adapter_id_parser<
    MyTagSend, MyTagRecv, my_parser_def
> my_adapter_id_parser;

my_adapter_id_parser parser;
auto id = parser.task_id<MyTagSend>(my_task);
```

## 结尾

本文件为适配器ID解析提供了高度通用和类型安全的辅助工具，适用于需要灵活切换和校验多种ID解析器的复杂场景。

---

