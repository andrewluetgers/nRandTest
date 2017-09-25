#!/bin/bash

emcc -O3 -v nrand.c -s WASM=1 -s NO\_FILESYSTEM=1 -s DISABLE_EXCEPTION_CATCHING=1 -s ELIMINATE\_DUPLICATE\_FUNCTIONS=1 -s NO_EXIT_RUNTIME=1 -s EXPORTED_FUNCTIONS="['_nRand', '_setSeed', '_sRand', '_pmcRand', '_pmcSetSeed']" -o nrand.js --llvm-lto 1