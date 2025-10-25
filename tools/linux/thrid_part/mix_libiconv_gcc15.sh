#!/bin/bash

out_dir=libiconv_117
x64_dir=libiconv_117_x64
x32_dir=libiconv_117_x32

if [ -d ${out_dir} ];then
	rm -fr ${out_dir}
fi

mkdir ${out_dir}

ln -s "../${x64_dir}/bin" ${out_dir}/bin
ln -s "../${x64_dir}/lib" ${out_dir}/lib64
ln -s "../${x64_dir}/include" ${out_dir}/include
ln -s "../${x64_dir}/share" ${out_dir}/share


#ln -s ../${x32_dir}/bin ${x32_dir}/bin
ln -s ../${x32_dir}/lib ${out_dir}/lib
#ln -s ../${x32_dir}/include ${x32_dir}/include
#ln -s ../${x32_dir}/share ${x32_dir}/share

rm -f libiconv
ln -s ${out_dir} libiconv
