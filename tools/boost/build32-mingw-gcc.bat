cd /d %~dp0

set PATH=%mingw32_path%;%PATH%

b2 -j12 toolset=gcc -sZLIB_SOURCE=%~dp0/../zlib-1.3 -sICU_PATH=d:/third_part/libicu_mgw15_x32 -sICU_ICUUC_NAME=icuuc.dll -sICU_ICUDT_NAME=icudt.dll -sICU_ICUIN_NAME=icuin.dll --build-type=complete address-model=32

