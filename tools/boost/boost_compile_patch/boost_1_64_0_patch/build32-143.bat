cd /d %~dp0

rem call "D:/Program Files/Microsoft Visual Studio/2022/Enterprise/VC/Auxiliary/Build/vcvars32.bat"
b2 -j12 toolset=msvc-14.3 -sZLIB_SOURCE=%~dp0/../zlib-1.3 -sICU_PATH=d:/third_part/libicu --build-type=complete address-model=32 threading=multi

