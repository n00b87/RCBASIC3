#! /bin/bash

pushd rcbasic_build
chmod u+x build.sh
./build.sh
popd


pushd rcbasic_runtime
chmod u+x build.sh
./build.sh
popd

pushd rcbasic_edit
chmod u+x build.sh
./build.sh
popd

mkdir rcbasic_linux

pushd rcbasic_linux

mkdir doc
mkdir geany_files

mkdir rcbasic32
mkdir rcbasic32/config
mkdir rcbasic32/config/schemes
mkdir rcbasic32/data
mkdir rcbasic32/gfx
mkdir rcbasic32/icon
mkdir rcbasic32/lib

mkdir rcbasic64
mkdir rcbasic64/config
mkdir rcbasic64/config/schemes
mkdir rcbasic64/data
mkdir rcbasic64/gfx
mkdir rcbasic64/icon
mkdir rcbasic64/lib

mkdir rcbasic_desktop_config
mkdir tools

popd

cp ./linux_setup_scripts/init_android_sdk.sh ./rcbasic_linux/init_android_sdk.sh
cp ./linux_setup_scripts/install.sh ./rcbasic_linux/install.sh
cp "./linux_setup_scripts/Install Instructions.txt" "./rcbasic_linux/Install Instructions.txt"
cp ./linux_setup_scripts/pacman_install.sh ./rcbasic_linux/pacman_install.sh
cp ./linux_setup_scripts/rcbasic_geany_config.sh ./rcbasic_linux/rcbasic_geany_config.sh
cp ./linux_setup_scripts/uninstall.sh ./rcbasic_linux/uninstall.sh
cp ./linux_setup_scripts/rcbasic.desktop ./rcbasic_linux/rcbasic_desktop_config/rcbasic.desktop

cp filetypes.rcbasic ./rcbasic_linux/geany_files/filetypes.rcbasic
cp -R ./tools/* ./rcbasic_linux/tools/

cp -R ./doc/* ./rcbasic_linux/doc

git clone git@github.com:n00b87/RCBASIC-Examples.git ./rcbasic_linux/examples

TGT_BIT=$(getconf LONG_BIT)

if [ $TGT_BIT == 64 ]
then

cp ./rcbasic_build/bin/Release/rcbasic_build ./rcbasic_linux/rcbasic64/rcbasic_build
cp ./rcbasic_runtime/bin/Release/rcbasic_runtime ./rcbasic_linux/rcbasic64/rcbasic
cp ./rcbasic_runtime/bin/Release/rcbasic_runtime ./rcbasic_linux/rcbasic64/rcbasic_studio_run
cp ./rcbasic_edit/bin/Release/rcbasic_edit ./rcbasic_linux/rcbasic64/rcbasic_studio
cp ./linux_setup_scripts/build_project.sh ./rcbasic_linux/rcbasic64/build_project.sh
cp ./linux_setup_scripts/get_run_pid.sh ./rcbasic_linux/rcbasic64/get_run_pid.sh
cp ./linux_setup_scripts/rcbasic_edit ./rcbasic_linux/rcbasic64/rcbasic_edit
cp ./linux_setup_scripts/get_deps.bas ./rcbasic_linux/rcbasic64/lib/get_deps.bas

cp ./icon/* ./rcbasic_linux/rcbasic64/icon/
cp ./rcbasic_edit/gfx/* ./rcbasic_linux/rcbasic64/gfx
cp ./rcbasic_edit/config/rcbasic_edit_linux.config ./rcbasic_linux/rcbasic64/config/rcbasic_edit.config
cp ./rcbasic_edit/config/default_view.config ./rcbasic_linux/rcbasic64/config/default_view.config
cp ./rcbasic_edit/config/schemes/* ./rcbasic_linux/rcbasic64/config/schemes/

pushd rcbasic_linux/rcbasic64/lib
rcbasic_build get_deps.bas
rcbasic get_deps
popd

else

cp ./rcbasic_build/bin/Release/rcbasic_build ./rcbasic_linux/rcbasic32/rcbasic_build
cp ./rcbasic_runtime/bin/Release/rcbasic_runtime ./rcbasic_linux/rcbasic32/rcbasic
cp ./rcbasic_runtime/bin/Release/rcbasic_runtime ./rcbasic_linux/rcbasic32/rcbasic_studio_run
cp ./rcbasic_edit/bin/Release/rcbasic_edit ./rcbasic_linux/rcbasic32/rcbasic_studio
cp ./linux_setup_scripts/build_project.sh ./rcbasic_linux/rcbasic32/build_project.sh
cp ./linux_setup_scripts/get_run_pid.sh ./rcbasic_linux/rcbasic32/get_run_pid.sh
cp ./linux_setup_scripts/rcbasic_edit.sh ./rcbasic_linux/rcbasic32/rcbasic_edit.sh
cp ./linux_setup_scripts/get_deps.bas ./rcbasic_linux/rcbasic32/lib/get_deps.bas

cp ./icon/* ./rcbasic_linux/rcbasic32/icon/
cp ./rcbasic_edit/gfx/* ./rcbasic_linux/rcbasic32/gfx
cp ./rcbasic_edit/config/rcbasic_edit_linux.config ./rcbasic_linux/rcbasic32/config/rcbasic_edit.config
cp ./rcbasic_edit/config/default_view.config ./rcbasic_linux/rcbasic32/config/default_view.config
cp ./rcbasic_edit/config/schemes ./rcbasic_linux/rcbasic32/config/schemes

pushd rcbasic_linux/rcbasic32/lib
rcbasic_build get_deps.bas
rcbasic get_deps
popd

fi

