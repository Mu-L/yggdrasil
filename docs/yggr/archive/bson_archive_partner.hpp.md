---
# 文件：bson_archive_partner.hpp

## 简介

该头文件定义了 Yggdrasil 框架下 BSON 归档相关的“归档伙伴”类型（archive partner），用于描述和管理多种 BSON 输入/输出归档的能力与辅助工具。通过宏或模板，统一了 BSON 归档类型的元信息和能力检测接口，便于归档系统的扩展和维护。

---

## 主要内容

### 1. 依赖

- `archive_partner_template.hpp`：归档伙伴模板基础设施
- `bson_archive_helper.hpp`：BSON 归档辅助工具
- `bson_iarchive.hpp` / `bson_oarchive.hpp`：BSON 输入/输出归档

---

### 2. 归档伙伴类型定义

根据是否定义 `YGGR_TPL_CONFIG_USING_TPL`，有两种实现方式：

#### 宏方式（默认）

使用 `YGGR_PP_ARCHIVE_PARTENER_TEMPLATE_DECL` 宏快速声明以下四种 BSON 归档伙伴类型：

- `bson_iarchive_partner`  
  - 归档类型：`archive::bson_iarchive<true>`
  - 辅助类型：`archive_helper::bson_archive_helper<archive::bson_iarchive<true>>`
  - 支持模式：`E_Mode_Bson`
- `bson_conv_iarchive_partner`  
  - 归档类型：`archive::bson_iarchive<false>`
  - 辅助类型：`archive_helper::bson_archive_helper<archive::bson_iarchive<false>>`
  - 支持模式：`E_Mode_Bson`
- `bson_oarchive_partner`  
  - 归档类型：`archive::bson_oarchive<false>`
  - 辅助类型：`archive_helper::bson_archive_helper<archive::bson_oarchive<false>>`
  - 支持模式：`E_Mode_Bson`
- `bson_nld_oarchive_partner`  
  - 归档类型：`archive::bson_oarchive<true>`
  - 辅助类型：`archive_helper::bson_archive_helper<archive::bson_oarchive<true>>`
  - 支持模式：`E_Mode_Bson`

#### 模板方式

直接用 `archive_partner_template` 模板定义上述四种类型，功能等价。

---

### 3. 别名定义

- `bson_io_iarchive_partner`：等同于 `bson_iarchive_partner`
- `bson_io_oarchive_partner`：等同于 `bson_oarchive_partner`
- `bson_conv_oarchive_partner`：等同于 `bson_oarchive_partner`

---

### 4. 主要用途

这些归档伙伴类型用于：

- 统一描述 BSON 归档类型的能力（如是否支持 BSON 模式）
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

本文件为 Yggdrasil 框架下的 BSON 归档类型提供了统一的“伙伴”类型定义，是归档系统类型安全和能力检测的重要基础设施，便于 BSON 数据的序列化与反序列化扩展。

