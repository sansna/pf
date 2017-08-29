#!/bin/bash
gcc -c -fpic b1.c
gcc -c -fpic b2.c
gcc -c -fpic b0.c
gcc -shared -o b1.so b1.o
gcc -shared -o b2.so b2.o
gcc -shared -o b0.so b0.o
gcc -ldl -lcrypto -g3 -O0 ikos_update_lib.c -o ikos_update_lib
#./ikos_update_lib
#mv b0.so b2.so
#./ikos_update_lib
