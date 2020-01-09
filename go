#!/bin/bash
rm EXE
g++ -c main.cpp ansigame.cpp 
g++ -o EXE main.o ansigame.o 
rm *.o
strip --strip-all EXE
./EXE
