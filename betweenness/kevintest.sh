#!/bin/bash
echo "1"
OMP_NUM_THREADS=1 ./dil data/lesmis.txt
echo "2"
OMP_NUM_THREADS=2 ./dil data/lesmis.txt
echo "3"
OMP_NUM_THREADS=3 ./dil data/lesmis.txt
echo "4"
OMP_NUM_THREADS=4 ./dil data/lesmis.txt
echo "5"
OMP_NUM_THREADS=5 ./dil data/lesmis.txt
echo "10"
OMP_NUM_THREADS=10 ./dil data/lesmis.txt
echo "16"
OMP_NUM_THREADS=16 ./dil data/lesmis.txt
echo "18"
OMP_NUM_THREADS=18 ./dil data/lesmis.txt
