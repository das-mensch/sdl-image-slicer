#!/bin/sh
gcc -Wall -O2 main.c -o sdl-slicer -D_REENTRANT -I/usr/include/SDL2 -lSDL2 -lSDL2_image
