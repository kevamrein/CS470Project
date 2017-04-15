#!/bin/bash
echo "1"
OMP_NUM_THREADS=1 ./bc data/collegefootball.txt
echo "2"
OMP_NUM_THREADS=2 ./bc data/collegefootball.txt
echo "3"
OMP_NUM_THREADS=3 ./bc data/collegefootball.txt
echo "4"
OMP_NUM_THREADS=4 ./bc data/collegefootball.txt
echo "5"
OMP_NUM_THREADS=5 ./bc data/collegefootball.txt
echo "10"
OMP_NUM_THREADS=10 ./bc data/collegefootball.txt
echo "16"
OMP_NUM_THREADS=16 ./bc data/collegefootball.txt
echo "18"
OMP_NUM_THREADS=18 ./bc data/collegefootball.txt
