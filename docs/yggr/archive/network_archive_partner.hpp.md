---
# 文件：network_archive_partner.hpp

## 简介

该头文件定义了 Yggdrasil 框架下网络归档相关的“归档伙伴”类型（archive partner），用于描述和管理网络输入/输出归档的能力与辅助工具。通过宏或模板，统一了网络归档类型的元信息和能力检测接口，便于归档系统的扩展和维护，适用于网络通信场景下的数据序列化与反序列化。

---

## 主要内容

### 1. 依赖

- `archive_partner_template.hpp`：归档伙伴模板基础设施
- `string_archive_helper.hpp`：字符串归档辅助工具
- `net_iarchive.hpp` / `net_oarchive.hpp`：网络输入/输出归档
- `network/socket_conflict_fixer.hpp`：网络环境兼容性处理

---

### 2. 归档伙伴类型定义

根据是否定义 `YGGR_TPL_CONFIG_USING_TPL`，有两种实现方式：

#### 宏方式（默认）

使用 `YGGR_PP_ARCHIVE_PARTENER_TEMPLATE_DECL` 宏快速声明以下两种网络归档伙伴类型：

- `network_iarchive_partner`  
  - 归档类型：`archive::net_iarchive`
  - 辅助类型：`archive_helper::string_archive_helper<archive::net_iarchive>`
  - 支持模式：`archive_partner_t::E_Mode_Network`

- `network_oarchive_partner`  
  - 归档类型：`archive::net_oarchive`
  - 辅助类型：`archive_helper::string_archive_helper<archive::net_oarchive>`
  - 支持模式：`archive_partner_t::E_Mode_Network`

#### 模板方式

直接用 `archive_partner_template` 模板定义上述两种类型，功能等价。

---

### 3. 主要用途

这些归档伙伴类型用于：

- 统一描述网络归档类型的能力（如是否支持网络模式）
- 提供归档类型与辅助工具的类型信息
- 便于归档系统根据类型特性自动选择合适的归档实现

---

## 命名空间

- 所有内容位于 `yggr::archive::archive_partner` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的网络归档类型提供了统一的“伙伴”类型定义，是归档系统类型安全和能力检测的重要基础设施，便于网络数据的序列化与反序列化扩展。

