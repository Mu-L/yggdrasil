---
# 文件：binary_archive_partner.hpp

## 简介

该头文件定义了 Yggdrasil 框架下二进制归档相关的“归档伙伴”类型（archive partner），用于描述和管理二进制输入/输出归档的能力与辅助工具。通过宏或模板，统一了二进制归档类型的元信息和能力检测接口，便于归档系统的扩展和维护。

---

## 主要内容

### 1. 依赖

- `archive_partner_template.hpp`：归档伙伴模板基础设施
- `string_archive_helper.hpp`：字符串归档辅助工具
- `binary_iarchive.hpp` / `binary_oarchive.hpp`：二进制输入/输出归档
- `binary_wiarchive.hpp` / `binary_woarchive.hpp`：宽字符二进制输入/输出归档

---

### 2. 归档伙伴类型定义

根据是否定义 `YGGR_TPL_CONFIG_USING_TPL`，有两种实现方式：

#### 宏方式（默认）

使用 `YGGR_PP_ARCHIVE_PARTENER_TEMPLATE_DECL` 宏快速声明以下四种归档伙伴类型：

- `binary_iarchive_partner`：二进制输入归档伙伴
- `binary_oarchive_partner`：二进制输出归档伙伴
- `binary_wiarchive_partner`：宽字符二进制输入归档伙伴
- `binary_woarchive_partner`：宽字符二进制输出归档伙伴

每个类型都指定了归档类型、辅助类型和支持的模式（`E_Mode_Binary`）。

#### 模板方式

直接用 `archive_partner_template` 模板定义上述四种类型，功能等价。

---

### 3. 主要用途

这些归档伙伴类型用于：

- 统一描述归档类型的能力（如是否支持二进制模式）
- 提供归档类型与辅助工具的类型信息
- 便于归档系统根据类型特性自动选择合适的归档实现

---

## 命名空间

- 所有内容位于 `yggr::archive::archive_partner` 命名空间下。

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的二进制归档类型提供了统一的“伙伴”类型定义，是归档系统类型安全和能力检测的重要基础设施。

