#!/bin/bash
GCC_FLAGS='-pipe -mtune=native -march=native -O0 -fmax-errors=1'
touch a.out && rm a.out && clear && gcc tinyBASIC.c $GCC_FLAGS -o tinyBASIC && ./tinyBASIC main.bas

