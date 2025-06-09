#!/bin/bash

timestamp=$(date +%s)

libs="-l SDL2 -l GL -l GLEW"
no_warnings="-Wno-writable-strings -Wno-format-security"
includes="-I third_party -I ."

# Compile all source files and link with SDL2
clang++ -g src/main.cpp imports/*.cpp -o celeste $libs $no_warnings $includes

rm -f game_*
clang++ -rdynamic -g src/game.cpp imports/rendering.cpp -fPIC --shared -o game_$timestamp.so $no_warnings $includes
mv game_$timestamp.so game.so