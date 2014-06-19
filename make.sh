#!/bin/sh

APP=FastLearn
bin_folder=bin_pc
APP_SUFFIX=

if [ "$2" = "ARM" ]; then
	APP_SUFFIX=.app
	bin_folder=bin_book
else
	ln -s ../../system system
fi

if [ -d $bin_folder ]; then
	rm -f -R $bin_folder
fi

rm -f ${APP}
rm -f ${APP}.app

cmake -DCMAKE_BUILD_TYPE=$1 -DTARGET_TYPE=$2
make

mkdir -p $bin_folder

mv ${APP} ${APP}${APP_SUFFIX}
mv CMakeFiles $bin_folder/CMakeFiles
mv CMakeCache.txt $bin_folder/CMakeCache.txt
mv Makefile $bin_folder/Makefile
mv cmake_install.cmake $bin_folder/cmake_install.cmake
cp ${APP}${APP_SUFFIX} $bin_folder/${APP}${APP_SUFFIX}