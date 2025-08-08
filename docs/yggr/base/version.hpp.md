---
# version.hpp 文档

## 文件简介

version.hpp 定义了 Yggdrasil 工程的版本号相关宏，提供主版本号、次版本号、修订号的统一管理，并支持多种格式的版本号生成（十六进制、点分十进制、字符串）。该文件还包含 Boost 版本兼容性检查，确保工程在受支持的 Boost 版本下编译。

---

## 版权声明

版权所有 (c) 2010-2024 yggdrasil  
 <!-- 作者：xu yang  -->
本文件遵循 MIT 许可证。

---

## 依赖

- 必须先包含 `<yggr/base/yggrdef.h>`，否则编译报错。
- `<boost/version.hpp>`

---

## 主要内容

### 1. Boost 版本兼容性检查

- 若 Boost 版本低于 1.53.0，则编译报错：  
  `yggdrasil not support boost 1.52 and older`

### 2. 版本号宏定义

- `YGGR_MAJOR_VERSION`：主版本号（当前为 0）
- `YGGR_MINOR_VERSION`：次版本号（当前为 8）
- `YGGR_MICRO_VERSION`：修订号（当前为 1）

### 3. 版本号格式化宏

- `YGGR_MAKE_VERSION_HEX(__major__, __minor__, __micro__)`  
  生成 32 位十六进制版本号，格式为 `0xMMmmpp00`（M=主，m=次，p=修订）。

- `YGGR_MAKE_VERSION_DOT_DEC(__major__, __minor__, __micro__)`  
  生成点分十进制版本号（如 0.8.1）。

- `YGGR_MAKE_VERSION_DOT_DEC_STRING(__major__, __minor__, __micro__)`  
  生成点分十进制字符串版本号（如 "0.8.1"）。

### 4. 当前版本号宏

- `YGGR_VERSION`：当前点分十进制版本号（如 0.8.1）
- `YGGR_VERSION_S`：当前点分十进制字符串版本号（如 "0.8.1"）
- `YGGR_VERSION_HEX`：当前十六进制版本号（如 0x00080010）

---

## 用法示例

````cpp
#include <yggr/base/version.hpp>

int main() {
    std::cout << "Yggdrasil version: " << YGGR_VERSION_S << std::endl;
    std::cout << "Yggdrasil version (hex): " << std::hex << YGGR_VERSION_HEX << std::endl;
}
````

---

## 注意事项

- 必须先包含 `<yggr/base/yggrdef.h>`，否则会编译报错。
- 仅支持 Boost 1.53.0 及以上版本。
- 推荐所有涉及版本号判断、显示、条件编译等场景统一使用本文件中的宏。

---

 

