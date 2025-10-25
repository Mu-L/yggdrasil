#!/bin/sh

#output="$(clang --version | head -1)"
#echo ${output}
#echo $(clang --version | sed -n '/version/s/.*version \([0-9]\+\).*/\1/p')
#clang --version | sed -n '/version/s/.*version \([0-9]\+\).*/\1/p'
#version="$(echo "${output}" | grep -o '[0-9][0-9][\.]([0-9])+[\.]([0-9])+' | cut -d. -f1 )" 
version=darwin$(clang --version | awk '/version/ {print $4}' | cut -d. -f1)
echo "$version"

#version2=$(clang --version | awk '/version/ {print $4}' | cut -d. -f1)
#clang --version | awk '/version/ {print $4}'

#echo ${version2}
