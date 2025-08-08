---
# 文件：any_check.hpp

## 简介

any_check.hpp 是 yggdrasil 项目中的头文件，主要用于包含 any_check.hpp，为 `any_val` 相关功能提供类型检查或辅助功能的接口声明。

## 版权声明

本文件遵循 MIT 许可证，允许自由使用、修改、分发和商业用途，但需保留原作者版权声明和许可信息。

 <!-- ## 作者 -->

 <!-- - xu yang -->

## 主要内容

- 头文件保护宏：防止重复包含。
- 包含 any_check.hpp，实际实现细节在该文件中。
- 本文件本身不包含具体实现，仅作为接口转发和保护。

## 用法说明

在需要使用 `any_val` 类型检查相关功能时，包含此头文件即可：

```cpp
#include <yggr/any_val/any_check.hpp>
```

## 依赖

- any_check.hpp

---

如需详细功能说明，请参考 any_check.hpp 文件。

