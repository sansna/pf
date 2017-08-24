#!/bin/bash
gcc -c -fpic b1.c
gcc -c -fpic b2.c
gcc -shared -o b1.so b1.o
gcc -shared -o b2.so b2.o
gcc -ldl -g3 -O0 test.c -o test
./test
