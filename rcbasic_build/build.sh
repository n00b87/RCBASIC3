#! /bin/bash

g++ -Wall -fexceptions -O2  -c main.cpp -o obj/Release/main.o
g++  -o bin/Release/rcbasic_build obj/Release/main.o  -s
