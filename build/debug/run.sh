#!/bin/bash

clang++ -std=c++23 -I../../core/ main.cpp \
    ../../core/parse/parse.cpp ../../core/huffman/HuffmanNode.cpp ../../core/huffman/HuffmanTree.cpp \
    && ./a.out -xzf ../../tests/some_program.c
