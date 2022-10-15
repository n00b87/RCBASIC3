#! /bin/bash


# export CPATH=/home/devman/Projects/SDL_install/include
# export LIBRARY_PATH=/home/devman/Projects/SDL_install/lib

g++ -Wall -fexceptions -O2  -c main.cpp -o obj/Release/main.o
gcc -Wall -fexceptions -O2  -c theoraplay.c -o obj/Release/theoraplay.o
g++  -o bin/Release/rcbasic_runtime obj/Release/main.o obj/Release/theoraplay.o -lSDL2main -lSDL2 -lSDL2_image -lSDL2_gfx -lSDL2_ttf -lSDL2_mixer -lSDL2_net -logg -lvorbis -lvorbisfile -ltheora -ltheoradec -pthread -s  
