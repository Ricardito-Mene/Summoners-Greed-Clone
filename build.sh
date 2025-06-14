#!/bin/bash

timestamp=$(date +%s)

defines="-DENGINE"
libs="-luser32 -lopengl32 -lgdi32 -lole32 -Lthird_party/lib -lfreetype.lib"
warnings="-Wno-writable-strings -Wno-format-security -Wno-deprecated-declarations -Wno-switch"

includes="-Ithird_party -Ithird_party/Include"

clang++ $includes -g src/main.cpp src/game.cpp -omain.exe $libs $warnings $defines
