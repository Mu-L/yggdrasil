---
safe_packet_tool.hpp 文档

---

# safe_packet_tool.hpp 文档

## 概述

safe_packet_tool.hpp 提供了安全数据包加解密工具模板类 `safe_packet_tool`，将加密工具与校验工具结合，实现数据包的加密和完整性校验。该工具适用于需要同时保证数据机密性和完整性的场景，如网络通信、数据传输等。

## 主要内容

### 命名空间

- `yggr::encryption_tool`：加密工具相关代码的命名空间。

### 主要类

#### `template<typename Encryption_Tool, typename Check_Tool> class safe_packet_tool`

- **模板参数**
  - `Encryption_Tool`：实际的加密/解密工具类型（需满足 `is_reductionable_tool`）。
  - `Check_Tool`：校验工具类型（如 HMAC、MD5 等）。

- **类型定义**
  - `key_type`：密钥类型（与加密工具一致）。
  - `encrypt_key_type`：加密工具密钥类型。
  - `check_key_type`：校验工具密钥类型。

- **构造与初始化**
  - 支持默认构造、拷贝构造。
  - 支持变参模板初始化（C++11）和宏展开的多参数初始化（兼容旧编译器）。
  - 可分别初始化加密工具和校验工具。

- **主要成员函数**
  - `void init(Args... args)`：初始化加密工具。
  - `void init_encrypt_tool(Args... args)`：单独初始化加密工具。
  - `void init_check_tool(Args... args)`：单独初始化校验工具。
  - `std::pair<encrypt_key_type, u32> get_key() const`：获取加密工具密钥。
  - `std::pair<check_key_type, u32> get_check_tool_key() const`：获取校验工具密钥。
  - `bool encrypt(Buffer& buf) const`：对数据包加密并附加校验码。
  - `bool decrypt(Buffer& buf) const`：解密数据包并校验完整性。

- **加解密流程**
  - 加密时，先用校验工具生成校验码，拼接到数据前，再整体加密。
  - 解密时，先解密，再分离校验码和数据，校验通过才返回数据。

- **类型特性**
  - 通过 `is_reductionable_tool` 继承加密工具的可还原性特性。

## 依赖

- 依赖 yggr 框架下的类型检查、宏工具等。

## 适用场景

适用于需要对数据包进行加密并保证完整性的 C++ 项目，尤其是基于 yggr 框架的网络通信、协议封装等场景。

---
