---
# endian.hpp 文档

## 文件简介

endian.hpp 用于检测和定义当前平台的字节序（Endian），为 Yggdrasil 工程提供统一的字节序宏。通过适配不同 Boost 版本的字节序检测机制，自动定义大端、小端、PDP端等相关宏，便于跨平台处理二进制数据的序列化、网络传输等场景。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- 必须先包含 `<yggr/base/yggrdef.h>`
- Boost 1.69.0 及以下：`<boost/detail/endian.hpp>`
- Boost 1.69.0 及以上：`<boost/predef/other/endian.h>`

---

## 主要内容

### 1. 头文件包含保护

- 若未先包含 `yggrdef.h`，则编译报错，确保类型和基础配置一致。

### 2. 字节序宏定义（兼容不同 Boost 版本）

#### Boost 1.69.0 及以下

- 通过 endian.hpp 检测并定义：
  - `YGGR_BIG_ENDIAN`：大端字节序
  - `YGGR_LITTLE_ENDIAN`：小端字节序
  - `YGGR_PDP_ENDIAN`：PDP 字节序
  - `YGGR_BYTE_ORDER`：字节序数值（如 4321、1234、2143）

#### Boost 1.69.0 及以上

- 通过 `boost/predef/other/endian.h` 检测并定义：
  - `YGGR_BIG_ENDIAN`：大端字节序（`BOOST_ENDIAN_BIG_BYTE`）
  - `YGGR_LITTLE_ENDIAN`：小端字节序（`BOOST_ENDIAN_LITTLE_BYTE`）
  - `YGGR_PDP_ENDIAN`：PDP 字节序（`BOOST_ENDIAN_LITTLE_WORD`）
  - `YGGR_BYTE_ORDER`：字节序数值（4321、1234、2134）

---

## 用法说明

- 通过检测宏 `YGGR_BIG_ENDIAN`、`YGGR_LITTLE_ENDIAN`、`YGGR_PDP_ENDIAN`，可在代码中安全判断当前平台字节序，进行字节序相关处理。
- `YGGR_BYTE_ORDER` 提供了数值型的字节序标识，便于条件编译或运行时判断。

````cpp
#if defined(YGGR_BIG_ENDIAN)
// 大端处理
#elif defined(YGGR_LITTLE_ENDIAN)
// 小端处理
#endif
````

---

## 注意事项

- 推荐所有涉及二进制数据处理、网络通信、文件序列化等场景均通过这些宏进行字节序判断，保证跨平台兼容性。
- 宏的具体定义会根据 Boost 版本自动适配，无需手动干预。

---

 

