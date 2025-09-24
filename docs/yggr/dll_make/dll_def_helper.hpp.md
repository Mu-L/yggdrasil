---
dll_def_helper.hpp 文档

---

# 文件：dll_def_helper.hpp

## 简介

该头文件为 yggdrasil 项目提供了用于简化 DLL 导出函数声明的宏定义。通过一系列宏，可以方便地为不同参数数量的函数生成标准的 DLL 导出声明，提升跨平台开发和接口维护的效率。

## 主要内容

### 版权声明

- 版权：2010-2024 yggdrasil
- 许可协议：MIT License

### 依赖

- `<yggr/ppex/open.hpp>`
- `<yggr/ppex/params_expand.hpp>`
- `<yggr/dll_make/dll_mark_define.hpp>`

### 宏定义

- `YGGR_DLL_MAKE_API_0` ~ `YGGR_DLL_MAKE_API_10`  
  用于生成带有 0~10 个参数的 DLL 导出函数声明。

- `YGGR_DLL_MAKE_API_N`  
  支持可变参数（C++11 及以上），自动展开参数列表，适用于参数数量不定的情况。

- `YGGR_DLL_MAKE_API`  
  别名，等同于 `YGGR_DLL_MAKE_API_N`。

### 命名空间

- `yggr::dll_make`  
  预留命名空间，便于后续扩展。

## 用法示例

```cpp
// 声明一个无参数的 DLL 导出函数
YGGR_DLL_MAKE_API_0(void, foo);

// 声明一个带两个参数的 DLL 导出函数
YGGR_DLL_MAKE_API_2(int, bar, int a, float b);

// 使用可变参数宏（C++11 及以上）
YGGR_DLL_MAKE_API(MyType, my_func, int a, double b, const char* c);
```

## 适用场景

- 跨平台 DLL 导出接口声明
- 动态库 API 统一声明风格
- 支持多参数和可变参数的导出函数

---


