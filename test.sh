#!/bin/bash
#
#SBATCH --job-name=final-proj
#SBATCH --nodes=1
#SBATCH --ntasks=1

make clean -C betweenness
make -C betweenness
make clean -C eigenvalue
make -C eigenvalue

labels=("Zachary's Karate Club" "Dolphin Network" "Les Miserables Network" "College Football")
texts=("data/edges.txt" "data/dolphin.txt" "data/lesmis.txt" "data/collegefootball.txt")
files=("bc" "dil")
index=0
for text in ${texts[@]}
do
    
    echo ${labels[$index]}
    echo "./ec"
    for i in 1 2 4 8 16
    do
        printf "Thread Count: %d\t" "$i"
        OMP_NUM_THREADS=${i} ./eigenvalue/ec_par eigenvalue/$text
    done
    for file in ${files[@]}
    do
        echo "./"$file
        for i in 1 2 4 8 16
        do
            printf "Thread Count: %d\t" "$i"
            OMP_NUM_THREADS=${i} ./betweenness/$file betweenness/$text
        done
    done
    index=$((index+1))
    echo ""
done
