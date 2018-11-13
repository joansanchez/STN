#!/bin/bash
clear
echo "Deleting old files..."
cd outputs/
rm *.txt
cd ..
echo "Running program..."
g++ -o extraction.out film.cpp member.cpp mainCode.cpp extraction.cpp matrixGenerator.cpp influencerSearcher.cpp kMeans.cpp
./extraction.out

rm *.out
