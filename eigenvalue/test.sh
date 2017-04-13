#!/bin/bash
rm out/*
make clean
make

echo "Results in out directory"
./ec_serial data/simple.txt >> out/simple_output.txt
./ec_serial data/4_nodes.txt >> out/4_nodes_output.txt
./ec_serial data/6_nodes.txt >> out/6_nodes_output.txt
./ec_serial data/12_nodes.txt >> out/12_nodes_output.txt
./ec_serial data/output_edges.txt >> out/edges_output.txt
./ec_serial data/output_dil_edges.txt >> out/dil_edges_output.txt
./ec_serial data/output_dil_edges_2.txt >> out/dil_edges_2_output.txt
