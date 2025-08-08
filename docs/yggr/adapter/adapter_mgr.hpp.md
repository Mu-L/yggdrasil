---
# 文件：adapter_mgr.hpp

## 简介

本头文件实现了 yggdrasil 框架中的适配器管理器（adapter_mgr），用于统一管理数据适配器的注册、注销、发送、接收等操作。通过模板参数实现高度通用性，支持多种数据类型和适配器转换方式，适用于复杂的数据流转和适配场景。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发，但需保留版权声明和许可信息。软件按“原样”提供，不附带任何明示或暗示的担保。

## 依赖

- yggdrasil 基础库（如 yggrdef.h、static_constant.hpp、bind.hpp 等）
- Boost 库（如 shared_mutex、type_traits、multi_index、enable_shared_from_this 等）
- 其他辅助模块（如 safe_container、exception、utility、adapter_parser_helper.hpp、adapter_register_type_def.hpp）

## 命名空间

- yggr
  - `adapter`
    - `detail`

## 主要内容

### 1. 适配器基类与实现

- **base_send_adapter / send_adapter**  
  发送适配器基类与实现，负责将标准数据发送到源对象，支持不同数据类型的适配。
- **base_recv_adapter / recv_adapter**  
  接收适配器基类与实现，负责从任务数据中解析结果数据，并支持回调处理。

### 2. 适配器映射（adapter_mapping）

- 用于将发送ID、接收ID与对应的适配器实例（智能指针）进行绑定和管理。
- 支持通过标签（tag_send/tag_recv）访问、交换、合并、清理等操作。

### 3. 注销适配器辅助（unregister_adapter_helper）

- 针对发送ID和接收ID是否相同，分别实现注销逻辑，支持多种注销策略（E_both、E_to_src、E_from_src）。

### 4. 适配器管理器（adapter_mgr）

```cpp
template<
    typename Src,
    typename Send_Std_Data,
    typename Recv_Rst_Data,
    typename ID_Parser_Def,
    template<typename, typename, typename> class Conver,
    typename Mutex = boost::shared_mutex
>
class adapter_mgr;
```

- **主要职责**：
  - 注册/注销适配器（支持单类型、容器类型、指定ID注册等多种方式）
  - 数据发送（send）
  - 数据接收与回调（hold_recv/stop_recv/drop_task/drop_all_tasks）
  - 适配器映射的内部管理（基于 safe_multi_index_container 实现线程安全的多索引管理）
  - 错误处理（内置错误码与异常抛出机制）

- **主要成员类型**：
  - `src_type`：数据源类型
  - `send_std_data_type`：标准发送数据类型
  - `recv_rst_data_type`：接收结果数据类型
  - `id_parser_def_type`：ID 解析器定义
  - `conver_type`：适配器转换器类型
  - `adapter_map_type`：适配器映射容器

- **主要接口**：
  - `register_adapter`：注册适配器
  - `unregister_adapter`：注销适配器
  - `send`：发送数据
  - `hold_recv`：注册接收回调
  - `stop_recv`：停止接收
  - `drop_task`/`drop_all_tasks`：丢弃任务
  - `clear`：清空所有适配器和任务

- **错误处理**：
  - 内置错误码（如 E_invalid_non_reg_adp、E_invalid_not_send）
  - 通过 exception::exception 抛出详细错误信息

### 5. 线程安全

- 适配器映射容器基于 `safe_multi_index_container`，结合 `boost::shared_mutex` 实现多线程安全访问。

## 示例用法

```cpp
// 假设已定义相关类型
typedef yggr::adapter::adapter_mgr<
    MySrc, MySendStdData, MyRecvRstData, MyIDParserDef, MyConver
> my_adapter_mgr;

my_adapter_mgr mgr(src);
mgr.register_adapter<MyRealData>();
mgr.send(data);
mgr.hold_recv(owner_id, handler);
mgr.unregister_adapter<MyRealData>();
mgr.clear();
```

## 结尾

本文件为 yggdrasil 框架提供了强大、灵活且线程安全的适配器管理机制，适用于需要动态注册、注销和调度多种数据适配器的复杂系统。

---
