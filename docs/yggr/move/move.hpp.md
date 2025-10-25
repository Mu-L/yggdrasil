# 文件：move.hpp 文档

路径：`yggr/move/move.hpp`

## 概要
`move.hpp` 提供了跨 C++ 标准（含无 C++11 rvalue 引用支持的旧编译器）下对“右值引用到左值/指针”转换的辅助函数模板。

库内使用的宏 `YGGR_NO_CXX11_RVALUE_REFERENCES` 用以判断是否有 C++11 rvalue 引用支持，并据此选择不同实现。

此头文件导出了两个主要工具函数模板：
- `rvref_to_ref`：将（可能为）右值引用形式的参数转换为左值引用（返回 T&）。
- `rvref_to_pointer`：将（可能为）右值引用形式的参数转换为指针（返回 T*），内部通过 `boost::addressof` 取得地址。

同时，文件在 `yggr::move` 命名空间内定义这些模板，并在 `yggr` 命名空间下通过 `using` 将其引入，方便使用。

文件顶部包含版权和许可声明（MIT 风格），并包含了必要的头文件依赖。

---

## 版权与许可
版权由 yggdrasil所有。许可为 MIT 风格（详见头部注释），文件里明确允许复制、修改和分发。

---

## 依赖
- `yggr/base/yggrdef.h`（项目内部定义，可能包含宏配置）
- `yggr/move/config.hpp`（move 模块配置）
- `yggr/move/has_move_emulation.hpp`（与是否需要移动仿真相关的宏/类型）
- `yggr/move/detail/move_return.hpp`（用于 move 返回的细节实现）
- Boost 库：使用了 `boost::ref`（头文件中以 `#include <boost/ref.hpp>` 引入，但实现中还用到 `boost::addressof` 与 `boost::forward` —— 请确保包含或通过其它头间接包含）

> 注意：源文件显式包含 `boost/ref.hpp`，在实现中又使用了 `boost::addressof` 与 `boost::forward`，标准用法通常需要 `boost/core/addressof.hpp` 或 `<boost/utility/forward.hpp>` / `<utility>`（C++11 下的 `std::forward`）等。仓库中其他头可能已提供这些符号。

---

## 命名空间与可见性
- 实现位于 `yggr::move` 命名空间。
- 通过 `using move::rvref_to_ref; using move::rvref_to_pointer;` 将这两个符号引入 `yggr` 顶层命名空间，便于 `yggr::rvref_to_ref` 形式直接访问。

---

## API 说明

### 模板：rvref_to_ref
原型（在支持 C++11 rvalue 引用时）：

template<typename T> inline
T& rvref_to_ref(BOOST_RV_REF(T) t)

行为：接受一个右值引用类型参数（通过宏 `BOOST_RV_REF(T)` 表示），并返回该参数的左值引用（T&）。

- 输入：一个类型为 `T&&`（或仿真宏对应形式）的参数 t。
- 输出：对 `t` 的左值引用（T&）。
- 作用：把以右值引用方式传入的对象作为左值引用来处理，常用于需要对接既支持 C++11 又兼容旧编译器的代码路径。

在不支持 C++11 rvalue 引用的环境下（`YGGR_NO_CXX11_RVALUE_REFERENCES` 已定义），实现退化为：

template<typename T> inline
T& rvref_to_ref(T& t)

也即直接接受左值引用并返回它，将接口语义在旧编译器上保持一致。

安全性与注意：返回的引用引用的是参数 `t` 的存储（函数内参数）。如果调用方传入临时对象（右值）且存在真正的 `T&&` 语义，临时对象在返回后会被延续或可能悬空——但在该函数里返回对参数的引用仅在函数被内联或用于内部转换时才安全，调用者应确保对象生命周期合法（通常配合模板参数推导或立即使用）。


### 模板：rvref_to_pointer
原型（在支持 C++11 rvalue 引用时）：

template<typename T> inline
T* rvref_to_pointer(BOOST_RV_REF(T) t)

行为：返回对象的地址，使用 `boost::addressof` 获取真实地址。实现内部通过 `rvref_to_ref(boost::forward<T>(t))` 获得左值引用再取地址。

在不支持 rvalue 引用的环境下退化为：

