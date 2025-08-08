可使用gendef + dlltool
或者dumpbin + lib制作mingw的.a文件

bcdedit \set IncreaseUserVa 3072

editbin \LARGEADDRESSAWARE  "D:\msys64\mingw32\lib\gcc\i686-w64-mingw32\15.1.0\cc1plus.exe"
editbin \LARGEADDRESSAWARE "D:\msys64\mingw64\lib\gcc\x86_64-w64-mingw32\15.1.0\cc1plus.exe"
editbin \LARGEADDRESSAWARE "D:\msys64\opt\lib\gcc\i686-w64-mingw32\15.1.0\cc1plus.exe"
editbin \LARGEADDRESSAWARE "D:\msys64\opt\lib\gcc\x86_64-w64-mingw32\15.1.0\cc1plus.exe"
editbin \LARGEADDRESSAWARE "D:\msys64\usr\lib\gcc\x86_64-pc-cygwin\15.1.0\cc1plus.exe"
