#!/bin/bash

out_dir=boost_182
x64_dir=boost_182_x64
x32_dir=boost_182_x32

if [ -d "boost" ];then
	rm -fr boost
fi

if [ -d ${out_dir} ];then
	rm -fr ${out_dir}
fi

mkdir -p ${out_dir}

cd ${out_dir}

ln -s ../${x64_dir}/lib lib64
ln -s ../${x64_dir}/include include
ln -s ../${x32_dir}/lib lib

cd ..

ln -s ${out_dir} boost
