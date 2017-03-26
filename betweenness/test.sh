#!/bin/bash
#
#SBATCH --job-name=mid-proj
#SBATCH --output=out

echo "Using Zachary's Karate Data Set"

make clean && make cluster

echo "Method #2 Betweenness Centrality BC"
echo "Serial Version"
./bc data/edges.txt

echo "OMP Version"
OMP_NUM_THREADS=1 ./bc data/edges.txt
OMP_NUM_THREADS=2 ./bc data/edges.txt
OMP_NUM_THREADS=4 ./bc data/edges.txt
OMP_NUM_THREADS=8 ./bc data/edges.txt

echo ""
echo "Method #3 Degree and Line Importance"
echo "Serial Version"
./dil data/edges.txt

echo "OMP Version"
OMP_NUM_THREADS=1 ./dil data/edges.txt
OMP_NUM_THREADS=2 ./dil data/edges.txt
OMP_NUM_THREADS=4 ./dil data/edges.txt
OMP_NUM_THREADS=8 ./dil data/edges.txt


