---
hmacsha256_tool.hpp 文档

---

# hmacsha256_tool.hpp 文档

## 概述

hmacsha256_tool.hpp 提供了 HMAC-SHA256 加密工具类 `hmacsha256_tool`，用于生成和校验基于 SHA256 的消息认证码（HMAC）。该工具支持密钥管理、签名生成、签名与字符串的互转，适用于数据完整性和认证场景。

## 主要内容

### 命名空间

- `yggr::encryption_tool`：加密工具相关代码的命名空间。

### 主要类

#### `class hmacsha256_tool`

- **常量定义**
  - `E_HMACSHA256_SIZE`：HMAC-SHA256 签名长度（字节数）。
  - `E_HMACSHA256_STRING_BUF_SIZE`：签名字符串缓冲区长度（通常为签名字节数的2倍）。
  - `E_HMACSHA256_STRING_LEAST_SIZE`：签名字符串最小长度。
  - `E_default_key_size`：默认密钥长度。

- **类型定义**
  - `value_type`：密钥字节类型（u8）。
  - `key_type`：密钥智能指针类型。
  - `sig_type`：签名类型（定长字节数组）。
  - `check_type`：校验类型（同签名类型）。

- **构造与赋值**
  - 支持默认构造、密钥构造、拷贝构造、移动构造、拷贝赋值、移动赋值。
  - 支持 swap 操作。

- **主要成员函数**
  - `void init(void)`：自动生成随机密钥初始化。
  - `void init(const Oth_Key& oth_key)`：用外部密钥初始化。
  - `std::pair<key_type, u32> get_key(void) const`：获取当前密钥及长度。
  - `sig_type encrypt(const Buffer& buf) const`：对数据进行 HMAC-SHA256 签名。
  - `static yggr::string sig_to_code(const sig_type& sig, ...)`：签名转字符串（支持多字符集）。
  - `static bool code_to_sig(sig_type& sig, const String& code, ...)`：字符串转签名。

- **静态工具函数**
  - 提供签名与字符串的互转，支持多字符集和分配器。

### 其他

- 提供了 `swap` 支持，方便与标准库和 Boost 兼容。
- 依赖 SHA256 算法实现、字符集转换工具、智能指针等。

## 依赖

- 依赖 `SHA256` 实现、yggr 框架下的多种工具和容器。

## 适用场景

适用于需要基于 HMAC-SHA256 进行数据完整性校验、消息认证的 C++ 项目，尤其是基于 yggr 框架的网络通信、数据存储等场景。

---



