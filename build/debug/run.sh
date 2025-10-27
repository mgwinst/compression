#!/bin/bash

clang++ -std=c++23 -I../.. -I../../core main.cpp \
    ../../core/parse/parse.cpp ../../core/huffman/huffman.cpp \
    && ./a.out -f ../../tests/some_program.c
