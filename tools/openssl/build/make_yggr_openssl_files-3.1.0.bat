
cd /d %~dp0

set var_src_root_dir=stage
set var_dst_root_dir=stage_fixed

set var_dst_vc100_dir=libopenssl-3.1.0-vc100
set var_dst_vc143_dir=libopenssl-3.1.0-vc143
set var_dst_mgw15_dir=libopenssl-3.1.0-mgw15
set var_dst_mix_dir=libopenssl-3.1.0-mix

rm -fr %var_dst_root_dir%

mkdir "%var_dst_root_dir%/%var_dst_vc100_dir%/bin"
mkdir "%var_dst_root_dir%/%var_dst_vc100_dir%/bin64"
mkdir "%var_dst_root_dir%/%var_dst_vc100_dir%/lib"
mkdir "%var_dst_root_dir%/%var_dst_vc100_dir%/lib64"

touch "%var_dst_root_dir%/%var_dst_vc100_dir%/%var_dst_vc100_dir%.txt"
cp -fr config_sample %var_dst_root_dir%/%var_dst_vc100_dir%/config
cp -fr %var_src_root_dir%/vc100-x64/include %var_dst_root_dir%/%var_dst_vc100_dir%/
cp -fr %var_src_root_dir%/vc100-x64/ssl %var_dst_root_dir%/%var_dst_vc100_dir%/
cp -fr %var_src_root_dir%/vc100-x64/html %var_dst_root_dir%/%var_dst_vc100_dir%/

