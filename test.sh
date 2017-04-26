#!/bin/bash
#
#SBATCH --job-name=final-proj
#SBATCH --nodes=1
#SBATCH --ntasks=1


cd betweenness 
make
TXT="data/edges.txt"
files=("./bc" "./dil")
echo "test"
for file in ${files[@]}
do
    echo $file
    for i in 1 2 4 8
    do
        OMP_NUM_THREADS=${i} $file $TXT
    done
done 
