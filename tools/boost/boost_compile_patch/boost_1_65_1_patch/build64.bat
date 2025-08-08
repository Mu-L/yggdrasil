cd /d %~dp0

b2 -j12 toolset=msvc-10.0 -sZLIB_SOURCE=%~dp0/../zlib-1.2.12 -sICU_PATH=d:/third_part/libicu --build-type=complete address-model=64 threading=multi

