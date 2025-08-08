# static_index_mapping.hpp 文档

## 1. 版权声明
文件顶部为 MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件为 Yggdrasil 框架提供了静态索引映射表的定义和使用工具。通过一组宏，可以方便地定义索引枚举、静态值数组，并自动生成支持 begin/end/at/size 等 STL 风格接口的静态映射类型，适合常量查表、配置映射、枚举与值的静态绑定等场景。

## 3. 主要类型与宏

### 3.1 主体模板
- `template<typename Tag> struct static_index_mapping;`
- `template<typename Tag> struct mapping_indexes;`
- `template<typename Tag> struct mapping_values;`
这些模板通过特化与宏展开实现具体的静态映射类型。

### 3.2 索引定义相关宏
- `YGGR_PP_STATIC_MAPPING_INDEXES_BEGIN(__tag__)`  
  开始定义索引枚举类型（如 enum { E_XXX, E_YYY, ... }）。
- `YGGR_PP_STATIC_MAPPING_INDEX(__name__)`  
  定义单个索引枚举成员（如 E_XXX）。
- `YGGR_PP_STATIC_MAPPING_INDEXES_END()`  
  结束索引定义，自动添加 E_size 和 E_compile_u32。
- `YGGR_PP_GET_STATIC_MAPPING_INDEXES(__tag__)`  
  获取指定 tag 的 mapping_indexes 类型。

### 3.3 静态值定义相关宏
- `YGGR_PP_STATIC_MAPPING_VALUES_DECLEAR(__tag__, __val_type__)`  
  声明静态值数组类型。
- `YGGR_PP_STATIC_MAPPING_VALUES_BEGIN(__tag__, __val_type__)`  
  开始定义静态值数组。
- `YGGR_PP_STATIC_MAPPING_VALUE(__val__)`  
  定义单个静态值。
- `YGGR_PP_STATIC_MAPPING_VALUES_END()`  
  结束静态值数组定义。
- `YGGR_PP_GET_STATIC_MAPPING_VALUES(__tag__)`  
  获取指定 tag 的 mapping_values 类型。

### 3.4 静态映射类型生成宏
- `YGGR_PP_STATIC_MAPPING_MAKE(__indexes__, __values__)`  
  生成静态索引映射类型，自动实现 STL 风格接口（begin/end/at/size/front/back 等），并断言索引和值的 tag 类型一致。

### 3.5 静态映射访问宏
- `YGGR_PP_GET_STATIC_MAPPING(__tag__)`  
  获取静态映射类型。
- `YGGR_PP_GET_STATIC_MAPPING_INDEX(__tag__, __name__)`  
  获取指定索引的枚举值。
- `YGGR_PP_GET_STATIC_MAPPING_SIZE(__tag__)`  
  获取静态映射的大小。
- `YGGR_PP_GET_STATIC_MAPPING_VALUE(__tag__, __name__)`  
  获取指定索引对应的静态值。

---

## 4. 典型用法

```cpp
// 定义索引
YGGR_PP_STATIC_MAPPING_INDEXES_BEGIN(MyTag)
    YGGR_PP_STATIC_MAPPING_INDEX(Apple)
    YGGR_PP_STATIC_MAPPING_INDEX(Banana)
    YGGR_PP_STATIC_MAPPING_INDEX(Cherry)
YGGR_PP_STATIC_MAPPING_INDEXES_END()

// 定义静态值
YGGR_PP_STATIC_MAPPING_VALUES_BEGIN(MyTag, int)
    YGGR_PP_STATIC_MAPPING_VALUE(100)
    YGGR_PP_STATIC_MAPPING_VALUE(200)
    YGGR_PP_STATIC_MAPPING_VALUE(300)
YGGR_PP_STATIC_MAPPING_VALUES_END()

// 生成静态映射类型
YGGR_PP_STATIC_MAPPING_MAKE(YGGR_PP_GET_STATIC_MAPPING_INDEXES(MyTag), YGGR_PP_GET_STATIC_MAPPING_VALUES(MyTag))

// 使用
auto val = YGGR_PP_GET_STATIC_MAPPING_VALUE(MyTag, Banana); // 200
auto size = YGGR_PP_GET_STATIC_MAPPING_SIZE(MyTag); // 3
auto it = YGGR_PP_GET_STATIC_MAPPING(MyTag)::begin();
```

---

## 5. 设计要点

- **编译期静态映射**：所有索引和值均为编译期常量，零运行时开销。
- **类型安全**：通过 tag 类型和 BOOST_MPL_ASSERT 保证索引和值一一对应。
- **STL 风格接口**：支持 begin/end/at/front/back/size/empty 等常用接口，便于与标准容器协作。
- **宏自动生成**：通过宏定义极大简化静态映射表的声明和实现。

---

## 6. 注意事项

- 索引和值的数量必须一致，否则断言失败。
- 仅适用于静态常量查表，不支持运行时动态修改。
- 建议为每组静态映射定义唯一的 tag 类型，避免冲突。

---

## 7. 总结

本文件为 Yggdrasil 框架提供了高效、类型安全、易用的静态索引映射表工具，适合常量查表、枚举与值的静态绑定、配置映射等多种场景。通过宏定义可快速生成 STL 风格的静态查表类型，提升代码可维护性和效率。

---

