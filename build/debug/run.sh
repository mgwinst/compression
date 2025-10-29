#!/bin/bash

clang++ -g -std=c++23 -I../.. -I../../core main.cpp \
    ../../core/parse/parse.cpp ../../core/huffman/huffman.cpp \
    && ./a.out -f ../../tests/sample.txt
