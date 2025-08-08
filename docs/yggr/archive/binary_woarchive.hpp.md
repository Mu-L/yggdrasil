---
# 文件：binary_woarchive.hpp

## 简介

该头文件定义了 Yggdrasil 框架下的宽字符二进制输出归档类 `binary_woarchive` 及其裸归档版本 `naked_binary_woarchive`，用于将 C++ 对象以宽字符格式序列化（写入）到二进制流（如 `std::wostream`）中。该类基于 Boost.Serialization 的归档机制，支持类型注册、宽字符流兼容和序列化补丁，适用于宽字符环境下的高效二进制序列化。

---

## 主要内容

### 1. 依赖

- `binary_oarchive_impl.hpp`：二进制输出归档实现模板
- `archive_data_wrap_traits.hpp`：归档数据包装特性
- `impl/codecvt_null.hpp`、`impl/utf8_codecvt_facet.hpp`：字符集转换支持
- Boost.Serialization 相关头文件

---

### 2. 类定义

#### `binary_woarchive`

```cpp
class binary_woarchive
    : public binary_oarchive_impl<
            yggr::archive::binary_woarchive,
            std::wostream::char_type,
            std::wostream::traits_type
        >
{
public:
    typedef std::wostream::char_type char_type;
    typedef std::wostream::traits_type traits_type;
    typedef binary_oarchive_impl<
            yggr::archive::binary_woarchive,
            std::wostream::char_type,
            std::wostream::traits_type
        > base_type;

    binary_woarchive(std::wostream & os, unsigned int flags = 0)
        : base_type(os, flags) {}

    binary_woarchive(std::wstreambuf & bsb, unsigned int flags = 0)
        : base_type(bsb, flags) {}
};
```

- **用途**：标准宽字符二进制输出归档，支持通过宽字符输出流或流缓冲区构造。
- **别名**：`typedef binary_woarchive naked_binary_woarchive;`  
  裸归档类型，功能等同于 `binary_woarchive`。

---

### 3. 类型注册与序列化补丁

- `BOOST_SERIALIZATION_REGISTER_ARCHIVE(yggr::archive::binary_woarchive)`  
  注册归档类型，便于 Boost.Serialization 导出机制识别。
- 包含 `oserializer_patch.hpp`，对 Boost 的非指针类型序列化做补丁处理，并通过宏自动应用到本归档类型。

---

### 4. 兼容性

- 若平台不支持宽字符流（`BOOST_NO_STD_WSTREAMBUF`），则编译时报错。

---

## 命名空间

- 主要内容位于 `yggr::archive` 命名空间下
- 类型注册相关内容位于 `boost` 命名空间下

---

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改和分发。

---

## 总结

本文件为 Yggdrasil 框架下的宽字符二进制输出归档提供了标准实现，兼容 Boost.Serialization，支持类型注册、宽字符流和序列化补丁，适用于宽字符环境下的高效二进制序列化场景。

