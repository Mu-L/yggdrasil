#!/bin/sh

gcc -m64 -posix -E -dM - < /dev/null > linux_gcc15_x64_macro.txt
gcc -m32 -posix -E -dM - < /dev/null > linux_gcc15_x32_macro.txt


