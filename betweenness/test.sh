#!/bin/bash
#
#SBATCH --job-name=mid-proj
#SBATCH --nodes=1
#SBATCH --ntasks=1

echo "Using Zachary's Karate Data Set"

make

echo "Method #2 Betweenness Centrality BC"
echo "--Serial Version--"
./bc data/edges.txt

echo "--OMP Version--"
OMP_NUM_THREADS=2 ./bc data/edges.txt
OMP_NUM_THREADS=4 ./bc data/edges.txt
OMP_NUM_THREADS=8 ./bc data/edges.txt

echo ""
echo "Method #3 Degree and Line Importance"
echo "--Serial Version--"
OMP_NUM_THREADS=1 srun dil data/edges.txt

echo "--OMP Version--"
OMP_NUM_THREADS=2 srun dil data/edges.txt
OMP_NUM_THREADS=4 srun dil data/edges.txt
OMP_NUM_THREADS=8 srun dil data/edges.txt


