#!/bin/bash

export THEORA_LIB=$PWD/libtheora-1.1.1/out/lib
export THEORA_INCLUDE=$PWD/libtheora-1.1.1/out/include

if ! test -e "emsdk"; then
echo Starting Emscripten Initial Setup....
# Get the emsdk repo
git clone https://github.com/emscripten-core/emsdk.git

# Enter that directory
echo ..
echo Go into folder
cd emsdk
echo PWD is $PWD
echo ..

# Download and install the latest SDK tools.
echo EMSDK install latest ....
./emsdk install latest
echo ...
else
# Enter that directory
cd emsdk
fi

# Make the "latest" SDK "active" for the current user. (writes ~/.emscripten file)
echo ACTIVATE
./emsdk activate latest
export EM_CONFIG=$HOME/.emscripten
echo ...

# Activate PATH and other environment variables in the current terminal
chmod u+x emsdk_env.sh
source $PWD/emsdk_env.sh

echo path is $PWD

cd ..


cd rcbasic_runtime

echo running command: em++ main.cpp theoraplay.c -L$THEORA_LIB -I$THEORA_INCLUDE -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_GFX=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_NET=2 -s USE_OGG=1 -s USE_VORBIS=1 -ltheora -ltheoradec -o $OUT_HTML --preload-file $PROG_LOCATION -O3 -s ASYNCIFY -s SDL2_IMAGE_FORMATS='["bmp","png","xpm"]' -s TOTAL_MEMORY=134217728 -s MAXIMUM_MEMORY=1073741824 $rc_extra_web_flags
echo --------------------------

em++ main.cpp theoraplay.c "-L$THEORA_LIB" "-I$THEORA_INCLUDE" -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s USE_SDL_GFX=2 -s USE_SDL_TTF=2 -s USE_SDL_MIXER=2 -s USE_SDL_NET=2 -s USE_OGG=1 -s USE_VORBIS=1 -ltheora -ltheoradec -o "$OUT_HTML" --preload-file $PROG_LOCATION -O3 -s ASYNCIFY -s SDL2_IMAGE_FORMATS='["bmp","png","xpm"]' -s TOTAL_MEMORY=134217728 -s MAXIMUM_MEMORY=1073741824 $rc_extra_web_flags

