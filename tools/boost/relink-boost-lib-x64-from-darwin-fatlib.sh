#!/bin/bash

var_local_dir=$(cd `dirname $0`; pwd)

find "${var_local_dir}" -type l -exec rm -f {} \;
ln -s . Debug
ln -s . Release

var_fat_dylib_list=$(find ${var_local_dir} -type f -name '*.dylib')
#echo "${var_fat_dylib_list}"

for var_fpath in ${var_fat_dylib_list}
do
    var_fname=${var_fpath##*/}
    var_lname=$(echo "${var_fname}" | sed 's/-a64-/-x64-/g')
    #echo ${var_lname}

    var_cmd_link="ln -s '${var_fname}' '${var_lname}'"
    echo "${var_cmd_link}"
    eval ${var_cmd_link}

done


var_fat_a_list=$(find ${var_local_dir} -type f -name '*.a')
#echo "${var_fat_a_list}"

for var_fpath in ${var_fat_a_list}
do
    var_fname=${var_fpath##*/}
    var_lname=$(echo "${var_fname}" | sed 's/-a64-/-x64-/g')
    #echo ${var_lname}

    var_cmd_link="ln -s '${var_fname}' '${var_lname}'"
    echo "${var_cmd_link}"
    eval ${var_cmd_link}

done
