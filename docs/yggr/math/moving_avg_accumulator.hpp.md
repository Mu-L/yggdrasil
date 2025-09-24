---
GitHub Copilot: moving_avg_accumulator.hpp 文档

---

# moving_avg_accumulator.hpp

## 简介

该头文件实现了多种滑动平均（Moving Average）累加器的元编程工厂和类型检查工具，支持简单、加权、指数等多种滑动平均算法的组合与泛型扩展。适用于信号处理、金融分析、数据平滑等需要滑动平均的场景。

## 主要内容

### 1. make_accumulator 模板结构体

```cpp
template<typename Val, typename Collector, typename Cdt_Genner, typename Result_Getter, typename Calculator>
struct make_accumulator
{
    // ...
    typedef yggr::tuple<Val, Collector, Cdt_Genner, Result_Getter, Calculator> type;
};
```
- **功能**：将滑动平均相关类型（值类型、收集器、条件生成器、结果获取器、计算器）组合为元组，便于统一管理和泛型扩展。
- **类型约束**：要求 `Val` 必须为浮点型或有符号整型。

### 2. make_accumlator_group 模板结构体

- **功能**：批量生成滑动平均累加器类型组（元组），支持多种滑动平均算法的组合。

### 3. maa_check_group 元编程类型检查

- **功能**：递归检查累加器组中各类型是否匹配，保证滑动平均算法组合的类型安全。
- **实现**：利用 Boost MPL 和元组工具，递归判断各类型之间的兼容性。

### 4. 依赖与扩展

- 支持多种滑动平均算法（SMA、CMA、MMA、EMA、WMA），通过包含相关头文件实现。
- 依赖 tuple.hpp、`yggr/math/moving_avg/*`、Boost MPL、类型萃取等。

## 典型用途

- 金融行情、传感器数据、实时信号等滑动平均处理。
- 泛型算法、模板元编程场景下的滑动平均算法组合与类型安全校验。

---