template<typename T> inline
T* rvref_to_pointer(T& t)

返回 `boost::addressof(t)`。

安全性与注意：同 `rvref_to_ref`，返回的指针指向参数 `t` 的存储，调用者需保证其指向对象在使用期内有效。

---

## 宏与兼容性
- `YGGR_NO_CXX11_RVALUE_REFERENCES`：当定义时，表明当前编译器或编译配置不支持 C++11 的 rvalue 引用语法，文件提供了对应的替代实现，以便在旧编译器下仍能编译通过。
- `BOOST_RV_REF(T)`：该宏通常由 Boost.Move 或类似实现定义，用于在不同时期和不同编译器上统一 rvalue 引用的表现（要确保工程中包含了定义该宏的头或相应替代实现）。

该头文件已考虑到两种情形（有或无 rvalue 引用），并将实现按条件编译，这使得库可以在现代与遗留编译器之间平滑兼容。

---

## 使用示例

下面示例展示在 C++11 环境下典型用法（假设 `YGGR_NO_CXX11_RVALUE_REFERENCES` 未定义）：

```cpp
#include <yggr/move/move.hpp>

struct X { int v; };

void foo(X& x) { /* 处理左值 */ }

int main() {
    X x;
    // 当有右值引用或 BOOST_RV_REF 宏作用时，可以把传入的 rvref 转为左值引用并使用
    foo(yggr::rvref_to_ref<X>(boost::move(x))); // 将 move 后的对象当左值处理（示意）

    X* p = yggr::rvref_to_pointer<X>(x);
    (void)p;
}
```

在不支持 C++11 的旧编译器上，接口一致，但参数类型退化为 `T&`，所以可以直接传递左值引用。

---

## 设计说明与意图
- 目的在于提供统一的接入点，使得在需要对待“以右值形式传入但需要把它当左值/取地址”的情景中能以一致的 API 编写代码。
- 在实现上使用 `boost::addressof` 获取对象地址以绕过自定义 `operator&` 的潜在重载，保证获取到对象真实内存地址。
- 使用 `boost::forward`（或等价的转发机制）确保在有 rvalue 支持时保留值类别信息。

---

## 明确契约（Contract）
- 输入：参数 t（在 C++11 下通常是 `T&&`，在旧编译器为 `T&`）。
- 输出：
  - `rvref_to_ref`：返回 `T&`，即参数对应的左值引用。
  - `rvref_to_pointer`：返回 `T*`，指向参数对象的真实地址（通过 `boost::addressof`）。
- 错误模式：无异常抛出；但若调用者对返回引用/指针所指对象的生命周期判断错误，会产生悬空引用/指针的未定义行为。
- 成功标准：正确返回有效引用或指针，且在旧编译器与 C++11 编译器下具有一致的语义（在生命周期合法的前提下）。

---

## 边界情况与注意事项
- 不要对临时对象（短生命周期的右值）在函数外长期保存由 `rvref_to_ref` 或 `rvref_to_pointer` 返回的引用或指针，除非调用者能保证临时对象的生命周期被延长。
- 若 `T` 重载了 `operator&`，`boost::addressof` 可保证拿到实际地址；因此这是实现上很好的选择。
- 确保项目中有定义 `BOOST_RV_REF`、`boost::forward` 和 `boost::addressof` 的头，否则需包含或引入对应 Boost 组件。

---

## 测试建议
- 在支持 C++11 的编译器下（例如 g++/clang++ 的现代版本或 MSVC）编译并运行包含 `rvref_to_ref` 与 `rvref_to_pointer` 的单元测试，验证对左值、右值和带有自定义 `operator&` 的类型行为。
- 在不支持 rvalue 引用的环境（或通过定义 `YGGR_NO_CXX11_RVALUE_REFERENCES` 强制模拟）下验证接口仍能编译通过并返回正确地址/引用。

建议测试用例：
1. 传入普通左值，检查返回引用与地址是否正确。
2. 传入 `std::move` / `boost::move` 后的对象（在支持 rvalue 引用时），确认函数行为符合预期且不引入悬空。
3. 类型重载 `operator&`，确保 `rvref_to_pointer` 返回真实地址。

---
