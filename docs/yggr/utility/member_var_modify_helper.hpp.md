# member_var_modify_helper.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了成员变量修改辅助器 `member_var_modify_helper`，用于将对象的成员变量包装为可控的“属性代理”，支持类型安全的赋值、访问、修改、交换及丰富的操作符重载。可广泛应用于属性系统、数据同步、UI 绑定、泛型容器等场景。

## 3. 主要类型与功能

### 3.1 member_var_modify_helper_data_store
- 封装对象和成员变量的引用，提供基础的访问和修改接口。
- 支持拷贝、移动、赋值和 swap 操作。
- 针对成员变量为 `null_type` 的情况做了特化处理。

### 3.2 操作符能力扩展
- 通过模板元编程自动检测成员变量类型是否支持 `[]`、`->`、`()` 等操作符，并自动扩展相应的操作符重载。
- 支持链式组合，自动适配成员变量的操作能力。

### 3.3 member_var_modify_helper
- 主模板类，继承自操作能力组合类型。
- 封装对象、成员变量、修改处理器（modify_handler）、视图处理器（view_handler）。
- 支持赋值、swap、类型转换、视图访问等操作。
- 通过操作符重载，支持算术、位运算、比较、逻辑等多种操作，行为与原始成员变量一致。
- 支持泛型赋值和 swap，便于与原始类型或其它 helper 互操作。

### 3.4 操作符重载
- 支持 `+ - * / % & | ^ << >>` 及其复合赋值操作符。
- 支持自增自减、取地址、解引用、正负号、按位取反等一元操作。
- 支持 `== != < <= > >= && || !` 等比较和逻辑操作。
- 支持流输出（operator<<）。

### 3.5 swap 支持
- 提供 swap_support 命名空间下的 swap 重载，支持 helper 与原始类型、helper 与 helper 之间的高效交换。
- swap 导入 std、boost 命名空间，兼容标准库和 Boost 生态。

### 3.6 类型萃取与 SFINAE 支持
- 通过 Boost.TypeTraits、Boost.MPL、SFINAE 技术自动检测和适配成员变量类型特性。
- 兼容 C++03/11，支持右值引用和 Boost.Move。

## 4. 典型用法

```cpp
#include <yggr/utility/member_var_modify_helper.hpp>

struct Foo {
    int value;
};

Foo foo{10};
auto modify_handler = [](Foo& obj, const int& val) { obj.value = val; };
auto view_handler = [](const Foo& obj) { return obj.value; };

yggr::utility::member_var_modify_helper<Foo, int, int, int> helper(
    foo, foo.value, modify_handler, view_handler
);

helper = 20;           // 修改成员变量
int v = helper.view(); // 获取成员变量视图
++helper;              // 支持自增
helper += 5;           // 支持复合赋值
swap(helper, v);       // 支持与原始类型交换
```

## 5. 设计要点

- **类型安全**：所有操作均通过类型萃取和断言保证类型安全。
- **操作符丰富**：支持绝大多数常用操作符，行为与原始类型一致。
- **泛型友好**：可与任意类型成员变量配合，适合模板和泛型编程。
- **高扩展性**：通过元编程自动适配成员变量的操作能力。
- **高性能**：支持右值引用和 Boost.Move，避免不必要的拷贝。

## 6. 注意事项

- 修改和视图处理器需保证线程安全和异常安全。
- 仅适用于成员变量的包装和代理，不建议跨线程保存 helper 指针。
- 若成员变量类型不支持某操作符，则相关重载不可用。

## 7. 总结

本文件为 Yggdrasil 框架提供了功能强大、类型安全、操作丰富的成员变量修改辅助器，适合属性系统、数据同步、UI 绑定、泛型容器等多种复杂场景。其设计兼顾类型安全、性能和易用性，是大型 C++ 工程中成员变量管理和属性封装的理想选择。

---

