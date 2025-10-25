#!/bin/bash

#libbase64
rm -f libbase64
ln -s base64-iphonesimulator libbase64

rm -f libbase64/lib/Debug
ln -s . libbase64/lib/Debug

rm -f libbase64/lib/Release
ln -s . libbase64/lib/Release

#libblowfish
rm -f libblowfish
ln -s blowfish-iphonesimulator libblowfish

rm -f libblowfish/lib/Debug
ln -s . libblowfish/lib/Debug

rm -f libblowfish/lib/Release
ln -s . libblowfish/lib/Release

#libzlib
rm -f libzlib
ln -s libzlib-1.3-iphonesimulator libzlib

rm -f libzlib/lib/Debug
ln -s . libzlib/lib/Debug

rm -f libzlib/lib/Release
ln -s . libzlib/lib/Release

#libicu
rm -f libicu
ln -s libicu58-iphonesimulator libicu

rm -f libicu/lib/Debug
ln -s . libicu/lib/Debug

rm -f libicu/lib/Release
ln -s . libicu/lib/Release

#boost
rm -f boost
ln -s boost-iphonesimulator boost

rm -f boost/lib/Debug
ln -s . boost/lib/Debug

rm -f boost/lib/Release
ln -s . boost/lib/Release


#libmd5
rm -f libmd5
ln -s md5-iphonesimulator libmd5

rm -f libmd5/lib/Debug
ln -s . libmd5/lib/Debug

rm -f libmd5/lib/Release
ln -s . libmd5/lib/Release


#libsha
rm -f libsha
ln -s sha-iphonesimulator libsha

rm -f libsha/lib/Debug
ln -s . libsha/lib/Debug

rm -f libsha/lib/Release
ln -s . libsha/lib/Release

#libopenssl
rm -f libopenssl
ln -s openssl_3.4.0-iphonesimulator libopenssl

rm -f libopenssl/include
ln -s include-x86_64 libopenssl/include

rm -f libopenssl/lib/Debug
ln -s . libopenssl/lib/Debug

rm -f libopenssl/lib/Release
ln -s . libopenssl/lib/Release

#IntelRDFPMathLib
rm -f IntelRDFPMathLib
ln -s intel_bid-iphonesimulator IntelRDFPMathLib

rm -f IntelRDFPMathLib/lib/Debug
ln -s . IntelRDFPMathLib/lib/Debug

rm -f IntelRDFPMathLib/lib/Release
ln -s . IntelRDFPMathLib/lib/Release


#LzmaLib
rm -f LzmaLib
ln -s LzmaLib-iphonesimulator LzmaLib

rm -f LzmaLib/lib/Debug
ln -s . LzmaLib/lib/Debug

rm -f LzmaLib/lib/Release
ln -s . LzmaLib/lib/Release


#unixODBC
rm -f unixODBC
ln -s unixODBC-iphonesimulator unixODBC

rm -f unixODBC/lib/Debug
ln -s . unixODBC/lib/Debug

rm -f unixODBC/lib/Release
ln -s . unixODBC/lib/Release


#cyrus-sasl
rm -f cyrus-sasl
ln -s cyrus-sasl-2.1.28 cyrus-sasl

sudo rm -f cyrus-sasl/lib/Debug
sudo ln -s . cyrus-sasl/lib/Debug

sudo rm -f cyrus-sasl/lib/Release
sudo ln -s . cyrus-sasl/lib/Release


#libdtl
rm -f libdtl
ln -s dtl-iphonesimulator libdtl

rm -f libdtl/lib/Debug
ln -s . libdtl/lib/Debug

rm -f libdtl/lib/Release
ln -s . libdtl/lib/Release

#lua_514
#rm -f lua
#ln -s lua5_14-iphonesimulator lua

rm -f lua_514
ln -s lua5_14-iphonesimulator lua_514

rm -f lua_514/lib/Debug
ln -s . lua_514/lib/Debug

rm -f lua_514/lib/Release
ln -s . lua_514/lib/Release

#lua_521
#rm -f lua
#ln -s lua5_21-iphonesimulator lua

