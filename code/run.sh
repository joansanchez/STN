#!/bin/bash
clear
echo "Extracting data from files"
g++ -o extraction.out film.cpp member.cpp mainCode.cpp extraction.cpp matrixGenerator.cpp influencerSearcher.cpp kMeans.cpp
./extraction.out

rm *.out
