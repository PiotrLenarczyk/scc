#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=c11 -O1 -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
LIBS=''
echo "====";echo "bootstraping:"; echo "====";
touch a.out && rm a.out && clear && gcc -DMIPS -g -o cCompiler.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT scc.c $LIBS &&
echo "====" && echo "source:" && echo "===="&&
cat 00_main.c &&
echo "====" && echo "cCompiler:" && echo "===="&&
#gdb --args cCompiler.out 00_main.c
./cCompiler.out 00_main.c &> cASM.asm && cat cASM.asm
exit 0;
