---
packet_cypher_tool.hpp 文档

---

# packet_cypher_tool.hpp 文档

## 概述

packet_cypher_tool.hpp 提供了通用的数据包加解密工具模板类 `packet_cypher_tool`，用于将任意加密工具（如 Blowfish、HMAC、MD5 等）包装为可直接对数据包对象进行加密和解密的工具。该工具适用于网络通信、数据传输等需要对数据包整体加解密的场景。

## 主要内容

### 命名空间

- `yggr::encryption_tool`：加密工具相关代码的命名空间。

### 主要类

#### `template<typename Tool> class packet_cypher_tool`

- **模板参数**
  - `Tool`：实际的加密/解密工具类型（需满足 `is_reductionable_tool`）。

- **继承关系**
  - 继承自 `Tool`，可直接调用其加解密接口。

- **构造与初始化**
  - 支持变参模板构造和初始化（C++11），也支持宏展开的多参数构造（兼容旧编译器）。
  - 构造时自动调用底层加密工具的 `init` 方法。

- **主要成员函数**
  - `void init(Args... args)`：初始化底层加密工具。
  - `bool encrypt(Packet& pak) const`：对数据包进行加密，自动调用包的 `cypher` 方法，并绑定底层工具的 `encrypt`。
  - `bool decrypt(Packet& pak) const`：对数据包进行解密，自动调用包的 `cypher` 方法，并绑定底层工具的 `decrypt`。

- **类型特性**
  - 通过 `is_reductionable_tool` 继承底层工具的可还原性特性。

## 依赖

- 依赖 yggr 框架下的 bind、类型检查、宏工具等。

## 适用场景

适用于需要对自定义数据包类型进行统一加解密操作的 C++ 项目，尤其是基于 yggr 框架的网络通信、协议封装等场景。

---



