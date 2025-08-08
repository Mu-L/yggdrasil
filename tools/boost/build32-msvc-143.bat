cd /d %~dp0

b2 -j12 toolset=msvc-14.3 -sZLIB_SOURCE=%~dp0/../zlib-1.3 -sICU_PATH=d:/third_part/libicu -sICU_ICUUC_NAME=icuuc-vc143 -sICU_ICUDT_NAME=icudt-vc143 -sICU_ICUIN_NAME=icuin-vc143 --build-type=complete address-model=32

