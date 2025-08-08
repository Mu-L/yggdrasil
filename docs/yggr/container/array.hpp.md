# array.hpp 文档

## 1. 版权声明
文件顶部包含 MIT 许可证，允许自由使用、修改和分发。

## 2. 头文件包含
- 引入了 Yggdrasil 框架的基础定义、容器选择器、移动语义、静态断言、适配器等。
- 支持 Boost 和 C++11 标准库的 array。
- 包含类型萃取和分配器适配相关头文件。

## 3. 命名空间与类型适配
- `yggr::container` 命名空间内，根据宏定义选择使用 `boost::array` 或 `std::array` 作为 array 类型别名。
- 全局 using 声明：`using container::array;`，便于直接使用 `yggr::array`。

## 4. allocator_t 特化
- 针对 `std::array` 和 `boost::array`，分别特化了 `allocator_t`，统一分配器类型为 `std::allocator<T>`。

## 5. 类型判断工具
- `is_std_array` 和 `is_boost_array` 模板结构体，用于判断容器类型是否为 `std::array` 或 `boost::array`，便于模板元编程分支。

## 6. 原生数组引用转换工具
- 提供了 `cast_to_native_array_reference` 系列函数模板，支持将 `std::array`、`boost::array` 及其它兼容模板容器转换为原生数组引用或常量引用。
- 通过静态断言保证类型大小一致，转换安全。
- 支持非常量和常量两种重载。

## 7. 兼容性说明
- 文件底部说明 array 不需要兼容性调用器，因为 Boost 与 STL array 结构一致。

---

## 主要接口说明

### array 类型别名
```cpp
using yggr::container::array;
```
根据宏定义自动选择 `boost::array` 或 `std::array`。

### allocator_t 特化
```cpp
template<typename T, std::size_t N>
struct allocator_t<std::array<T, N>> { typedef std::allocator<T> type; };

template<typename T, std::size_t N>
struct allocator_t<boost::array<T, N>> { typedef std::allocator<T> type; };
```
为 array 类型提供统一分配器类型。

### 类型判断
```cpp
template<typename Container>
struct is_std_array : public boost::mpl::false_ {};

template<typename T, std::size_t N>
struct is_std_array<std::array<T, N>> : public boost::mpl::true_ {};

template<typename Container>
struct is_boost_array : public boost::mpl::false_ {};

template<typename T, std::size_t N>
struct is_boost_array<boost::array<T, N>> : public boost::mpl::true_ {};
```
用于模板元编程中判断容器类型。

### 原生数组引用转换
```cpp
template<typename T, std::size_t N>
typename array_reference_t_maker<T, N>::type
cast_to_native_array_reference(std::array<T, N>& arr);

template<typename T, std::size_t N>
typename array_const_reference_t_maker<T, N>::type
cast_to_native_array_reference(const std::array<T, N>& arr);

template<typename T, std::size_t N>
typename array_reference_t_maker<T, N>::type
cast_to_native_array_reference(boost::array<T, N>& arr);

template<typename T, std::size_t N>
typename array_const_reference_t_maker<T, N>::type
cast_to_native_array_reference(const boost::array<T, N>& arr);
```
将 array 容器转换为原生数组引用，便于与 C 风格接口兼容。

---

## 总结

本文件为 Yggdrasil 框架提供了 array 容器的统一适配、类型判断和原生数组引用转换工具，兼容 Boost 和 C++11 标准库，便于在不同平台和配置下无缝切换和使用。

