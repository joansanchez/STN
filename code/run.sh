#!/bin/bash
clear
echo "Extracting data from files"
g++ -o extraction.out film.cpp MatrixGenerator.cpp extraction.cpp
./extraction.out

rm *.out