rm -f lua_521
ln -s lua5_21-iphonesimulator lua_521

rm -f lua_521/lib/Debug
ln -s . lua_521/lib/Debug

rm -f lua_521/lib/Release
ln -s . lua_521/lib/Release

#rm -f lua
#ln -s lua5_34-iphonesimulator lua

rm -f lua_534
ln -s lua5_34-iphonesimulator lua_534

rm -f lua_534/lib/Debug
ln -s . lua_534/lib/Debug

rm -f lua_534/lib/Release
ln -s . lua_534/lib/Release


#lua5_46
rm -f lua
ln -s lua5_46-iphonesimulator lua

rm -f lua_546
ln -s lua5_46-iphonesimulator lua_546

rm -f lua_546/lib/Debug
ln -s . lua_546/lib/Debug

rm -f lua_546/lib/Release
ln -s . lua_546/lib/Release

#lua_jit21
#rm -f lua
#ln -s luajit21-iphonesimulator lua

#rm -f lua_jit21
#ln -s luajit21-iphonesimulator lua_jit21

#rm -f lua_jit21/lib/Debug
#ln -s . lua_jit21/lib/Debug

#rm -f lua_jit21/lib/Release
#ln -s . lua_jit21/lib/Release

#luabind_501
#rm -f luabind
#ln -s luabind_501-iphonesimulator luabind

rm -f luabind_501
ln -s luabind_501-iphonesimulator luabind_501

rm -f luabind_501/lib/Debug
ln -s . luabind_501/lib/Debug

rm -f luabind_501/lib/Release
ln -s . luabind_501/lib/Release

#luabind_502
#rm -f luabind
#ln -s luabind_502-iphonesimulator luabind

rm -f luabind_502
ln -s luabind_502-iphonesimulator luabind_502

rm -f luabind_502/lib/Debug
ln -s . luabind_502/lib/Debug

rm -f luabind_502/lib/Release
ln -s . luabind_502/lib/Release

#luabind_503
#rm -f luabind
#ln -s luabind_503-iphonesimulator luabind

rm -f luabind_503
ln -s luabind_503-iphonesimulator luabind_503

rm -f luabind_503/lib/Debug
ln -s . luabind_503/lib/Debug

rm -f luabind_503/lib/Release
ln -s . luabind_503/lib/Release

#luabind_504
rm -f luabind
ln -s luabind_504-iphonesimulator luabind

rm -f luabind_504
ln -s luabind_504-iphonesimulator luabind_504

rm -f luabind_504/lib/Debug
ln -s . luabind_504/lib/Debug

rm -f luabind_504/lib/Release
ln -s . luabind_504/lib/Release

#luabind_jit21
#rm -f luabind
#ln -s luabind_jit21-iphonesimulator luabind

#rm -f luabind_jit21
#ln -s luabind_jit21-iphonesimulator luabind_jit21

#rm -f luabind_jit21/lib/Debug
#ln -s . luabind_jit21/lib/Debug

#rm -f luabind_jit21/lib/Release
#ln -s . luabind_jit21/lib/Release

#python
#rm -f python
#ln -s python-iphonesimulator python

#rm -f python/lib/Debug
#ln -s . python/lib/Debug

#rm -f python/lib/Release
#ln -s . python/lib/Release

#rm -f python/lib/libpython3.a
#ln -s libpython3.13.a python/lib/libpython3.a

#mongodb_c_driver
rm -f mongodb_c_driver
ln -s mongodb_c_driver-iphonesimulator mongodb_c_driver

rm -f mongodb_c_driver/lib/Debug
ln -s . mongodb_c_driver/lib/Debug

rm -f mongodb_c_driver/lib/Release
ln -s . mongodb_c_driver/lib/Release

#mongodb
#rm -f mongodb
#ln -s mongodb-macos-x86_64-enterprise--8.2.1 mongodb

#rm -f mongodb/lib/Debug
#ln -s . mongodb/lib/Debug

#rm -f mongodb/lib/Release
#ln -s . mongodb/lib/Release

