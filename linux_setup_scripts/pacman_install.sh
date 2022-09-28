#! /bin/bash
sudo rm /usr/share/applications/rcbasic.ico
sudo rm /usr/share/applications/rcbasic.desktop
sudo rm -rf /$HOME/Programs/rcbasic
sudo pacman -Sy
# sudo pacman -S --needed sdl2
# sudo pacman -S --needed sdl2_gfx
# sudo pacman -S --needed sdl2_image
# sudo pacman -S --needed sdl2_mixer
# sudo pacman -S --needed sdl2_net
# sudo pacman -S --needed sdl2_ttf
# sudo pacman -S --needed libtheora
# sudo pacman -S --needed libogg
# sudo pacman -S --needed lib32-libogg
# sudo pacman -S --needed libvorbis
sudo pacman -S --needed nodejs
sudo pacman -S --needed cmake
# This next package is required for the RCBasic Package Tool.

mkdir /$HOME/Programs
mkdir /$HOME/Programs/rcbasic

TGT_BIT=$(getconf LONG_BIT)

if [ $TGT_BIT == 64 ]
then

cp -a "$(readlink -f rcbasic64)/." /$HOME/Programs/rcbasic
sudo cp "$(readlink -f rcbasic64)/icon/rcbasic.ico" /usr/share/applications

else

cp -a "$(readlink -f rcbasic32)/." /$HOME/Programs/rcbasic
sudo cp "$(readlink -f rcbasic32)/icon/rcbasic.ico" /usr/share/applications

fi

sudo cp "$(readlink -f rcbasic_desktop_config)/rcbasic.desktop" /usr/share/applications

chmod u+x $HOME/Programs/rcbasic/rcbasic
chmod u+x $HOME/Programs/rcbasic/rcbasic_build
chmod u+x $HOME/Programs/rcbasic/rcbasic_edit

sudo ln -sf $HOME/Programs/rcbasic/rcbasic /usr/bin/rcbasic
sudo ln -sf $HOME/Programs/rcbasic/rcbasic_build /usr/bin/rcbasic_build
sudo ln -sf $HOME/Programs/rcbasic/rcbasic_edit /usr/bin/rcbasic_edit
sudo ln -sf $HOME/Programs/rcbasic/rcbasic_edit /usr/bin/rcbasic_studio_run

cp -a "$(readlink -f doc)/." /$HOME/Programs/rcbasic/doc
cp -a "$(readlink -f examples)/." /$HOME/Programs/rcbasic/examples
cp -a "$(readlink -f tools)/." /$HOME/Programs/rcbasic/tools

chmod u+x -R $HOME/Programs/rcbasic/tools/dist
chmod u+x -R $HOME/Programs/rcbasic/lib

bashrc_path=$HOME/.bashrc

RCBASIC_LIB_SET=$( cat $bashrc_path | grep RCBASIC_LIB )

if [ -z "$RCBASIC_LIB_SET" ]
then
	echo "" >> $bashrc_path
	echo "" >> $bashrc_path
	echo "# RCBASIC Library Path" >> $bashrc_path
	echo "export RCBASIC_LIB=$HOME/Programs/rcbasic/lib" >> $bashrc_path
	echo "alias rcbasic='LD_LIBRARY_PATH=\$RCBASIC_LIB rcbasic'" >> $bashrc_path
	echo "alias rcbasic_build='LD_LIBRARY_PATH=\$RCBASIC_LIB rcbasic_build'" >> $bashrc_path
	echo "alias rcbasic_edit='LD_LIBRARY_PATH=\$RCBASIC_LIB:\$LD_LIBRARY_PATH rcbasic_edit'" >> $bashrc_path
	echo "" >> $bashrc_path
	echo "" >> $bashrc_path
fi

echo "RCBasic install is complete"
