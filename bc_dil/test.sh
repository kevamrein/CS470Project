#!/bin/bash
#
#SBATCH --job-name=mid-proj
#SBATCH --nodes=1
#SBATCH --ntasks=1

echo "Using Zachary's Karate Data Set"

make
TXT="data/dil_test.txt" 

echo "Method #2 Betweenness Centrality BC"
echo "--Serial Version--"
#OMP_NUM_THREADS=1 ./bc $TXT

echo "--OMP Version--"
OMP_NUM_THREADS=2 ./bc $TXT
#OMP_NUM_THREADS=4 ./bc $TXT
#OMP_NUM_THREADS=8 ./bc $TXT

echo ""
echo "Method #3 Degree and Line Importance"
echo "--Serial Version--"
#./dil-serial $TXT

echo "--OMP Version--"
OMP_NUM_THREADS=2 ./dil $TXT
#OMP_NUM_THREADS=4 ./dil $TXT
#OMP_NUM_THREADS=8 ./dil $TXT

