#!/bin/bash
rm simple_output.txt 4_nodes_output.txt 6_nodes_output.txt 12_nodes_output.txt
make clean
make

echo "Results in out directory"
./ec_serial data/simple.txt >> out/simple_output.txt
./ec_serial data/4_nodes.txt >> out/4_nodes_output.txt
./ec_serial data/6_nodes.txt >> out/6_nodes_output.txt
./ec_serial data/12_nodes.txt >> out/12_nodes_output.txt
