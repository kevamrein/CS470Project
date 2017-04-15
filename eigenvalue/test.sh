#!/bin/bash
rm out/*
make clean
make

echo "Results in out directory"
echo "Running serial tests"
./ec_serial data/simple.txt >> out/simple_serial.txt
./ec_serial data/4_nodes.txt >> out/4_nodes_serial.txt
./ec_serial data/6_nodes.txt >> out/6_nodes_serial.txt
./ec_serial data/12_nodes.txt >> out/12_nodes_serial.txt
./ec_serial data/output_edges.txt >> out/edges_serialt.txt
./ec_serial data/output_dil_edges.txt >> out/dil_edges_serial.txt
./ec_serial data/output_dil_edges_2.txt >> out/dil_edges_2_serial.txt

echo "Running parallel tests"
COUNTER=1
while [ $COUNTER -le 16 ]; do	
	OMP_NUM_THREADS=$COUNTER srun ec_par data/simple.txt >> out/simple_par.txt
	OMP_NUM_THREADS=$COUNTER srun ec_par data/4_nodes.txt >> out/4_nodes_par.txt
	OMP_NUM_THREADS=$COUNTER srun ec_par data/12_nodes.txt >> out/12_nodes_par.txti
	OMP_NUM_THREADS=$COUNTER srun ec_par data/output_edges.txt >> out/edges_par.txt
	OMP_NUM_THREADS=$COUNTER srun ec_par data/output_dil_edges.txt >> out/dil_edges_par.txt
	OMP_NUM_THREADS=$COUNTER srun ec_par data/output_dil_edges_2.txt >> out/dil_edges_2_par.txt
	let COUNTER=COUNTER*2
done

