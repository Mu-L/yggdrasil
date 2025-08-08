---
# string_charset_helper.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了**字符串与字符集信息绑定的泛型辅助工具**，即 `string_charset_helper` 及其相关工具函数和类型 traits。它用于在泛型编程中，将字符串数据与其字符集（编码）信息一同传递和管理，极大方便了多字符集环境下的字符串处理、编码转换等场景。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心类**：`string_charset_helper<T1, T2>`
- **辅助 traits**：`is_string_charset_helper`、`is_string_charset_helper_ex`
- **辅助函数**：`make_string_charset_helper`、`string_charset_helper_data`、`string_charset_helper_first`、`string_charset_helper_second`
- **类型萃取**：`string_charset_helper_first_t`、`string_charset_helper_second_t`

---

## 主要功能

### 1. string_charset_helper 类模板

```cpp
template<typename T1, typename T2 = const yggr::string&>
class string_charset_helper;
```

- **功能**：将字符串数据（T1）与字符集名称（T2，通常为 `const string&`）绑定在一起，形成一个二元组对象。
- **成员变量**：
  - `first`：字符串数据（如 char、wchar_t、const char*、std::string、std::wstring 等）
  - `second`：字符集名称（如 "utf-8", "gbk", "utf-16le" 等）
- **不可移动**：继承自 `nonable::nonmoveable`，防止误用。

### 2. 类型 traits

- `is_string_charset_helper<T>`  
  判断类型 T 是否为 `string_charset_helper` 实例。
- `is_string_charset_helper_ex<T>`  
  支持去除 const/reference 修饰后的判断。
- `is_convertible_utf8_string<string_charset_helper<T1, T2>>`  
  标记 string_charset_helper 可用于 UTF-8 字符串转换。

### 3. 类型萃取

- `string_charset_helper_first_t<T>`  
  获取 string_charset_helper 的第一个模板参数类型（字符串类型）。
- `string_charset_helper_second_t<T>`  
  获取 string_charset_helper 的第二个模板参数类型（字符集名称类型）。

### 4. 辅助构造函数

- `make_string_charset_helper(...)`  
  支持多种输入类型（char、wchar_t、char*、const char*、std::string、std::wstring、字符串视图等），自动推导字符集名称并生成 string_charset_helper 对象。也可手动指定字符集名称。
- 支持对字符串对象、字符串视图、C 风格字符串等的重载，便于泛型调用。

### 5. 数据访问与解包

- `string_charset_helper_first(...)`  
  获取 string_charset_helper 的字符串数据部分。
- `string_charset_helper_second(...)`  
  获取 string_charset_helper 的字符集名称部分。

### 6. 兼容 UTF-8 工具

- 支持与 `utf8_string_t_getter` 等 UTF-8 工具类协作，便于自动编码转换。

---

## 设计说明

- **泛型友好**：支持任意字符串类型、字符类型、字符串视图、标准字符串、boost 字符串等。
- **类型安全**：大量使用 SFINAE、traits、enable_if，防止类型误用。
- **自动编码适配**：默认自动推导字符集名称，也可手动指定，适合多编码环境。
- **高效实现**：所有辅助函数均为 inline，零额外开销。
- **与 yggdrasil 框架深度集成**：依赖于框架的字符串类型、traits、编码配置等。

---

## 用法示例

```cpp
#include <yggr/charset/string_charset_helper.hpp>
#include <string>

// 绑定 char 字符和编码
auto h1 = yggr::charset::make_string_charset_helper('A'); // 默认编码 "utf-8"

// 绑定 C 风格字符串和编码
auto h2 = yggr::charset::make_string_charset_helper("hello", "gbk");

// 绑定 std::string 和编码
std::string s = "你好";
auto h3 = yggr::charset::make_string_charset_helper(s);

// 获取数据和编码
auto str = yggr::charset::string_charset_helper_first(h3); // std::string
auto charset = yggr::charset::string_charset_helper_second(h3); // "utf-8"
```

---

## 版权声明

MIT License，详见文件头部注释。

---

如需扩展支持自定义字符串类型或编码，请参考模板参数与实现细节。详细用法和扩展方式请查阅源码与注释。

