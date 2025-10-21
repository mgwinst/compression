#!/bin/bash

clang++ -std=c++23 main.cpp -I../../core/ \
&& ./a.out -xzf ../../tests/some_program.c
