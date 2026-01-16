# size_container.hpp

概述
- 提供 `size_container<Size>` 模板，用于在网络包头中存储三个尺寸字段：表示序列化大小类型的长度、info 区域大小、data 区域大小。类内以固定字节缓冲表示（E_length = sizeof(Size) * 3）。

模板参数
- `Size`：无符号整型（如 `u16`/`u32`），要求为整型且无符号。

重要类型
- `size_type`：等于模板参数 `Size`。
- 常量 `E_length`：字节缓冲总长度（`sizeof(size_type) * 3`）。

构造与赋值
- 默认构造：初始化 `_size_t_size` 为 `sizeof(yggr::ser_size_type)`，其它为 0。
- `size_container(info_size, data_size)`：以给定 info 与 data 大小构造。
- 通过缓冲区或迭代器构造：从包含至少 `E_length` 字节的缓冲拷贝内部表示。
- 支持 `operator=` 从缓冲区赋值，也支持拷贝赋值。

访问器
- `info_size()` / `data_size()`：获取或返回引用以修改对应大小。
- `count_size()`：返回 info + data 的和。
- `size()`：静态函数，返回 `E_length`。
- `size_size()`：静态函数，返回 `sizeof(size_type)`。
- `buf()`：返回内部原始字节缓冲指针（`u8*` / `const u8*`）。
- `effective()`：检查内部 `_size_t_size` 是否等于 `sizeof(yggr::ser_size_type)`。

字节序转换
- `hton()` / `ntoh()`：返回转换后副本（分别对三字段调用 `yggr::network::hton` / `ntoh`）。

实现细节与注意点
- 内部使用 union 将三个 `size_type` 字段与固定长度字节数组 `_buf[E_length]` 共享内存，便于直接写入/读取网络缓冲。
- 构造/赋值中对缓冲长度进行断言（`assert(buf.size() >= E_length)` 或迭代器长度检查）。
- `_size_t_size` 在拷贝赋值中不被覆盖（注释中说明该字段为 const 行为意图），仅在构造时设置。
- 依赖 `yggr::ser_size_type` 以确定序列化中记录 size 的字节数。

示例（伪代码）

```cpp
typedef yggr::network::size_container<u32> szc;
// 构造
szc s(128, 1024);
assert(s.count_size() == 1152);
// 写入缓冲并发送：
u8* p = s.buf(); // 长度为 szc::size()
// 网络字节序发送
szc out = s.hton();
send_raw(out.buf(), szc::size());
```

何时使用
- 需要在自定义协议中在消息前置固定尺寸头部（info 长度 + data 长度）并以原始字节形式直接写入/读取时。

文件
- 源文件：`size_container.hpp`（查看实现以获取完整断言与字节序工具依赖）。

----
