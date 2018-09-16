#!/bin/sh

# .exe is to be found by .gitignore
g++ test.cpp -std=c++17 -O2 -o test.exe && ./test.exe && echo "it works."

