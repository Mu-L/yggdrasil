#!/bin/bash

var_local_dir=$(cd `dirname $0`; pwd)
var_rname_files=$(find ${var_local_dir} -type f -name '*interger*')
#echo "${var_rname_files}"

for var_fpath in ${var_rname_files}
do
    var_fname=${var_fpath##*/}
    var_lname=$(echo "${var_fname}" | sed 's/interger/integer/g')
    #echo ${var_lname}

    var_cmd_link="mv -f '${var_fname}' '${var_lname}'"
    echo "${var_cmd_link}"
    eval ${var_cmd_link}

done
