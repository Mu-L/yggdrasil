
# 文件:conversion_helper.hpp


## 文件简介

- **版权**：2010-2024 yggdrasil
- **许可协议**：MIT License

## 主要内容

### 命名空间

- 所有内容均在 `yggr::geometry` 命名空间下。

### 主要类

#### `conversion_helper`

- 工具类，禁止实例化（继承自 `nonable::noncreateable`）。
- 所有方法均为 `static`，用于二维与三维几何对象的相互转换。

#### 主要方法

##### 二维转三维（two_to_three）

- 支持以下类型的转换：
  - `math::vector2d` → `math::vector3d`
  - `geo_line<math::vector2d>` → `geo_line<math::vector3d>`
  - `geo_line_segment<math::vector2d>` → `geo_line_segment<math::vector3d>`
- 可选支持变换矩阵（`math::matrix3d`）参与转换。

##### 三维转二维（three_to_two）

- 支持以下类型的转换：
  - `math::vector3d` → `math::vector2d`
  - `geo_line<math::vector3d>` → `geo_line<math::vector2d>`
  - `geo_line_segment<math::vector3d>` → `geo_line_segment<math::vector2d>`
- 可选支持变换矩阵（`math::matrix3d`）参与转换。

### 依赖

- vector2d.hpp
- vector3d.hpp
- matrix2d.hpp
- matrix3d.hpp
- `yggr/geometry/plane.hpp`
- geo_line.hpp
- geo_line_segment.hpp

### 适用场景

- 需要在二维与三维几何对象间进行数据转换的场景
- 适用于图形学、几何建模、空间变换等领域



