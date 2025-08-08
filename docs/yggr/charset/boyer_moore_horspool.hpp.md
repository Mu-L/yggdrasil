---
# boyer_moore_horspool.hpp 文档

该头文件为 yggdrasil 框架的字符集模块提供了 Boyer-Moore-Horspool 字符串查找算法的适配接口。Boyer-Moore-Horspool 算法是一种高效的字符串搜索算法，常用于大文本中的子串查找。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **功能**：直接引入了 `yggr::algorithm` 命名空间下的 `boyer_moore_horspool` 和 `boyer_moore_horspool_search` 算法，使其在 `yggr::charset` 下可用。
- **依赖**：
  - boyer_moore_horspool.hpp：算法实现。
  - bm_traits.hpp：算法相关 traits 支持。

---

## 主要接口

- `boyer_moore_horspool`
- `boyer_moore_horspool_search`

这两个接口均为模板函数，支持任意迭代器类型，适用于字符串、容器等的高效子串查找。

---

## 用法示例

```cpp
#include <yggr/charset/boyer_moore_horspool.hpp>
#include <string>

std::string text = "hello world";
std::string pattern = "world";

auto it = yggr::charset::boyer_moore_horspool_search(
    text.begin(), text.end(),
    pattern.begin(), pattern.end()
);

if (it != text.end()) {
    // 找到匹配
}
```

---

## 设计说明

- **适配性**：通过 `using` 声明，将算法接口暴露到 `yggr::charset` 命名空间，便于统一调用。
- **高效性**：Boyer-Moore-Horspool 算法在大文本查找中性能优越，适合高性能场景。
- **可扩展性**：依赖 traits，可适配不同字符类型和容器。

---

## 版权声明

MIT License，详见文件头部注释。

---

如需详细算法原理和参数说明，请参考 boyer_moore_horspool.hpp 的实现与注释。

