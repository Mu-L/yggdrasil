# `yggr::network::packets_support::packets_crypher`（文件：`packets_crypher.hpp`）

## 概述
- 目的：为 Packet 加解密（crypto/crypher）提供一个轻量包装，使用外部 `Crypher` 类型实现具体的加密/解密逻辑；当 `Crypher` 为 `void` 时提供空实现（pass-through）。
- 位置：`yggr/network/packets_support/packets_crypher.hpp`（该文档与源文件同目录）。
- 适用场景：在发送/接收前对 Packet 数据进行加密/解密，或在不需要加密的构建中使用 `packets_crypher<void>` 以减少分支代码。

## 类型与模板
- `template<typename Crypher> class packets_crypher`：
  - 成员类型：`typedef Crypher crypher_type;`。
  - 成员变量：`crypher_type _crypher;`。
  - 构造：默认构造会调用 `_crypher.init()`。
  - 变参构造：通过预处理器（`YGGR_PP_FOO_*` / Boost.Preprocessor）生成多参数构造重载，允许把初始化参数转发给 `_crypher.init(...)`。
  - 方法：
    - `template<typename Pak> bool encrypt(Pak& pak) const`：调用 `_crypher.encrypt(pak)` 并返回布尔值（成功/失败）。
    - `template<typename Pak> bool decrypt(Pak& pak) const`：调用 `_crypher.decrypt(pak)` 并返回布尔值。

- `template<> class packets_crypher<void>`（特化）：
  - `crypher_type` 为 `void`。
  - 构造只存在空实现（不调用 init）。
  - `encrypt` / `decrypt` 对任何 `Pak` 都返回 `true`（即不做任何处理，始终成功）。
  - 同样使用预处理器生成的多参数构造重载，但这些构造函数为空，实现与 `Crypher` 非 `void` 的构造接口一致以简化使用处的代码。

## 行为细节
- `_crypher.init(...)`：在默认构造中无参数调用 `_crypher.init()`。当使用变参构造时，传入的参数会被完美转发到 `_crypher.init(args...)`（由预处理器宏生成对应重载）。
- `encrypt` / `decrypt`：这些函数直接把 `Pak` 转发给 `_crypher.encrypt(pak)` / `_crypher.decrypt(pak)`，因此 `Crypher` 类型必须实现对应的接口并能接受包类型 `Pak`。
- `packets_crypher<void>`：提供零成本的占位实现，适用于禁用加密功能的构建场景。

## 使用示例（伪代码）
```cpp
// 假设有一个 Crypher 实现：
struct MyCrypher {
    void init() { /* 初始化密钥/上下文 */ }
    template<typename Pak> bool encrypt(Pak& p) { /* 对 p 进行加密 */ }
    template<typename Pak> bool decrypt(Pak& p) { /* 解密 */ }
};

// 使用带 Crypher 的包装
packets_crypher<MyCrypher> cryp; // 自动调用 init
MyPacket p = ...;
if(!cryp.encrypt(p)) {
    // 处理加密失败
}

// 使用无加密（pass-through）
packets_crypher<void> null_cryp;
null_cryp.encrypt(p); // 总是返回 true
```

## 线程与生命周期注意事项
- `packets_crypher` 持有 `_crypher` 成员对象，是否线程安全取决于 `Crypher` 的实现：
  - 若 `_crypher` 内部维护可变共享状态，请在多线程环境中对 `packets_crypher` 的实例加锁或为每线程/会话使用独立实例。
  - 若 `Crypher` 是无状态或内部保证并发安全，则 `packets_crypher` 的 `encrypt` / `decrypt` 可被并发调用。
- 变参构造生成的 `init(...)` 参数会在构造时被传递并使用，注意不要传入会在构造后失效的引用。

