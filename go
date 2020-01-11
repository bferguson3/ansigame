#!/bin/bash
rm EXE
g++ -c main.cpp ansigame.cpp 
g++ -o EXE main.o ansigame.o -lX11
rm *.o
strip --strip-all EXE
./EXE
