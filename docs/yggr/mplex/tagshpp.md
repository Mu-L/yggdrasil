# `yggr::mplex::tags`（文件：`yggr/mplex/tags.hpp`）

## 概要
- **目的**：在模板元编程与解析/操作符抽象中提供一组轻量的标签类型（空 struct），以及一个可移植的全局 `non_handler` 实例。文件利用预处理宏快速生成大量标签类型以便在代码中作为标记/分发用途。
- **位置**：`yggr/mplex/tags.hpp`（与该文档同目录）
- **适用场景**：实现 tag-dispatch、表达式解析、运算符分类、以及模板重载/特化时使用的类型标签。

## 关键点与实现说明
- 宏 `YGGR_PP_TAGS_DEF(__name__)`：
  - 定义形式：`#define YGGR_PP_TAGS_DEF( __name__ ) \n\tstruct BOOST_PP_CAT( tag_, __name__ ){};`
  - 作用：通过 Boost.Preprocessor 的 `BOOST_PP_CAT` 拼接生成 `tag_<name>` 的空 struct 类型。
  - 使用该宏可以快速声明大量命名一致的标签（例如 `tag_plus`, `tag_minus` 等）。

- `typedef null_type tag_null;`
  - 把项目中通用的 `null_type`（在 `null_t.hpp` 中定义）作为 `tag_null`，用于表示“空标签”或无操作。

- 标签列表（非穷举，按文件顺序示例）：
  - 操作符与运算：`tag_plus`, `tag_minus`, `tag_mul`, `tag_div`, `tag_mod`
  - 赋值/集合类：`tag_set`, `tag_plus_set`, `tag_minus_set`, ...
  - 逻辑/位运算：`tag_logic_and`, `tag_logic_or`, `tag_bitwise_and`, `tag_bitwise_xor`, ...
  - 分隔符与括号：`tag_parentheses`, `tag_brackets`, `tag_braces`, `tag_angle_brackets`, `tag_comma`, `tag_semicolon`, `tag_colon`, ...
  - 数字与布尔：`tag_number_zero` ... `tag_number_nine`, `tag_bool_false`, `tag_bool_true`
  - 以及 `tag_empty`, `tag_question_mark`, `tag_area`, `tag_slash`, `tag_ellipsis` 等。

- 全局 `non_handler` 的可移植定义：
  - 为了兼容不同编译器（Borland, GCC 旧版, MSVC, DEC CXX, Metrowerks 等），文件通过条件编译选择不同的定义方式：
    - 对于某些编译器使用 `inline tag_non_handler __non_handler(){ return tag_non_handler(); }` 并定义宏 `non_handler` 映射到 `__non_handler()`，以避免链接问题；
    - 对部分编译器使用 `static tag_non_handler non_handler;`；
    - 否则直接 `tag_non_handler non_handler;`。
  - 目的是在不同编译器与链接模型下都能安全地提供一个全局 `non_handler` 实例。

- `detail::__fix_non_handler_defined_but_not_used_t`：
  - 提供静态方法 `__fix_non_handler_defined_but_not_used()` 返回 `::yggr::non_handler`，用于消除某些编译器或静态分析器对定义未使用的警告或链接器问题。

## 使用示例
- 简单的 tag-dispatch：
```cpp
#include <iostream>
#include <yggr/mplex/tags.hpp>

// 通用处理函数模板
template<typename Tag>
void handle(Tag) {
    std::cout << "unknown tag\n";
}

// 针对具体标签的重载
void handle(yggr::mplex::tag_plus) { std::cout << "handle plus\n"; }
void handle(yggr::mplex::tag_minus){ std::cout << "handle minus\n"; }

int main(){
    handle(yggr::mplex::tag_plus());   // 输出：handle plus
    handle(yggr::mplex::tag_minus());  // 输出：handle minus
    handle(yggr::mplex::tag_null());   // 输出：unknown tag
}
```

- 在模板元编程中作为类型选择或分支占位：
```cpp
template<typename Tag>
struct is_arithmetic_tag : std::false_type {};

template<>
struct is_arithmetic_tag<yggr::mplex::tag_plus> : std::true_type {};

// 使用示例：
static_assert(is_arithmetic_tag<yggr::mplex::tag_plus>::value, "tag_plus is arithmetic");
```
