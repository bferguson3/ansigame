#!/bin/bash
rm EXE
g++ main.cpp -o EXE
strip --strip-all EXE
./EXE
