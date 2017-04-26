#!/bin/bash
#
#SBATCH --job-name=final-proj
#SBATCH --nodes=1
#SBATCH --ntasks=1


cd betweenness 
make
texts=("data/edges.txt" "data/dolphin.txt" "data/lesmis.txt" "data/collegefootball.txt")
files=("./bc" "./dil")
echo "test"
for text in ${texts[@]}
do
    for file in ${files[@]}
    do
        echo $file
        for i in 1 2 4 8
        do
            OMP_NUM_THREADS=${i} $file $text
        done
    done
done
