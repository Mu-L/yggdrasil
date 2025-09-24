---
GitHub Copilot: inner_process_id.hpp 文档

---

# 文件：inner_process_id.hpp

## 版权声明
- 版权所有 (c) 2010-2024 yggdrasil

- 采用 MIT 许可协议，允许自由使用、复制、修改、分发等。

## 主要内容

### 1. 进程内ID类型
#### `class inner_process_id`
- 继承自 `id_n<sizeof(id64_type) + sizeof(id64_type)>`，实现了由主ID和内部ID组成的复合定长ID。
- 支持通过主ID、内部ID、迭代器、容器等多种方式构造。
- 提供拷贝、移动、赋值、比较等操作。
- 适用于进程内对象、任务、会话等唯一标识场景。

### 2. 辅助比较器
- `detail::inner_process_id_id_data_cmp_helper`：用于高效比较 `inner_process_id` 与其底层数据结构，支持不同内存布局。

### 3. 依赖与特性
- 依赖 Yggdrasil 基础类型、定长ID、Boost 原子与哈希、序列化、数学符号判断等。
- 支持序列化、哈希、字节级比较、类型安全等高级功能。

---

## 用途说明
本文件为Yggdrasil系统提供了进程内唯一标识符的实现，适用于多线程、分布式、对象唯一性等需要高效复合ID的场景。



