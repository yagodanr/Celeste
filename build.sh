#!/bin/bash

no_warnings="-Wno-writable-strings -Wno-format-security"

clang++ -g src/main.cpp -o celeste $no_warnings