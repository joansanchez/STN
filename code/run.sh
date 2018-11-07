#!/bin/bash
clear
echo "Extracting data from files"
g++ MatrixGenerator.cpp film.cpp
./a.out

rm *.out
