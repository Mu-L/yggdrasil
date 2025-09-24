---
dll_imp_helper.hpp 文档

---

# 文件：dll_imp_helper.hpp

## 简介

该头文件为 yggdrasil 项目提供了用于简化 DLL 导出函数指针类型声明的宏定义。通过一系列宏，可以方便地为不同参数数量的 DLL 导出函数生成标准的函数指针类型声明，便于动态库接口的实现和调用。

## 主要内容

### 版权声明

- 版权：2010-2024 yggdrasil
- 许可协议：MIT License

### 依赖

- `<yggr/ppex/open.hpp>`
- `<yggr/dll_make/dll_mark_define.hpp>`

### 宏定义

- `YGGR_DLL_MAKE_API_TYPE_0` ~ `YGGR_DLL_MAKE_API_TYPE_11`  
  用于生成带有 0~11 个参数的 DLL 导出函数指针类型声明。

- `YGGR_DLL_MAKE_API_TYPE_N`  
  支持可变参数（C++11 及以上），自动展开参数列表，适用于参数数量不定的函数指针类型声明。

- `YGGR_DLL_MAKE_API_TYPE`  
  别名，等同于 `YGGR_DLL_MAKE_API_TYPE_N`。

### 命名空间

- `yggr::dll_make`  
  预留命名空间，便于后续扩展。

## 用法示例

```cpp
// 声明一个无参数的 DLL 导出函数指针类型
YGGR_DLL_MAKE_API_TYPE_0(void, foo_type);

// 声明一个带两个参数的 DLL 导出函数指针类型
YGGR_DLL_MAKE_API_TYPE_2(int, bar_type, int a, float b);

// 使用可变参数宏（C++11 及以上）
YGGR_DLL_MAKE_API_TYPE(MyType, my_func_type, int a, double b, const char* c);
```

## 适用场景

- 跨平台 DLL 导出函数指针类型声明
- 动态库 API 的类型安全调用
- 支持多参数和可变参数的导出函数指针类型声明

---


