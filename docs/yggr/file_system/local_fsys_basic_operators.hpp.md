# local_fsys_basic_operators.hpp 文档

## 1. 版权声明
MIT 许可证，允许自由使用、修改和分发。

## 2. 文件作用
本文件定义了模板类 `local_fsys_basic_operators<File_Stream_Config>`，为本地文件系统操作提供了统一、类型安全、跨平台的接口。支持文件/目录/符号链接的创建、删除、移动、复制、递归操作、属性查询、批量处理等，兼容 Boost.Filesystem v2/v3，支持 Windows/Linux 等多平台。

## 3. 主要类型与成员

### 3.1 主要类型别名
- `file_size_type`、`size_type`：文件和目录大小类型。
- `ifstream_type`、`ofstream_type`、`fbuf_type`、`char_type`：流和字符类型。
- `path_type`、`path_char_type`、`path_string_type`：路径相关类型。
- `file_status_type`、`space_info_type`、`error_code_type`、`exception_type`：状态、空间信息、错误码、异常类型。
- `directory_entry_type`、`directory_iterator_type`、`recursive_directory_iterator_type`：目录项和迭代器类型。
- `options_type`、`file_types_options_type`：操作选项类型。
- `symlink_option_type`、`directory_options_type`、`copy_option_type`：符号链接、目录、复制选项。

### 3.2 主要静态成员
- `npos`：无效文件大小常量。

## 4. 主要功能接口

### 4.1 路径与属性操作
- `current_path()`、`parent_path()`、`root_path()`、`absolute()`、`canonical()`、`system_complete()`：获取和转换路径。
- `is_exists()`、`is_in_same_volume()`、`symlink_is_in_same_volume()`：路径存在性与卷判断。
- `equivalent()`、`symlink_equivalent()`：判断路径/符号链接等价性。
- `equivalent_hash_value()`、`symlink_equivalent_hash_value()`：等价性哈希。
- `permissions()`、`path_status()`、`path_symlink_status()`、`status_known()`：权限与状态查询。
- `expand_path()`、`recursive_expand_path()`：符号链接展开。

### 4.2 目录操作
- `create_directories()`、`create_directory()`、`rename_directory()`、`move_directory()`、`copy_directory()`、`remove_directory()`、`recursive_copy_directories()`、`recursive_remove_directories()`：目录的创建、重命名、移动、复制、删除及递归操作。
- `count_children_directory()`、`recursive_count_children_directory()`：统计子目录数量。
- `is_included_in_directory()`、`is_child()`、`check_is_child()`：目录包含关系判断。

### 4.3 文件操作
- `is_regular_file()`、`file_size()`、`recursive_file_size()`：文件类型判断与大小获取。
- `create_file_of_binary()`、`create_file_of_text()`：创建二进制/文本文件。
- `write_file_of_binary()`、`write_file_of_text()`、`append_file_of_binary()`、`append_file_of_text()`：写入/追加二进制或文本文件，支持容器、迭代器等多种参数。
- `read_file_of_binary()`、`read_file_of_text()`：读取二进制或文本文件，支持容器、迭代器等多种参数。
- `copy_file()`、`rename_file()`、`move_file()`、`remove_file()`、`resize_file()`：文件的复制、重命名、移动、删除、调整大小。

### 4.4 符号链接与硬链接操作
- `is_symlink()`、`count_children_symlink()`、`create_symlink()`、`create_directory_symlink()`、`copy_symlink()`、`rename_symlink()`、`move_symlink()`、`remove_symlink()`、`read_symlink()`、`recursive_read_symlink()`：符号链接相关操作。
- `hard_link_count()`、`symlink_hard_link_count()`、`create_hard_link()`：硬链接相关操作。

### 4.5 批量与递归操作
- `copy()`、`move()`、`remove()`、`recursive_copy()`、`recursive_move()`、`recursive_remove()`：支持目录、文件、符号链接的批量和递归操作，支持自定义回调和通知处理。
- `for_each()`、`recursive_for_each()`：遍历目录或递归遍历，支持回调处理和过滤。

### 4.6 其他
- `temp_directory_path()`：获取临时目录路径。
- `space()`：获取磁盘空间信息。

## 5. 设计要点

- **类型安全**：大量使用模板和类型萃取，保证接口类型安全。
- **异常与错误码双支持**：所有操作均有异常抛出和 error_code 返回两种版本，便于灵活处理错误。
- **跨平台**：兼容 Windows/Linux，自动适配 Boost.Filesystem 版本。
- **高扩展性**：支持自定义处理器（如重命名、通知等），便于扩展特殊需求。
- **泛型友好**：支持容器、迭代器、回调等多种参数类型，适合泛型编程。
- **高性能**：内部大量使用静态断言、SFINAE、Boost.MPL 优化性能和编译期检查。

## 6. 典型用法

```cpp
using fs_ops = yggr::file_system::local_fsys_basic_operators<MyFStreamConfig>;
fs_ops::path_type path = fs_ops::current_path();
bool exists = fs_ops::is_exists(path);
fs_ops::create_directory("test_dir");
fs_ops::write_file_of_text("test.txt", "hello world");
auto size = fs_ops::file_size("test.txt");
```

## 7. 注意事项

- 部分操作（如递归、符号链接处理）在不同平台和 Boost 版本下行为略有差异，需注意兼容性。
- 文件/目录操作涉及权限和并发时需确保线程安全。
- 回调和处理器需保证异常安全和正确性。

## 8. 总结

本文件为 Yggdrasil 框架提供了功能强大、接口丰富、类型安全的本地文件系统操作工具，是跨平台 C++ 项目中进行文件和目录管理的理想选择。其设计兼顾易用性、扩展性和高性能，适合各种复杂工程场景。

---

