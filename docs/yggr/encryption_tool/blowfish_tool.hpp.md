---
blowfish_tool.hpp 文档

---

# blowfish_tool.hpp 文档

## 概述

blowfish_tool.hpp 提供了一个基于 Blowfish 算法的加解密工具模板类 `blowfish_tool`，支持自定义密钥长度和加密模式。该工具适用于需要对数据进行对称加密和解密的场景，封装了密钥管理、加解密流程，并对异常和内存管理做了安全处理。

## 主要内容

### 命名空间

- `yggr::encryption_tool`：加密工具相关代码的命名空间。

### 主要类

#### `template<u32 Key_Len = 8, u32 Mode = CBlowFish::ECB> class blowfish_tool`

- **模板参数**
  - `Key_Len`：密钥长度，默认为8字节，且必须为8的倍数。
  - `Mode`：Blowfish 加密模式，默认为 ECB。

- **类型定义**
  - `blowfish_type`：Blowfish 算法实现类型。
  - `blowfish_ptr_type`：Blowfish 算法智能指针类型。
  - `value_type`：密钥字节类型（u8）。
  - `key_type`：密钥智能指针类型。

- **构造与赋值**
  - 支持默认构造、密钥构造、拷贝构造、移动构造、拷贝赋值、移动赋值。
  - 支持 swap 操作。

- **主要成员函数**
  - `void init(const Oth_Key& oth_key)`：用外部密钥初始化。
  - `void init(void)`：自动生成随机密钥初始化。
  - `bool encrypt(Buffer& buf) const`：加密数据缓冲区。
  - `bool decrypt(Buffer& buf) const`：解密数据缓冲区。
  - `std::pair<key_type, u32> get_key(void) const`：获取当前密钥及长度。

- **内部实现**
  - 加密时会对数据进行填充，保证长度为8字节的倍数，并在数据头部存储原始长度。
  - 解密时会校验长度并恢复原始数据。

### 其他

- 提供了 `swap` 支持，方便与标准库和 Boost 兼容。
- 通过 `is_reductionable_tool` 进行类型特性标记。

## 依赖

- 依赖 `CBlowFish` 实现、`blowfish_exception` 异常类，以及 yggr 框架下的多种工具和容器。

## 适用场景

适用于需要高效对称加密/解密的 C++ 项目，尤其是基于 yggr 框架的网络通信、数据存储等场景。

---