:rem vc100 x64
cp -f %var_src_root_dir%/vc100-x64/bin/*.pl %var_dst_root_dir%/%var_dst_vc100_dir%/bin64/
cp -f %var_src_root_dir%/vc100-x64/bin/*.exe %var_dst_root_dir%/%var_dst_vc100_dir%/bin64/
cp -f %var_src_root_dir%/vc100-x64/bin/*.dll %var_dst_root_dir%/%var_dst_vc100_dir%/bin64/
cp -f %var_src_root_dir%/vc100-x64/lib/*.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib64/
cp -f %var_src_root_dir%/vc100-x64/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib64/libcrypto-vc100.lib
cp -f %var_src_root_dir%/vc100-x64/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib64/libssl-vc100.lib
cp -f %var_src_root_dir%/vc100-x64-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib64/libcrypto_static.lib
cp -f %var_src_root_dir%/vc100-x64-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib64/libssl_static.lib
cp -f %var_src_root_dir%/vc100-x64-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib64/libcrypto_static-vc100.lib
cp -f %var_src_root_dir%/vc100-x64-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib64/libssl_static-vc100.lib

:rem vc100 x32
cp -f %var_src_root_dir%/vc100-x32/bin/*.pl %var_dst_root_dir%/%var_dst_vc100_dir%/bin/
cp -f %var_src_root_dir%/vc100-x32/bin/*.exe %var_dst_root_dir%/%var_dst_vc100_dir%/bin/
cp -f %var_src_root_dir%/vc100-x32/bin/*.dll %var_dst_root_dir%/%var_dst_vc100_dir%/bin/
cp -f %var_src_root_dir%/vc100-x32/lib/*.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib/
cp -f %var_src_root_dir%/vc100-x32/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib/libcrypto-vc100.lib
cp -f %var_src_root_dir%/vc100-x32/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib/libssl-vc100.lib
cp -f %var_src_root_dir%/vc100-x32-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib/libcrypto_static.lib
cp -f %var_src_root_dir%/vc100-x32-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib/libssl_static.lib
cp -f %var_src_root_dir%/vc100-x32-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib/libcrypto_static-vc100.lib
cp -f %var_src_root_dir%/vc100-x32-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc100_dir%/lib/libssl_static-vc100.lib

mkdir "%var_dst_root_dir%/%var_dst_vc143_dir%/bin"
mkdir "%var_dst_root_dir%/%var_dst_vc143_dir%/bin64"
mkdir "%var_dst_root_dir%/%var_dst_vc143_dir%/lib"
mkdir "%var_dst_root_dir%/%var_dst_vc143_dir%/lib64"

touch "%var_dst_root_dir%/%var_dst_vc143_dir%/%var_dst_vc143_dir%.txt"
cp -fr config_sample %var_dst_root_dir%/%var_dst_vc143_dir%/config
cp -fr %var_src_root_dir%/vc143-x64/include %var_dst_root_dir%/%var_dst_vc143_dir%/
cp -fr %var_src_root_dir%/vc143-x64/ssl %var_dst_root_dir%/%var_dst_vc143_dir%/
cp -fr %var_src_root_dir%/vc143-x64/html %var_dst_root_dir%/%var_dst_vc143_dir%/

:rem vc143 x64
cp -f %var_src_root_dir%/vc143-x64/bin/*.pl %var_dst_root_dir%/%var_dst_vc143_dir%/bin64/
cp -f %var_src_root_dir%/vc143-x64/bin/*.exe %var_dst_root_dir%/%var_dst_vc143_dir%/bin64/
cp -f %var_src_root_dir%/vc143-x64/bin/*.dll %var_dst_root_dir%/%var_dst_vc143_dir%/bin64/
cp -f %var_src_root_dir%/vc143-x64/lib/*.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib64/
cp -f %var_src_root_dir%/vc143-x64/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib64/libcrypto-vc143.lib
cp -f %var_src_root_dir%/vc143-x64/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib64/libssl-vc143.lib
cp -f %var_src_root_dir%/vc143-x64-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib64/libcrypto_static.lib
cp -f %var_src_root_dir%/vc143-x64-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib64/libssl_static.lib
cp -f %var_src_root_dir%/vc143-x64-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib64/libcrypto_static-vc143.lib
cp -f %var_src_root_dir%/vc143-x64-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib64/libssl_static-vc143.lib

:rem vc143 x32
cp -f %var_src_root_dir%/vc143-x32/bin/*.pl %var_dst_root_dir%/%var_dst_vc143_dir%/bin/
cp -f %var_src_root_dir%/vc143-x32/bin/*.exe %var_dst_root_dir%/%var_dst_vc143_dir%/bin/
cp -f %var_src_root_dir%/vc143-x32/bin/*.dll %var_dst_root_dir%/%var_dst_vc143_dir%/bin/
cp -f %var_src_root_dir%/vc143-x32/lib/*.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib/
cp -f %var_src_root_dir%/vc143-x32/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib/libcrypto-vc143.lib
cp -f %var_src_root_dir%/vc143-x32/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib/libssl-vc143.lib
cp -f %var_src_root_dir%/vc143-x32-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib/libcrypto_static.lib
cp -f %var_src_root_dir%/vc143-x32-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib/libssl_static.lib
cp -f %var_src_root_dir%/vc143-x32-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib/libcrypto_static-vc143.lib
cp -f %var_src_root_dir%/vc143-x32-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_vc143_dir%/lib/libssl_static-vc143.lib

:rem mkdir "%var_dst_root_dir%/%var_dst_mgw15_dir%/bin"
:rem mkdir "%var_dst_root_dir%/%var_dst_mgw15_dir%/bin64"
mkdir "%var_dst_root_dir%/%var_dst_mgw15_dir%/lib"
mkdir "%var_dst_root_dir%/%var_dst_mgw15_dir%/lib64"

touch "%var_dst_root_dir%/%var_dst_mgw15_dir%/%var_dst_mgw15_dir%.txt"
cp -fr config_sample %var_dst_root_dir%/%var_dst_mgw15_dir%/config
cp -fr %var_src_root_dir%/mingw64/include %var_dst_root_dir%/%var_dst_mgw15_dir%/
cp -fr %var_src_root_dir%/mingw64/ssl %var_dst_root_dir%/%var_dst_mgw15_dir%/
cp -fr %var_src_root_dir%/mingw64/html %var_dst_root_dir%/%var_dst_mgw15_dir%/

:rem mgw15 x64
cp -fr %var_src_root_dir%/mingw64/bin %var_dst_root_dir%/%var_dst_mgw15_dir%/bin64
cp -f %var_src_root_dir%/mingw64/lib64/*.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib64/
cp -f %var_src_root_dir%/mingw64/lib64/libcrypto.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib64/libcrypto-mgw15.a
cp -f %var_src_root_dir%/mingw64/lib64/libssl.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib64/libssl-mgw15.a
cp -f %var_src_root_dir%/mingw64/lib64/libcrypto.dll.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib64/libcrypto-mgw15.dll.a
cp -f %var_src_root_dir%/mingw64/lib64/libssl.dll.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib64/libssl-mgw15.dll.a

:rem mgw15 x32
cp -fr %var_src_root_dir%/mingw32/bin %var_dst_root_dir%/%var_dst_mgw15_dir%/bin
cp -f %var_src_root_dir%/mingw32/lib/*.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib/
cp -f %var_src_root_dir%/mingw32/lib/libcrypto.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib/libcrypto-mgw15.a
cp -f %var_src_root_dir%/mingw32/lib/libssl.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib/libssl-mgw15.a
cp -f %var_src_root_dir%/mingw32/lib/libcrypto.dll.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib/libcrypto-mgw15.dll.a
cp -f %var_src_root_dir%/mingw32/lib/libssl.dll.a %var_dst_root_dir%/%var_dst_mgw15_dir%/lib/libssl-mgw15.dll.a

mkdir "%var_dst_root_dir%/%var_dst_mix_dir%/bin"
mkdir "%var_dst_root_dir%/%var_dst_mix_dir%/bin64"
mkdir "%var_dst_root_dir%/%var_dst_mix_dir%/lib"
mkdir "%var_dst_root_dir%/%var_dst_mix_dir%/lib64"

touch "%var_dst_root_dir%/%var_dst_mix_dir%/%var_dst_mix_dir%.txt"
cp -fr config_sample %var_dst_root_dir%/%var_dst_mix_dir%/config
cp -fr %var_src_root_dir%/vc143-x64/include %var_dst_root_dir%/%var_dst_mix_dir%/
cp -fr %var_src_root_dir%/vc143-x64/ssl %var_dst_root_dir%/%var_dst_mix_dir%/
cp -fr %var_src_root_dir%/vc143-x64/html %var_dst_root_dir%/%var_dst_mix_dir%/

:rem mix x64
cp -f %var_src_root_dir%/vc143-x64/bin/*.pl %var_dst_root_dir%/%var_dst_mix_dir%/bin64/
cp -f %var_src_root_dir%/vc143-x64/bin/*.exe %var_dst_root_dir%/%var_dst_mix_dir%/bin64/
cp -f %var_src_root_dir%/vc143-x64/bin/*.dll %var_dst_root_dir%/%var_dst_mix_dir%/bin64/
cp -f %var_src_root_dir%/vc143-x64/lib/*.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/
cp -f %var_src_root_dir%/vc143-x64/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libcrypto-vc143.lib
cp -f %var_src_root_dir%/vc143-x64/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libssl-vc143.lib
cp -f %var_src_root_dir%/vc143-x64-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libcrypto_static.lib
cp -f %var_src_root_dir%/vc143-x64-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libssl_static.lib
cp -f %var_src_root_dir%/vc143-x64-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libcrypto_static-vc143.lib
cp -f %var_src_root_dir%/vc143-x64-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libssl_static-vc143.lib

cp -f %var_src_root_dir%/vc100-x64/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libcrypto-vc100.lib
cp -f %var_src_root_dir%/vc100-x64/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libssl-vc100.lib
cp -f %var_src_root_dir%/vc100-x64-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libcrypto_static-vc100.lib
cp -f %var_src_root_dir%/vc100-x64-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libssl_static-vc100.lib

cp -f %var_src_root_dir%/mingw64/bin/c_rehash %var_dst_root_dir%/%var_dst_mix_dir%/bin64/
cp -f %var_src_root_dir%/mingw64/lib64/*.a %var_dst_root_dir%/%var_dst_mix_dir%/lib64/
cp -f %var_src_root_dir%/mingw64/lib64/libcrypto.a %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libcrypto-mgw15.a
cp -f %var_src_root_dir%/mingw64/lib64/libssl.a %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libssl-mgw15.a
cp -f %var_src_root_dir%/mingw64/lib64/libcrypto.dll.a %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libcrypto-mgw15.dll.a
cp -f %var_src_root_dir%/mingw64/lib64/libssl.dll.a %var_dst_root_dir%/%var_dst_mix_dir%/lib64/libssl-mgw15.dll.a

:rem mix x32
cp -f %var_src_root_dir%/vc143-x32/bin/*.pl %var_dst_root_dir%/%var_dst_mix_dir%/bin/
cp -f %var_src_root_dir%/vc143-x32/bin/*.exe %var_dst_root_dir%/%var_dst_mix_dir%/bin/
cp -f %var_src_root_dir%/vc143-x32/bin/*.dll %var_dst_root_dir%/%var_dst_mix_dir%/bin/
cp -f %var_src_root_dir%/vc143-x32/lib/*.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/
cp -f %var_src_root_dir%/vc143-x32/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libcrypto-vc143.lib
cp -f %var_src_root_dir%/vc143-x32/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libssl-vc143.lib
cp -f %var_src_root_dir%/vc143-x32-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libcrypto_static.lib
cp -f %var_src_root_dir%/vc143-x32-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libssl_static.lib
cp -f %var_src_root_dir%/vc143-x32-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libcrypto_static-vc143.lib
cp -f %var_src_root_dir%/vc143-x32-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libssl_static-vc143.lib

cp -f %var_src_root_dir%/vc100-x32/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libcrypto-vc100.lib
cp -f %var_src_root_dir%/vc100-x32/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libssl-vc100.lib
cp -f %var_src_root_dir%/vc100-x32-static/lib/libcrypto.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libcrypto_static-vc100.lib
cp -f %var_src_root_dir%/vc100-x32-static/lib/libssl.lib %var_dst_root_dir%/%var_dst_mix_dir%/lib/libssl_static-vc100.lib

cp -f %var_src_root_dir%/mingw32/bin/c_rehash %var_dst_root_dir%/%var_dst_mix_dir%/bin/
cp -f %var_src_root_dir%/mingw32/lib/*.a %var_dst_root_dir%/%var_dst_mix_dir%/lib/
cp -f %var_src_root_dir%/mingw32/lib/libcrypto.a %var_dst_root_dir%/%var_dst_mix_dir%/lib/libcrypto-mgw15.a
cp -f %var_src_root_dir%/mingw32/lib/libssl.a %var_dst_root_dir%/%var_dst_mix_dir%/lib/libssl-mgw15.a
cp -f %var_src_root_dir%/mingw32/lib/libcrypto.dll.a %var_dst_root_dir%/%var_dst_mix_dir%/lib/libcrypto-mgw15.dll.a
cp -f %var_src_root_dir%/mingw32/lib/libssl.dll.a %var_dst_root_dir%/%var_dst_mix_dir%/lib/libssl-mgw15.dll.a