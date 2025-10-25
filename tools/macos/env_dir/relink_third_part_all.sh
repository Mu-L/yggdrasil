#!/bin/bash

cd third_part
sh relink-third_part_darwin-macosx.sh
cd ..

cd third_part_iphoneos
sh relink-third_part_darwin-iphoneos.sh
cd ..

cd third_part_iphonesimulator
sh relink-third_part_darwin-iphonesimulator.sh
cd ..
