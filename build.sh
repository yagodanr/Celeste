#!/bin/bash

libs="-l SDL2 -l GL -l GLEW"
no_warnings="-Wno-writable-strings -Wno-format-security"

# Compile all source files and link with SDL2
clang++ -g src/*.cpp -o celeste $libs $no_warnings