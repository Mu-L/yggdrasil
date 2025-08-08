---
# 文件：archive_partner_template.hpp

## 简介

该头文件定义了归档伙伴（archive partner）相关的模板类和宏，用于描述和管理不同归档类型（如网络、XML、文本、二进制、SQL、BSON等）的支持特性。通过模板和静态常量，便于统一管理归档类型的能力检测和元信息获取。

---

## 主要内容

### 1. `archive_partner_t` 结构体

```cpp
struct archive_partner_t
{
    YGGR_STATIC_CONSTANT(u32, E_Mode_Start = 0x00000000);
    YGGR_STATIC_CONSTANT(u32, E_Mode_Network = 0x00000001);
    YGGR_STATIC_CONSTANT(u32, E_Mode_XML = 0x00000002);
    YGGR_STATIC_CONSTANT(u32, E_Mode_Text = 0x00000004);
    YGGR_STATIC_CONSTANT(u32, E_Mode_Binary = 0x00000008);
    YGGR_STATIC_CONSTANT(u32, E_Mode_Sql = 0x00000010); // 目前未支持
    YGGR_STATIC_CONSTANT(u32, E_Mode_Bson = 0x00000020);
    YGGR_STATIC_CONSTANT(u32, E_Mode_End = 0xffffffff);
};
```

- **用途**：定义各种归档模式的标志位（以位掩码方式），用于后续归档类型的能力描述。

---

### 2. 归档伙伴模板宏

#### `YGGR_PP_ARCHIVE_PARTENER_TEMPLATE_DECL`

```cpp
#define YGGR_PP_ARCHIVE_PARTENER_TEMPLATE_DECL(__name__, Archive, Archive_Helper, Mode) \
    class __name__ : private nonable::noncreateable { ... }
```

- **用途**：快速声明一个归档伙伴类型，指定归档类型、辅助类型和支持的模式。
- **成员**：
  - `archive_type`、`archive_helper_type` 类型别名
  - 静态常量 `E_Mode`
  - 一系列静态成员函数用于检测是否支持某种归档模式（如 `is_support_network()` 等）
  - `mode()` 返回支持的模式

---

### 3. `archive_partner_template` 模板类

```cpp
template<typename Archive, typename Archive_Helper, u32 Mode>
class archive_partner_template : private nonable::noncreateable
{
    // 类型别名
    // 静态常量 E_Mode
    // 支持检测函数
    // mode() 获取模式
};
```

- **用途**：通用的归档伙伴模板，便于通过模板参数自定义归档类型、辅助类型和支持的模式。
- **成员函数**：
  - `is_support_network()`：是否支持网络归档
  - `is_support_xml_file()`：是否支持 XML 文件归档
  - `is_support_text_file()`：是否支持文本文件归档
  - `is_support_binary_file()`：是否支持二进制文件归档
  - `is_support_sql()`：是否支持 SQL 归档
  - `is_support_bson()`：是否支持 BSON 归档
  - `mode()`：返回当前支持的模式

- **特性**：继承自 `nonable::noncreateable`，禁止实例化，仅用于静态接口和类型信息。

---

## 命名空间

- 所有内容位于 `yggr::archive::archive_partner` 命名空间下。

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为归档类型的能力描述和统一管理提供了模板化、类型安全的基础设施，便于扩展和维护多种归档格式的支持能力。

