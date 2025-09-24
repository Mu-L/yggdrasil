---
fstream_config.hpp 文档

---

# 文件：fstream_config.hpp

## 简介
该头文件定义了一个通用的文件流配置模板类 `fstream_config`，用于统一管理输入流、输出流、缓冲区和默认处理器类型。通过模板参数，支持灵活组合不同的流和处理器实现，便于扩展和适配多种文件系统需求。

## 版权声明

- 版权归 yggdrasil 项目所有，2010-2024
- 采用 MIT 许可证，允许自由使用、修改和分发

## 主要内容

- 头文件保护宏：`__YGGR_FILE_SYSTEM_FSTREM_CONFIG_HPP__`
- 依赖头文件：
  - `<yggr/base/yggrdef.h>`
  - `<yggr/mplex/static_assert.hpp>`
  - `<yggr/nonable/noncreateable.hpp>`
- 命名空间：`yggr::file_system`
- 模板类定义：
  ```cpp
  template<
      typename Input_Stream,
      typename Output_Stream,
      typename Buffer,
      typename Default_Handlers
  >
  class fstream_config : private nonable::noncreateable
  {
  public:
      typedef Buffer fbuf_type;
      typedef Input_Stream ifstream_type;
      typedef Output_Stream ofstream_type;
      typedef Default_Handlers default_handlers_type;
      typedef typename fbuf_type::char_type char_type;
  private:
      BOOST_MPL_ASSERT((boost::is_same<char_type, typename ifstream_type::char_type >));
      BOOST_MPL_ASSERT((boost::is_same<char_type, typename ofstream_type::char_type >));
  };
  ```
  - 该类通过类型定义和静态断言，确保流和缓冲区的字符类型一致。
  - 继承自 `nonable::noncreateable`，禁止实例化。

## 适用场景
适用于需要自定义文件流类型、缓冲区和处理器，并希望统一管理和类型安全的 C++ 项目，尤其适合跨平台和多后端文件系统适配。

---



