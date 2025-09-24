---
GitHub Copilot: odd_even_number.hpp 文档

---

# odd_even_number.hpp

## 简介

该头文件实现了奇偶性判断的泛型工具，支持运行时和编译时判断任意类型（主要为整数类型）的奇数和偶数。适用于算法开发、模板元编程、数值分析等需要奇偶性判断的场景。

## 主要内容

### 1. odd_checker / even_checker 模板结构体

- **功能**：运行时判断一个数是否为奇数或偶数。
- **实现**：
  - 对于整数类型，直接通过按位与 `1` 判断。
  - 对于非整数类型，先转换为整数再判断。
- **用法**：
  ```cpp
  odd_checker<int> odd_chk(5);
  bool is_odd = odd_chk; // true
  even_checker<int> even_chk(6);
  bool is_even = even_chk; // true
  ```

### 2. odd_t_checker / even_t_checker 编译时判断

- **功能**：在编译期判断常量是否为奇数或偶数，适用于模板元编程。
- **实现**：继承自 `boost::mpl::bool_`，可用于静态断言和类型选择。

### 3. is_odd_number / is_even_number 函数模板

- **功能**：运行时判断任意类型变量的奇偶性，返回 `bool` 或自定义类型。
- **用法**：
  ```cpp
  bool b1 = is_odd_number(7); // true
  bool b2 = is_even_number(8); // true
  ```

### 4. is_odd_number_t / is_even_number_t 编译时类型

- **功能**：编译期常量判断，适合模板元编程。

### 5. 依赖关系

- 依赖 Boost MPL、类型萃取等。

## 典型用途

- 算法开发、模板元编程、数值分析等需要奇偶性判断的场景。
- 支持运行时和编译时两种方式，便于泛型和高性能开发。

---



