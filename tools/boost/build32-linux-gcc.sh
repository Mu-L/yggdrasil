#!/bin/bash

# errors.user-error : "$(ICU_ICUUC_NAME)" ;

var_local_dir=$(cd `dirname $0`; pwd)

./b2 \
    -j12 \
    toolset=gcc \
    -sZLIB_SOURCE=${var_local_dir}/../zlib-1.3 \
    -sICU_PATH=/home/${USER}/third_part/libicu58_gcc15_x32 \
    -sICU_ICUUC_NAME=icuuc \
    -sICU_ICUDT_NAME=icudata \
    -sICU_ICUIN_NAME=icui18n \
    --prefix=/home/${USER}/third_part/boost_182_x32 \
    --build-type=complete \
    --layout=versioned \
    address-model=32 \
    install