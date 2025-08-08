---
# knuth_morris_pratt.hpp 文档

该头文件为 yggdrasil 框架字符集模块提供了 Knuth-Morris-Pratt（KMP）字符串查找算法的适配接口。KMP 算法是一种高效的字符串搜索算法，适用于在大文本中查找子串，具有线性时间复杂度。

---

## 主要内容

- **命名空间**：`yggr::charset`
- **核心接口**：
  - `knuth_morris_pratt`
  - `knuth_morris_pratt_search`
- **依赖**：
  - knuth_morris_pratt.hpp：KMP 算法实现
  - kmp_traits.hpp：算法相关 traits 支持

---

## 主要功能

- 通过 `using` 声明，将 `yggr::algorithm` 命名空间下的 `knuth_morris_pratt` 和 `knuth_morris_pratt_search` 算法引入到 `yggr::charset` 命名空间，便于统一调用。
- 支持任意迭代器类型，适用于字符串、容器等的高效子串查找。

---

## 用法示例

```cpp
#include <yggr/charset/knuth_morris_pratt.hpp>
#include <string>

std::string text = "ababcabcacbab";
std::string pattern = "abcac";

auto it = yggr::charset::knuth_morris_pratt_search(
    text.begin(), text.end(),
    pattern.begin(), pattern.end()
);

if (it != text.end()) {
    // 找到匹配
}
```

---

## 设计说明

- **适配性**：通过 `using` 声明，将算法接口暴露到 `yggr::charset` 命名空间，便于统一调用和扩展。
- **高效性**：KMP 算法在大文本查找中性能优越，适合高性能场景。
- **可扩展性**：依赖 traits，可适配不同字符类型和容器。

---

## 版权声明

MIT License，详见文件头部注释。

---

如需详细算法原理和参数说明，请参考 knuth_morris_pratt.hpp 的实现与注释。

